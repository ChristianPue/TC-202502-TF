#ifndef STATEMENT_GEN_H
#define STATEMENT_GEN_H

#include "CodeGenerator.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include <vector>
#include <iostream>

class StatementGen {
private:
    CodeGenerator* codeGen;
    IRBuilder<>* builder;
    LLVMContext* context;
    TypeSystem* typeSystem;
    SymbolTable* symbolTable;
    Module* module;

public:
    StatementGen(CodeGenerator* cg) 
        : codeGen(cg),
          builder(cg->getBuilder()),
          context(cg->getContext()),
          typeSystem(cg->getTypeSystem()),
          symbolTable(cg->getSymbolTable()),
          module(cg->getModule()) {}

    // Declaración de variables
    void generateVarDeclaration(const std::string& name, const std::string& typeStr, Value* initVal = nullptr) {
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        Type* llvmType = typeSystem->getLLVMType(typeStr);
        
        AllocaInst* alloca = typeSystem->createEntryBlockAlloca(currentFunc, name, llvmType);
        symbolTable->declare(name, alloca);

        if (initVal) {
            if (llvmType->isFloatTy() && initVal->getType()->isIntegerTy()) {
                initVal = builder->CreateSIToFP(initVal, llvmType);
            }
            builder->CreateStore(initVal, alloca);
        }
    }

    // Asignación
    void generateAssignment(const std::string& name, Value* val) {
        AllocaInst* varPtr = symbolTable->lookup(name);
        if (!varPtr) {
            std::cerr << "Error: Variable no definida " << name << std::endl;
            return;
        }

        Type* varType = varPtr->getAllocatedType();
        
        if (varType->isFloatTy() && val->getType()->isIntegerTy()) {
            val = builder->CreateSIToFP(val, varType);
        }
        
        builder->CreateStore(val, varPtr);
    }

    // Print statement
    void generatePrint(const std::vector<Value*>& values) {
        Function* printfFunc = module->getFunction("printf");

        // 1. Imprimir cada argumento SIN salto de línea
        for (Value* val : values) {
            if (!val) continue;

            std::string fmtStr;
            
            if (val->getType()->isIntegerTy(32)) {
                fmtStr = "%d"; // Quitamos \n
            } else if (val->getType()->isFloatTy()) {
                // Usamos %.2f para limitar a 2 decimales (arregla el 99.949997)
                // O podrías usar %g para que sea dinámico y quite ceros extra
                fmtStr = "%.2f"; 
                val = builder->CreateFPExt(val, builder->getDoubleTy());
            } else if (val->getType()->isIntegerTy(1)) {
                fmtStr = "%d"; // Quitamos \n
            } else {
                fmtStr = "%s"; // Quitamos \n
            }

            Value* formatPtr = codeGen->createFormatString(fmtStr);
            builder->CreateCall(printfFunc, {formatPtr, val});
        }

        // 2. Imprimir el salto de línea AL FINAL de todo
        Value* newlineFmt = codeGen->createFormatString("\n");
        builder->CreateCall(printfFunc, {newlineFmt});
    }

    // Read statement
    void generateRead(const std::vector<std::string>& varNames) {
        FunctionCallee scanfFunc = module->getOrInsertFunction(
            "scanf",
            FunctionType::get(builder->getInt32Ty(), {builder->getPtrTy()}, true)
        );

        for (const std::string& name : varNames) {
            AllocaInst* alloca = symbolTable->lookup(name);
            if (!alloca) {
                std::cerr << "Error: Variable '" << name << "' no definida." << std::endl;
                continue;
            }

            std::string fmtStr;
            Type* type = alloca->getAllocatedType();
            
            if (type->isIntegerTy(32)) fmtStr = "%d";
            else if (type->isFloatTy()) fmtStr = "%f";
            else if (type->isIntegerTy(1)) fmtStr = "%d";
            else fmtStr = "%s";

            Value* formatPtr = codeGen->createFormatString(fmtStr);
            builder->CreateCall(scanfFunc, {formatPtr, alloca});
        }
    }

    // If statement
    struct IfBlocks {
        BasicBlock* thenBB;
        BasicBlock* elseBB;
        BasicBlock* mergeBB;
    };

    IfBlocks generateIfStart(Value* condVal, bool hasElse) {
        if (!condVal->getType()->isIntegerTy(1)) {
            condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
        }

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        
        BasicBlock* thenBB = BasicBlock::Create(*context, "then", currentFunc);
        BasicBlock* elseBB = hasElse ? BasicBlock::Create(*context, "else") : nullptr;
        BasicBlock* mergeBB = BasicBlock::Create(*context, "ifcont");

        builder->CreateCondBr(condVal, thenBB, hasElse ? elseBB : mergeBB);
        builder->SetInsertPoint(thenBB);

        return {thenBB, elseBB, mergeBB};
    }

    void generateIfElse(IfBlocks& blocks) {
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(blocks.mergeBB);
        }

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.elseBB);
        builder->SetInsertPoint(blocks.elseBB);
    }

    void generateIfEnd(IfBlocks& blocks) {
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(blocks.mergeBB);
        }

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.mergeBB);
        builder->SetInsertPoint(blocks.mergeBB);
    }

    // While loop
    struct LoopBlocks {
        BasicBlock* condBB;
        BasicBlock* loopBB;
        BasicBlock* afterBB;
    };

    LoopBlocks generateWhileStart() {
        Function* currentFunc = builder->GetInsertBlock()->getParent();

        BasicBlock* condBB = BasicBlock::Create(*context, "loopcond", currentFunc);
        BasicBlock* loopBB = BasicBlock::Create(*context, "loopbody");
        BasicBlock* afterBB = BasicBlock::Create(*context, "loopend");

        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);

        return {condBB, loopBB, afterBB};
    }

    void generateWhileCondition(LoopBlocks& blocks, Value* condVal) {
        if (!condVal->getType()->isIntegerTy(1)) {
            condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "whilecond");
        }
        builder->CreateCondBr(condVal, blocks.loopBB, blocks.afterBB);

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.loopBB);
        builder->SetInsertPoint(blocks.loopBB);
    }

    void generateWhileEnd(LoopBlocks& blocks) {
        builder->CreateBr(blocks.condBB);

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.afterBB);
        builder->SetInsertPoint(blocks.afterBB);
    }

    // Do-While loop
    LoopBlocks generateDoWhileStart() {
        Function* currentFunc = builder->GetInsertBlock()->getParent();

        BasicBlock* loopBB = BasicBlock::Create(*context, "dowhileloop", currentFunc);
        BasicBlock* condBB = BasicBlock::Create(*context, "dowhilecond");
        BasicBlock* afterBB = BasicBlock::Create(*context, "dowhileend");

        builder->CreateBr(loopBB);
        builder->SetInsertPoint(loopBB);

        return {condBB, loopBB, afterBB};
    }

    void generateDoWhileEnd(LoopBlocks& blocks, Value* condVal) {
        builder->CreateBr(blocks.condBB);

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.condBB);
        builder->SetInsertPoint(blocks.condBB);

        if (!condVal->getType()->isIntegerTy(1)) {
            condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "loopcond");
        }

        builder->CreateCondBr(condVal, blocks.loopBB, blocks.afterBB);

        currentFunc->insert(currentFunc->end(), blocks.afterBB);
        builder->SetInsertPoint(blocks.afterBB);
    }

    // Switch statement
    SwitchInst* generateSwitchStart(Value* switchVal, BasicBlock*& defaultBB, BasicBlock*& mergeBB) {
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        
        defaultBB = BasicBlock::Create(*context, "swdefault", currentFunc);
        mergeBB = BasicBlock::Create(*context, "swend");

        return builder->CreateSwitch(switchVal, defaultBB, 0);
    }

    BasicBlock* generateSwitchCase(SwitchInst* switchInst, ConstantInt* caseConst) {
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        BasicBlock* caseBB = BasicBlock::Create(*context, "swcase", currentFunc);
        switchInst->addCase(caseConst, caseBB);
        builder->SetInsertPoint(caseBB);
        return caseBB;
    }

    void generateSwitchCaseEnd(BasicBlock* mergeBB) {
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(mergeBB);
        }
    }

    void generateSwitchEnd(BasicBlock* defaultBB, BasicBlock* mergeBB) {
        builder->SetInsertPoint(defaultBB);
        builder->CreateBr(mergeBB);

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), mergeBB);
        builder->SetInsertPoint(mergeBB);
    }

    // Array declaration
    void generateArrayDeclaration(const std::string& name, uint64_t size, const std::vector<Value*>& initValues = {}) {
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        
        Type* elementType = builder->getInt32Ty();
        ArrayType* arrayType = ArrayType::get(elementType, size);
        
        AllocaInst* alloca = typeSystem->createEntryBlockAlloca(currentFunc, name, arrayType);
        symbolTable->declare(name, alloca);

        for (size_t i = 0; i < initValues.size() && i < size; ++i) {
            std::vector<Value*> indices;
            indices.push_back(builder->getInt32(0));
            indices.push_back(builder->getInt32(i));
            
            Value* ptr = builder->CreateInBoundsGEP(arrayType, alloca, indices);
            builder->CreateStore(initValues[i], ptr);
        }
    }

    // Array assignment
    void generateArrayAssignment(const std::string& name, Value* indexVal, Value* val) {
        AllocaInst* alloca = symbolTable->lookup(name);
        if (!alloca) return;

        Type* allocatedType = alloca->getAllocatedType();
        if (!allocatedType->isArrayTy()) {
            std::cerr << "Error: " << name << " no es un arreglo." << std::endl;
            return;
        }

        std::vector<Value*> indices;
        indices.push_back(builder->getInt32(0));
        indices.push_back(indexVal);

        Value* ptr = builder->CreateInBoundsGEP(allocatedType, alloca, indices, "arrayptr");
        builder->CreateStore(val, ptr);
    }

    // ForEach loop
    struct ForEachInfo {
        AllocaInst* idxVar;
        AllocaInst* elemVar;
        uint64_t arrayLen;
        Type* elemType;
    };

    ForEachInfo generateForEachStart(const std::string& iteratorName, const std::string& arrayName, 
                                      BasicBlock*& condBB, BasicBlock*& bodyBB, BasicBlock*& afterBB) {
        AllocaInst* arrAlloca = symbolTable->lookup(arrayName);
        if (!arrAlloca || !arrAlloca->getAllocatedType()->isArrayTy()) {
            return {nullptr, nullptr, 0, nullptr};
        }

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        uint64_t arrLen = arrAlloca->getAllocatedType()->getArrayNumElements();
        Type* elemType = arrAlloca->getAllocatedType()->getArrayElementType();

        AllocaInst* idxVar = typeSystem->createEntryBlockAlloca(currentFunc, iteratorName + "_idx", builder->getInt32Ty());
        builder->CreateStore(builder->getInt32(0), idxVar);

        AllocaInst* elemVar = typeSystem->createEntryBlockAlloca(currentFunc, iteratorName, elemType);
        symbolTable->declare(iteratorName, elemVar);

        condBB = BasicBlock::Create(*context, "foreachcond", currentFunc);
        bodyBB = BasicBlock::Create(*context, "foreachbody");
        afterBB = BasicBlock::Create(*context, "foreachend");

        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);

        return {idxVar, elemVar, arrLen, elemType};
    }

    void generateForEachBody(ForEachInfo& info, const std::string& arrayName, 
                             BasicBlock* bodyBB, BasicBlock* afterBB) {
        Value* curIdx = builder->CreateLoad(builder->getInt32Ty(), info.idxVar);
        Value* cond = builder->CreateICmpSLT(curIdx, builder->getInt32(info.arrayLen));
        
        builder->CreateCondBr(cond, bodyBB, afterBB);

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), bodyBB);
        builder->SetInsertPoint(bodyBB);

        AllocaInst* arrAlloca = symbolTable->lookup(arrayName);
        std::vector<Value*> indices;
        indices.push_back(builder->getInt32(0));
        indices.push_back(curIdx);
        
        Value* elemPtr = builder->CreateInBoundsGEP(arrAlloca->getAllocatedType(), arrAlloca, indices);
        Value* elemVal = builder->CreateLoad(info.elemType, elemPtr);
        builder->CreateStore(elemVal, info.elemVar);
    }

    void generateForEachEnd(ForEachInfo& info, BasicBlock* condBB, BasicBlock* afterBB) {
        Value* curIdx = builder->CreateLoad(builder->getInt32Ty(), info.idxVar);
        Value* nextIdx = builder->CreateAdd(curIdx, builder->getInt32(1));
        builder->CreateStore(nextIdx, info.idxVar);
        
        builder->CreateBr(condBB);

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), afterBB);
        builder->SetInsertPoint(afterBB);
    }
    // For loop helpers
    struct ForBlocks {
        BasicBlock* condBB;
        BasicBlock* bodyBB;
        BasicBlock* incBB;  // Bloque para el incremento (i = i + 1)
        BasicBlock* afterBB;
    };

    ForBlocks generateForStart() {
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        BasicBlock* condBB = BasicBlock::Create(*context, "forcond", currentFunc);
        BasicBlock* bodyBB = BasicBlock::Create(*context, "forbody");
        BasicBlock* incBB = BasicBlock::Create(*context, "forinc");
        BasicBlock* afterBB = BasicBlock::Create(*context, "forend");

        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);

        return {condBB, bodyBB, incBB, afterBB};
    }

    void generateForCondition(ForBlocks& blocks, Value* condVal) {
        if (!condVal->getType()->isIntegerTy(1)) {
            condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "forcond");
        }
        builder->CreateCondBr(condVal, blocks.bodyBB, blocks.afterBB);
        
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.bodyBB);
        builder->SetInsertPoint(blocks.bodyBB);
    }

    void generateForIncrementStart(ForBlocks& blocks) {
        builder->CreateBr(blocks.incBB);
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.incBB);
        builder->SetInsertPoint(blocks.incBB);
    }

    void generateForEnd(ForBlocks& blocks) {
        builder->CreateBr(blocks.condBB); // Volver a la condición tras el incremento
        Function* currentFunc = builder->GetInsertBlock()->getParent();
        currentFunc->insert(currentFunc->end(), blocks.afterBB);
        builder->SetInsertPoint(blocks.afterBB);
    }
};

#endif // STATEMENT_GEN_H
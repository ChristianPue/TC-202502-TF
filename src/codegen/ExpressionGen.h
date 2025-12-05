#ifndef EXPRESSION_GEN_H
#define EXPRESSION_GEN_H

#include "CodeGenerator.h"
#include "EduCodeParser.h"
#include "llvm/IR/Constants.h"
#include <any>
#include <iostream>

class ExpressionGen {
private:
    CodeGenerator* codeGen;
    IRBuilder<>* builder;
    LLVMContext* context;
    TypeSystem* typeSystem;
    SymbolTable* symbolTable;
    Module* module;

public:
    ExpressionGen(CodeGenerator* cg) 
        : codeGen(cg),
          builder(cg->getBuilder()),
          context(cg->getContext()),
          typeSystem(cg->getTypeSystem()),
          symbolTable(cg->getSymbolTable()),
          module(cg->getModule()) {}

    // Expresiones literales
    Value* generateInt(const std::string& text) {
        return ConstantInt::get(*context, APInt(32, std::stoi(text), true));
    }

    Value* generateFloat(const std::string& text) {
        return ConstantFP::get(*context, APFloat(std::stof(text)));
    }

    Value* generateBool(const std::string& text) {
        bool val = (text == "true" || text == "verdadero");
        return ConstantInt::get(*context, APInt(1, val ? 1 : 0, false));
    }

    Value* generateString(const std::string& text) {
        // Quitar comillas
        std::string cleanText = text;
        if (cleanText.length() >= 2) {
            cleanText = cleanText.substr(1, cleanText.length() - 2);
        }
        return builder->CreateGlobalString(cleanText, "str_lit");
    }

    // Expresiones de identificadores
    Value* generateIdLoad(const std::string& name) {
        AllocaInst* alloca = symbolTable->lookup(name);
        if (!alloca) {
            std::cerr << "Error: Variable no encontrada: " << name << std::endl;
            return nullptr;
        }
        return builder->CreateLoad(alloca->getAllocatedType(), alloca, name);
    }

    // Operaciones aritméticas
    Value* generateBinaryOp(Value* L, Value* R, int opType) {
        typeSystem->promoteOperands(L, R);
        
        bool isFloat = L->getType()->isFloatTy();

        switch (opType) {
            // ADD
            case EduCodeParser::ADD:
                return isFloat ? builder->CreateFAdd(L, R, "addtmp") 
                              : builder->CreateAdd(L, R, "addtmp");
            // SUB
            case EduCodeParser::SUB:
                return isFloat ? builder->CreateFSub(L, R, "subtmp") 
                              : builder->CreateSub(L, R, "subtmp");
            // MUL
            case EduCodeParser::MUL:
                return isFloat ? builder->CreateFMul(L, R, "multmp") 
                              : builder->CreateMul(L, R, "multmp");
            // DIV
            case EduCodeParser::DIV:
                return isFloat ? builder->CreateFDiv(L, R, "divtmp") 
                              : builder->CreateSDiv(L, R, "divtmp");
            // MOD
            case EduCodeParser::MOD:
                return isFloat ? builder->CreateFRem(L, R, "modtmp") 
                              : builder->CreateSRem(L, R, "modtmp");
            default:
                return nullptr;
        }
    }

    // Operaciones de comparación
    Value* generateComparison(Value* L, Value* R, int opType) {
        typeSystem->promoteOperands(L, R);
        
        bool isFloat = L->getType()->isFloatTy();

        if (isFloat) {
            switch (opType) {
                case EduCodeParser::LT: return builder->CreateFCmpOLT(L, R, "cmptmp");
                case EduCodeParser::GT: return builder->CreateFCmpOGT(L, R, "cmptmp");
                case EduCodeParser::LE: return builder->CreateFCmpOLE(L, R, "cmptmp");
                case EduCodeParser::GE: return builder->CreateFCmpOGE(L, R, "cmptmp");
                case EduCodeParser::EQ: return builder->CreateFCmpOEQ(L, R, "cmptmp");
                case EduCodeParser::NE: return builder->CreateFCmpONE(L, R, "cmptmp");
            }
        } else {
            switch (opType) {
                case EduCodeParser::LT: return builder->CreateICmpSLT(L, R, "cmptmp");
                case EduCodeParser::GT: return builder->CreateICmpSGT(L, R, "cmptmp");
                case EduCodeParser::LE: return builder->CreateICmpSLE(L, R, "cmptmp");
                case EduCodeParser::GE: return builder->CreateICmpSGE(L, R, "cmptmp");
                case EduCodeParser::EQ: return builder->CreateICmpEQ(L, R, "cmptmp");
                case EduCodeParser::NE: return builder->CreateICmpNE(L, R, "cmptmp");
            }
        }
        return nullptr;
    }

    // Operaciones lógicas
    Value* generateAnd(Value* L, Value* R) {
        L = typeSystem->convertToBool(L);
        R = typeSystem->convertToBool(R);
        return builder->CreateAnd(L, R, "andtmp");
    }

    Value* generateOr(Value* L, Value* R) {
        L = typeSystem->convertToBool(L);
        R = typeSystem->convertToBool(R);
        return builder->CreateOr(L, R, "ortmp");
    }

    Value* generateNot(Value* val) {
        val = typeSystem->convertToBool(val);
        return builder->CreateNot(val, "nottmp");
    }

    // Acceso a arrays
    Value* generateArrayAccess(const std::string& arrayName, Value* indexVal) {
        AllocaInst* alloca = symbolTable->lookup(arrayName);
        if (!alloca) return nullptr;

        Type* allocatedType = alloca->getAllocatedType();
        if (!allocatedType->isArrayTy()) {
            std::cerr << "Error: " << arrayName << " no es un arreglo." << std::endl;
            return nullptr;
        }

        std::vector<Value*> indices;
        indices.push_back(builder->getInt32(0));
        indices.push_back(indexVal);

        Value* ptr = builder->CreateInBoundsGEP(allocatedType, alloca, indices, "elemPtr");
        return builder->CreateLoad(allocatedType->getArrayElementType(), ptr, "elemVal");
    }

    // Length de array
    Value* generateLength(const std::string& arrayName) {
        AllocaInst* alloca = symbolTable->lookup(arrayName);
        if (!alloca) return builder->getInt32(0);

        Type* type = alloca->getAllocatedType();
        if (type->isArrayTy()) {
            uint64_t len = type->getArrayNumElements();
            return ConstantInt::get(*context, APInt(32, len));
        }
        return builder->getInt32(0);
    }

    // Read como expresión
    Value* generateReadExpr() {
        FunctionCallee scanfFunc = module->getOrInsertFunction(
            "scanf",
            FunctionType::get(builder->getInt32Ty(), {builder->getPtrTy()}, true)
        );

        Function* currentFunc = builder->GetInsertBlock()->getParent();
        AllocaInst* tempVar = typeSystem->createEntryBlockAlloca(
            currentFunc, "read_tmp", builder->getInt32Ty()
        );

        Value* formatPtr = codeGen->createFormatString("%d");
        builder->CreateCall(scanfFunc, {formatPtr, tempVar});

        return builder->CreateLoad(builder->getInt32Ty(), tempVar, "read_val");
    }
};

#endif // EXPRESSION_GEN_H
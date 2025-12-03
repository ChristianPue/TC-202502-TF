#ifndef DRIVER_H
#define DRIVER_H

#include "antlr4-runtime.h"
#include "EduCodeBaseVisitor.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <system_error>
#include <iostream>

using namespace llvm;

class Driver : public EduCodeBaseVisitor {
public:
    std::unique_ptr<LLVMContext> context;
    std::unique_ptr<Module> module;
    std::unique_ptr<IRBuilder<>> builder;
    std::map<std::string, AllocaInst*> namedValues;

    Driver() {
        context = std::make_unique<LLVMContext>();
        module = std::make_unique<Module>("EduCodeModule", *context);
        builder = std::make_unique<IRBuilder<>>(*context);
        
        setupExternalFunctions();
    }

    void setupExternalFunctions() {
        // Setup printf: int printf(ptr, ...)
        std::vector<Type*> printfArgs;
        printfArgs.push_back(builder->getPtrTy()); 
        FunctionType* printfType = FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        module->getOrInsertFunction("printf", printfType);
    }

    void saveIR(const std::string& filename) {
        std::error_code EC;
        raw_fd_ostream dest(filename, EC, sys::fs::OF_None);
        if (EC) {
            std::cerr << "Error exportando IR: " << EC.message() << std::endl;
            return;
        }
        module->print(dest, nullptr);
    }

    // --- Helpers ---

    AllocaInst* createEntryBlockAlloca(Function *TheFunction, const std::string &VarName, Type* type) {
        IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
        return TmpB.CreateAlloca(type, nullptr, VarName);
    }

    Type* getLLVMType(const std::string& typeName) {
        if (typeName == "int" || typeName == "entero") return builder->getInt32Ty();
        if (typeName == "float" || typeName == "real") return builder->getFloatTy();
        if (typeName == "bool" || typeName == "booleano") return builder->getInt1Ty();
        if (typeName == "string" || typeName == "cadena") return builder->getPtrTy();
        return builder->getVoidTy();
    }

    // Helper para convertir cualquier valor numérico a Float si es necesario
    Value* convertToFloat(Value* val) {
        if (val->getType()->isFloatTy()) return val;
        if (val->getType()->isIntegerTy()) return builder->CreateSIToFP(val, builder->getFloatTy(), "casttmp");
        return val; // Should handle error
    }

    // --- VISITORS ---

    std::any visitProgram(EduCodeParser::ProgramContext *ctx) override {
        FunctionType *funcType = FunctionType::get(builder->getInt32Ty(), false);
        Function *mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", module.get());
        
        BasicBlock *entry = BasicBlock::Create(*context, "entry", mainFunc);
        builder->SetInsertPoint(entry);

        visitChildren(ctx);

        builder->CreateRet(builder->getInt32(0));
        return std::any();
    }

    // --- Declaraciones y Asignaciones ---
    std::any visitVarDef(EduCodeParser::VarDefContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::string typeStr = ctx->children[0]->getText();
        
        Function *TheFunction = builder->GetInsertBlock()->getParent();
        Type* llvmType = getLLVMType(typeStr);
        
        AllocaInst *Alloca = createEntryBlockAlloca(TheFunction, name, llvmType);
        namedValues[name] = Alloca;

        if (ctx->expression()) {
            std::any valAny = visit(ctx->expression());
            if (valAny.has_value()) {
                Value* initVal = std::any_cast<Value*>(valAny);
                if (llvmType->isFloatTy() && initVal->getType()->isIntegerTy()) {
                    initVal = builder->CreateSIToFP(initVal, llvmType);
                }
                builder->CreateStore(initVal, Alloca);
            }
        }
        return std::any();
    }
    std::any visitAssignExpr(EduCodeParser::AssignExprContext *ctx) override {
        std::string name = ctx->ID()->getText();
        if (namedValues.find(name) == namedValues.end()) {
             std::cerr << "Error: Variable no definida " << name << std::endl;
             return std::any();
        }

        std::any valAny = visit(ctx->expression());
        if (valAny.has_value()) {
            Value* val = std::any_cast<Value*>(valAny);
            AllocaInst* varPtr = namedValues[name];
            Type* varType = varPtr->getAllocatedType();
            
            if (varType->isFloatTy() && val->getType()->isIntegerTy()) {
                val = builder->CreateSIToFP(val, varType);
            }
            builder->CreateStore(val, varPtr);
        }
        return std::any();
    }

    // --- Statements (Delegados) ---
    std::any visitVarDeclaration(EduCodeParser::VarDeclarationContext *ctx) override {
        return visit(ctx->varDef()); // Delega a la nueva regla
    }

    std::any visitAssignment(EduCodeParser::AssignmentContext *ctx) override {
        return visit(ctx->assignExpr()); // Delega a la nueva regla
    }

    // --- I/O ---
    std::any visitPrintStatement(EduCodeParser::PrintStatementContext *ctx) override {
        Function* printfFunc = module->getFunction("printf");
        
        for (auto expr : ctx->expression()) {
            std::any valAny = visit(expr);
            if (!valAny.has_value()) continue;
            
            Value* val = std::any_cast<Value*>(valAny);
            std::string fmtStr;

            if (val->getType()->isIntegerTy(32)) fmtStr = "%d\n";
            else if (val->getType()->isFloatTy()) {
                fmtStr = "%f\n"; 
                val = builder->CreateFPExt(val, builder->getDoubleTy()); // printf usa double para floats
            }
            else if (val->getType()->isIntegerTy(1)) fmtStr = "%d\n"; // bool
            else fmtStr = "%s\n"; // Asumimos string/ptr

            // Crear string global para el formato
            Constant *formatConst = ConstantDataArray::getString(*context, fmtStr);
            GlobalVariable *var = new GlobalVariable(
                *module, formatConst->getType(), true, GlobalValue::PrivateLinkage, formatConst, ".str");
            
            Value* formatPtr = builder->CreateInBoundsGEP(
                formatConst->getType(), var, {builder->getInt32(0), builder->getInt32(0)});

            builder->CreateCall(printfFunc, {formatPtr, val});
        }
        return std::any();
    }

    // --- Control de Flujo ---

    std::any visitBlock(EduCodeParser::BlockContext *ctx) override {
        // En un compilador completo aquí manejaríamos scopes locales
        visitChildren(ctx);
        return std::any();
    }

    std::any visitIfStatement(EduCodeParser::IfStatementContext *ctx) override {
        // 1. Evaluar condición
        std::any condAny = visit(ctx->expression(0));
        Value* condVal = std::any_cast<Value*>(condAny);
        
        // Asegurar que sea bool (i1)
        if (!condVal->getType()->isIntegerTy(1)) {
            condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "ifcond");
        }

        Function *TheFunction = builder->GetInsertBlock()->getParent();
        
        BasicBlock *ThenBB = BasicBlock::Create(*context, "then", TheFunction);
        BasicBlock *ElseBB = BasicBlock::Create(*context, "else");
        BasicBlock *MergeBB = BasicBlock::Create(*context, "ifcont");

        bool hasElse = (ctx->ELSE() != nullptr);
        
        builder->CreateCondBr(condVal, ThenBB, hasElse ? ElseBB : MergeBB);

        // --- Generar Then ---
        builder->SetInsertPoint(ThenBB);
        visit(ctx->block(0)); // Primer bloque (then)
        
        // Solo crear salto si el bloque no tiene terminador (ej. return)
        if (!builder->GetInsertBlock()->getTerminator())
            builder->CreateBr(MergeBB);

        // --- Generar Else ---
        if (hasElse) {
            TheFunction->insert(TheFunction->end(), ElseBB);
            builder->SetInsertPoint(ElseBB);
            visit(ctx->block(1)); // Segundo bloque (else)
            if (!builder->GetInsertBlock()->getTerminator())
                builder->CreateBr(MergeBB);
        }

        // --- Continuar ---
        TheFunction->insert(TheFunction->end(), MergeBB);
        builder->SetInsertPoint(MergeBB);

        return std::any();
    }

    std::any visitWhileStatement(EduCodeParser::WhileStatementContext *ctx) override {
        Function *TheFunction = builder->GetInsertBlock()->getParent();

        BasicBlock *CondBB = BasicBlock::Create(*context, "loopcond", TheFunction);
        BasicBlock *LoopBB = BasicBlock::Create(*context, "loopbody");
        BasicBlock *AfterBB = BasicBlock::Create(*context, "loopend");

        // Salto inicial a la condición
        builder->CreateBr(CondBB);

        // --- Condición ---
        builder->SetInsertPoint(CondBB);
        std::any condAny = visit(ctx->expression());
        Value* condVal = std::any_cast<Value*>(condAny);
        if (!condVal->getType()->isIntegerTy(1)) {
             condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "whilecond");
        }
        builder->CreateCondBr(condVal, LoopBB, AfterBB);

        // --- Cuerpo ---
        TheFunction->insert(TheFunction->end(), LoopBB);
        builder->SetInsertPoint(LoopBB);
        visit(ctx->block());
        builder->CreateBr(CondBB); // Volver a evaluar

        // --- Fin ---
        TheFunction->insert(TheFunction->end(), AfterBB);
        builder->SetInsertPoint(AfterBB);

        return std::any();
    }

    // --- Expresiones ---

    std::any visitAddSubExpr(EduCodeParser::AddSubExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        
        bool isFloat = L->getType()->isFloatTy() || R->getType()->isFloatTy();

        if (isFloat) {
            L = convertToFloat(L);
            R = convertToFloat(R);
            if (ctx->op->getType() == EduCodeParser::ADD) return (Value*)builder->CreateFAdd(L, R, "addtmp");
            else return (Value*)builder->CreateFSub(L, R, "subtmp");
        } else {
            if (ctx->op->getType() == EduCodeParser::ADD) return (Value*)builder->CreateAdd(L, R, "addtmp");
            else return (Value*)builder->CreateSub(L, R, "subtmp");
        }
    }

    std::any visitMulDivModExpr(EduCodeParser::MulDivModExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        
        bool isFloat = L->getType()->isFloatTy() || R->getType()->isFloatTy();
        
        if (isFloat) {
            L = convertToFloat(L);
            R = convertToFloat(R);
            if (ctx->op->getType() == EduCodeParser::MUL) return (Value*)builder->CreateFMul(L, R, "multmp");
            else if (ctx->op->getType() == EduCodeParser::DIV) return (Value*)builder->CreateFDiv(L, R, "divtmp");
            else return (Value*)builder->CreateFRem(L, R, "modtmp");
        } else {
            if (ctx->op->getType() == EduCodeParser::MUL) return (Value*)builder->CreateMul(L, R, "multmp");
            else if (ctx->op->getType() == EduCodeParser::DIV) return (Value*)builder->CreateSDiv(L, R, "divtmp");
            else return (Value*)builder->CreateSRem(L, R, "modtmp");
        }
    }

    std::any visitComparisonExpr(EduCodeParser::ComparisonExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));

        bool isFloat = L->getType()->isFloatTy() || R->getType()->isFloatTy();
        if (isFloat) {
            L = convertToFloat(L);
            R = convertToFloat(R);
            // FCmp
            switch (ctx->op->getType()) {
                case EduCodeParser::LT: return (Value*)builder->CreateFCmpOLT(L, R, "cmptmp");
                case EduCodeParser::GT: return (Value*)builder->CreateFCmpOGT(L, R, "cmptmp");
                case EduCodeParser::LE: return (Value*)builder->CreateFCmpOLE(L, R, "cmptmp");
                case EduCodeParser::GE: return (Value*)builder->CreateFCmpOGE(L, R, "cmptmp");
                case EduCodeParser::EQ: return (Value*)builder->CreateFCmpOEQ(L, R, "cmptmp");
                case EduCodeParser::NE: return (Value*)builder->CreateFCmpONE(L, R, "cmptmp");
            }
        } else {
            // ICmp
            switch (ctx->op->getType()) {
                case EduCodeParser::LT: return (Value*)builder->CreateICmpSLT(L, R, "cmptmp");
                case EduCodeParser::GT: return (Value*)builder->CreateICmpSGT(L, R, "cmptmp");
                case EduCodeParser::LE: return (Value*)builder->CreateICmpSLE(L, R, "cmptmp");
                case EduCodeParser::GE: return (Value*)builder->CreateICmpSGE(L, R, "cmptmp");
                case EduCodeParser::EQ: return (Value*)builder->CreateICmpEQ(L, R, "cmptmp");
                case EduCodeParser::NE: return (Value*)builder->CreateICmpNE(L, R, "cmptmp");
            }
        }
        return std::any();
    }

    std::any visitParenExpr(EduCodeParser::ParenExprContext *ctx) override { return visit(ctx->expression()); }
    
    std::any visitIdExpr(EduCodeParser::IdExprContext *ctx) override { 
        std::string name = ctx->ID()->getText();
        if (namedValues.find(name) == namedValues.end()) {
            std::cerr << "Error: Variable no encontrada: " << name << std::endl;
            return std::any();
        }
        AllocaInst* alloca = namedValues[name];
        return (Value*)builder->CreateLoad(alloca->getAllocatedType(), alloca, name.c_str()); 
    }

    std::any visitIntExpr(EduCodeParser::IntExprContext *ctx) override {
        return (Value*)ConstantInt::get(*context, APInt(32, std::stoi(ctx->INT()->getText()), true));
    }
    
    std::any visitFloatExpr(EduCodeParser::FloatExprContext *ctx) override {
        return (Value*)ConstantFP::get(*context, APFloat(std::stof(ctx->FLOAT()->getText())));
    }

    std::any visitBoolExpr(EduCodeParser::BoolExprContext *ctx) override {
        bool val = (ctx->BOOLEAN()->getText() == "true" || ctx->BOOLEAN()->getText() == "verdadero");
        return (Value*)ConstantInt::get(*context, APInt(1, val ? 1 : 0, false));
    }

    // Stubs restantes (Switch, For, Read)
    std::any visitReadStatement(EduCodeParser::ReadStatementContext *ctx) override {
        // Asegurar que scanf existe: int scanf(ptr, ...)
        std::vector<Type*> scanfArgs;
        scanfArgs.push_back(builder->getPtrTy());
        FunctionType* scanfType = FunctionType::get(builder->getInt32Ty(), scanfArgs, true);
        FunctionCallee scanfFunc = module->getOrInsertFunction("scanf", scanfType);

        for (auto idNode : ctx->ID()) {
            std::string name = idNode->getText();
            if (namedValues.find(name) == namedValues.end()) {
                std::cerr << "Error: Variable '" << name << "' no definida antes de leer." << std::endl;
                continue;
            }

            AllocaInst* alloca = namedValues[name];
            std::string fmtStr;

            // Determinar formato según el tipo de la variable
            Type* type = alloca->getAllocatedType();
            if (type->isIntegerTy(32)) fmtStr = "%d";
            else if (type->isFloatTy()) fmtStr = "%f";
            else if (type->isIntegerTy(1)) fmtStr = "%d"; // bool como int
            else fmtStr = "%s"; // char*

            Constant *formatConst = ConstantDataArray::getString(*context, fmtStr);
            GlobalVariable *var = new GlobalVariable(
                *module, formatConst->getType(), true, GlobalValue::PrivateLinkage, formatConst, ".str_scanf");
            
            Value* formatPtr = builder->CreateInBoundsGEP(
                formatConst->getType(), var, {builder->getInt32(0), builder->getInt32(0)});

            // Llamar a scanf(format, variable_ptr)
            builder->CreateCall(scanfFunc, {formatPtr, alloca});
        }
        return std::any();
    }
    std::any visitForStatement(EduCodeParser::ForStatementContext *ctx) override {
        Function *TheFunction = builder->GetInsertBlock()->getParent();

        // 1. Inicialización
        if (ctx->varDef()) visit(ctx->varDef());
        else if (ctx->assignExpr().size() > 0 && ctx->children[2] == ctx->assignExpr(0)) visit(ctx->assignExpr(0));
        else if (ctx->expression().size() > 0 && ctx->children[2] == ctx->expression(0)) visit(ctx->expression(0));

        BasicBlock *CondBB = BasicBlock::Create(*context, "forcond", TheFunction);
        BasicBlock *LoopBB = BasicBlock::Create(*context, "forbody");
        BasicBlock *AfterBB = BasicBlock::Create(*context, "forend");

        builder->CreateBr(CondBB);

        // 2. Condición
        builder->SetInsertPoint(CondBB);
        Value* condVal = nullptr;
        
        // Buscar la expresión de condición (está entre los SEMI)
        // Estrategia simple: si hay una expresión que NO está en init ni update
        // Dado que la gramática es laxa, asumimos:
        // Si hay expression() y no es la init (children[2]), entonces es cond.
        // O más robusto: buscar expresión en el medio.
        EduCodeParser::ExpressionContext* condExpr = nullptr;
        
        // Recorrer hijos para encontrar expresión entre los dos ';'
        bool firstSemiFound = false;
        for (auto child : ctx->children) {
            if (child->getText() == ";") {
                if (!firstSemiFound) firstSemiFound = true;
                else break; // Segundo semi
            } else if (firstSemiFound) {
                // Si es una expresión, es la condición
                if (auto expr = dynamic_cast<EduCodeParser::ExpressionContext*>(child)) {
                    condExpr = expr;
                }
            }
        }

        if (condExpr) {
             std::any condAny = visit(condExpr); 
             condVal = std::any_cast<Value*>(condAny);
             if (!condVal->getType()->isIntegerTy(1))
                condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "loopcond");
        } else {
             condVal = ConstantInt::get(Type::getInt1Ty(*context), 1); // Bucle infinito
        }

        builder->CreateCondBr(condVal, LoopBB, AfterBB);

        // 3. Cuerpo
        TheFunction->insert(TheFunction->end(), LoopBB);
        builder->SetInsertPoint(LoopBB);
        visit(ctx->block());

        // 4. Update (Incremento)
        // Puede ser assignExpr o expression. Está al final.
        if (ctx->assignExpr().size() > 0) {
            // Si el init NO fue assignExpr, entonces el assignExpr(0) es update.
            // Si el init FUE assignExpr, entonces assignExpr(1) es update.
            bool initIsAssign = (ctx->children[2] == ctx->assignExpr(0));
            int updateIdx = initIsAssign ? 1 : 0;
            if (ctx->assignExpr().size() > updateIdx) visit(ctx->assignExpr(updateIdx));
        } 
        else if (ctx->expression().size() > 0) {
            // Lógica similar para expression
            // Simplificación: Ejecutar la última expresión si está cerca del final
            auto lastChild = ctx->children[ctx->children.size()-2]; // penúltimo (antes de ')')
            if (auto expr = dynamic_cast<EduCodeParser::ExpressionContext*>(lastChild)) {
                visit(expr);
            }
        }
        
        builder->CreateBr(CondBB);

        // 5. Salida
        TheFunction->insert(TheFunction->end(), AfterBB);
        builder->SetInsertPoint(AfterBB);

        return std::any();
    }
    std::any visitDoWhileStatement(EduCodeParser::DoWhileStatementContext *ctx) override {
        Function *TheFunction = builder->GetInsertBlock()->getParent();

        BasicBlock *LoopBB = BasicBlock::Create(*context, "dowhileloop", TheFunction);
        BasicBlock *CondBB = BasicBlock::Create(*context, "dowhilecond");
        BasicBlock *AfterBB = BasicBlock::Create(*context, "dowhileend");

        // 1. Entrar directamente al loop
        builder->CreateBr(LoopBB);

        // 2. Cuerpo del ciclo
        builder->SetInsertPoint(LoopBB);
        visit(ctx->block());
        builder->CreateBr(CondBB);

        // 3. Condición
        TheFunction->insert(TheFunction->end(), CondBB);
        builder->SetInsertPoint(CondBB);
        
        std::any condAny = visit(ctx->expression());
        Value* condVal = std::any_cast<Value*>(condAny);
        
        if (!condVal->getType()->isIntegerTy(1)) {
            condVal = builder->CreateICmpNE(condVal, ConstantInt::get(condVal->getType(), 0), "loopcond");
        }
        
        // Si es verdadero, vuelve al LoopBB; si no, sale
        builder->CreateCondBr(condVal, LoopBB, AfterBB);

        // 4. Bloque de salida
        TheFunction->insert(TheFunction->end(), AfterBB);
        builder->SetInsertPoint(AfterBB);

        return std::any();
    }
    std::any visitSwitchStatement(EduCodeParser::SwitchStatementContext *ctx) override {
        // 1. Evaluar expresión del switch
        std::any condAny = visit(ctx->expression());
        Value* switchVal = std::any_cast<Value*>(condAny);

        Function *TheFunction = builder->GetInsertBlock()->getParent();
        
        // Bloques de destino
        BasicBlock *DefaultBB = BasicBlock::Create(*context, "swdefault", TheFunction);
        BasicBlock *MergeBB = BasicBlock::Create(*context, "swend"); // Donde nos unimos al final

        // Crear instrucción Switch
        // numCases = cantidad de 'case'
        SwitchInst *Switch = builder->CreateSwitch(switchVal, DefaultBB, ctx->caseClause().size());

        // 2. Generar casos
        for (auto caseCtx : ctx->caseClause()) {
            // Evaluar valor del caso (debe ser constante entera para LLVM Switch simple)
            std::any caseValAny = visit(caseCtx->expression());
            Value* caseValPtr = std::any_cast<Value*>(caseValAny);
            
            // Verificamos si es constante
            ConstantInt* caseConst = dyn_cast<ConstantInt>(caseValPtr);
            if (!caseConst) {
                std::cerr << "Error: Los casos del switch deben ser constantes enteras." << std::endl;
                continue;
            }

            // Crear bloque para este caso
            BasicBlock *CaseBB = BasicBlock::Create(*context, "swcase", TheFunction);
            builder->SetInsertPoint(CaseBB);
            
            // Generar sentencias del caso
            for (auto stmt : caseCtx->statement()) {
                visit(stmt);
            }
            
            // Break implícito (saltar al final)
            if (!builder->GetInsertBlock()->getTerminator())
                builder->CreateBr(MergeBB);

            // Añadir al switch
            Switch->addCase(caseConst, CaseBB);
        }

        // 3. Generar Default
        builder->SetInsertPoint(DefaultBB);
        if (ctx->DEFAULT()) {
            // Si hay declaraciones en default
            for (auto stmt : ctx->statement()) {
                visit(stmt);
            }
        }
        builder->CreateBr(MergeBB);

        // 4. Continuar
        TheFunction->insert(TheFunction->end(), MergeBB);
        builder->SetInsertPoint(MergeBB);

        return std::any();
    }
    std::any visitArrayDeclaration(EduCodeParser::ArrayDeclarationContext *ctx) override {
        std::string name = ctx->ID()->getText();
        Function *TheFunction = builder->GetInsertBlock()->getParent();
        
        // Tipo base: Asumimos Int32 según nota
        Type* elementType = builder->getInt32Ty(); 
        uint64_t size = 0;
        Value* initList = nullptr;

        // Caso 1: array id[INT];
        if (ctx->INT()) {
            size = std::stoi(ctx->INT()->getText());
        } 
        // Caso 2: array id = [exp, exp...];
        else if (ctx->expressionList()) {
            size = ctx->expressionList()->expression().size();
        }

        // Crear el tipo Array [size x i32]
        ArrayType *arrayType = ArrayType::get(elementType, size);
        AllocaInst *alloca = createEntryBlockAlloca(TheFunction, name, arrayType);
        namedValues[name] = alloca;

        // Inicializar valores si existen
        if (ctx->expressionList()) {
            int idx = 0;
            for (auto expr : ctx->expressionList()->expression()) {
                std::any valAny = visit(expr);
                Value* val = std::any_cast<Value*>(valAny);
                
                // Obtener puntero al elemento i: &name[0][i]
                std::vector<Value*> indices;
                indices.push_back(builder->getInt32(0)); // Dereferencia el puntero al array
                indices.push_back(builder->getInt32(idx++)); // Índice del elemento
                
                Value *ptr = builder->CreateInBoundsGEP(arrayType, alloca, indices);
                builder->CreateStore(val, ptr);
            }
        }

        return std::any();
    }
    std::any visitArrayAssignment(EduCodeParser::ArrayAssignmentContext *ctx) override {
        std::string name = ctx->ID()->getText();
        if (namedValues.find(name) == namedValues.end()) return std::any();

        AllocaInst *alloca = namedValues[name];
        Type *allocatedType = alloca->getAllocatedType();

        // Verificar que sea un array
        if (!allocatedType->isArrayTy()) {
            std::cerr << "Error: " << name << " no es un arreglo." << std::endl;
            return std::any();
        }

        // 1. Calcular índice
        std::any idxAny = visit(ctx->expression(0));
        Value *indexVal = std::any_cast<Value*>(idxAny);

        // 2. Calcular valor a asignar
        std::any resAny = visit(ctx->expression(1));
        Value *val = std::any_cast<Value*>(resAny);

        // 3. Obtener dirección: &arr[0][index]
        std::vector<Value*> indices;
        indices.push_back(builder->getInt32(0));
        indices.push_back(indexVal);

        Value *ptr = builder->CreateInBoundsGEP(allocatedType, alloca, indices, "arrayptr");
        builder->CreateStore(val, ptr);

        return std::any();
    }
    std::any visitForEachStatement(EduCodeParser::ForEachStatementContext *ctx) override {
        std::string iteratorName = ctx->ID(0)->getText(); // Variable local (ej. 'x')
        std::string arrayName = ctx->ID(1)->getText();    // Array (ej. 'arr')
        
        if (namedValues.find(arrayName) == namedValues.end()) return std::any();
        AllocaInst *arrAlloca = namedValues[arrayName];
        if (!arrAlloca->getAllocatedType()->isArrayTy()) return std::any();

        Function *TheFunction = builder->GetInsertBlock()->getParent();
        uint64_t arrLen = arrAlloca->getAllocatedType()->getArrayNumElements();

        // 1. Crear variable iteradora interna (ej. 'idx')
        AllocaInst *idxVar = createEntryBlockAlloca(TheFunction, iteratorName + "_idx", builder->getInt32Ty());
        builder->CreateStore(builder->getInt32(0), idxVar); // idx = 0

        // 2. Crear variable del elemento (ej. 'x')
        Type* elemType = arrAlloca->getAllocatedType()->getArrayElementType();
        AllocaInst *elemVar = createEntryBlockAlloca(TheFunction, iteratorName, elemType);
        namedValues[iteratorName] = elemVar; // Registrar en tabla de símbolos para que el bloque lo use

        // Bloques
        BasicBlock *CondBB = BasicBlock::Create(*context, "foreachcond", TheFunction);
        BasicBlock *BodyBB = BasicBlock::Create(*context, "foreachbody");
        BasicBlock *AfterBB = BasicBlock::Create(*context, "foreachend");

        builder->CreateBr(CondBB);

        // --- Condición (idx < length) ---
        builder->SetInsertPoint(CondBB);
        Value *curIdx = builder->CreateLoad(builder->getInt32Ty(), idxVar);
        Value *cond = builder->CreateICmpSLT(curIdx, builder->getInt32(arrLen));
        builder->CreateCondBr(cond, BodyBB, AfterBB);

        // --- Cuerpo ---
        TheFunction->insert(TheFunction->end(), BodyBB);
        builder->SetInsertPoint(BodyBB);

        // Cargar elemento actual: x = arr[idx]
        std::vector<Value*> indices;
        indices.push_back(builder->getInt32(0));
        indices.push_back(curIdx);
        Value *elemPtr = builder->CreateInBoundsGEP(arrAlloca->getAllocatedType(), arrAlloca, indices);
        Value *elemVal = builder->CreateLoad(elemType, elemPtr);
        builder->CreateStore(elemVal, elemVar);

        // Ejecutar bloque del usuario
        visit(ctx->block());

        // Incremento: idx = idx + 1
        Value *nextIdx = builder->CreateAdd(curIdx, builder->getInt32(1));
        builder->CreateStore(nextIdx, idxVar);
        
        builder->CreateBr(CondBB); // Loop

        // --- Fin ---
        TheFunction->insert(TheFunction->end(), AfterBB);
        builder->SetInsertPoint(AfterBB);

        return std::any();
    }
    std::any visitStringExpr(EduCodeParser::StringExprContext *ctx) override {
        std::string text = ctx->STRING()->getText();
        // Quitar comillas
        if (text.length() >= 2) {
            text = text.substr(1, text.length() - 2);
        }
        
        // CORREGIDO: Usar CreateGlobalString en lugar de CreateGlobalStringPtr
        return (Value*)builder->CreateGlobalString(text, "str_lit");
    }
    std::any visitAndExpr(EduCodeParser::AndExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));

        // Asegurar que sean bool (i1)
        if (!L->getType()->isIntegerTy(1)) 
            L = builder->CreateICmpNE(L, ConstantInt::get(L->getType(), 0));
        if (!R->getType()->isIntegerTy(1)) 
            R = builder->CreateICmpNE(R, ConstantInt::get(R->getType(), 0));

        return (Value*)builder->CreateAnd(L, R, "andtmp");
    }
    std::any visitOrExpr(EduCodeParser::OrExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));

        if (!L->getType()->isIntegerTy(1)) 
            L = builder->CreateICmpNE(L, ConstantInt::get(L->getType(), 0));
        if (!R->getType()->isIntegerTy(1)) 
            R = builder->CreateICmpNE(R, ConstantInt::get(R->getType(), 0));

        return (Value*)builder->CreateOr(L, R, "ortmp");
    }
    std::any visitNotExpr(EduCodeParser::NotExprContext *ctx) override {
        Value* val = std::any_cast<Value*>(visit(ctx->expression()));

        if (!val->getType()->isIntegerTy(1)) 
            val = builder->CreateICmpNE(val, ConstantInt::get(val->getType(), 0));

        return (Value*)builder->CreateNot(val, "nottmp");
    }
    std::any visitReadExpr(EduCodeParser::ReadExprContext *ctx) override {
        // 1. Preparar scanf
        std::vector<Type*> scanfArgs;
        scanfArgs.push_back(builder->getPtrTy());
        FunctionType* scanfType = FunctionType::get(builder->getInt32Ty(), scanfArgs, true);
        FunctionCallee scanfFunc = module->getOrInsertFunction("scanf", scanfType);

        // 2. Crear variable temporal en stack para guardar el input
        Function *TheFunction = builder->GetInsertBlock()->getParent();
        AllocaInst *tempVar = createEntryBlockAlloca(TheFunction, "read_tmp", builder->getInt32Ty());

        // 3. Crear formato "%d"
        Constant *formatConst = ConstantDataArray::getString(*context, "%d");
        GlobalVariable *var = new GlobalVariable(
            *module, formatConst->getType(), true, GlobalValue::PrivateLinkage, formatConst, ".str_read_expr");
        
        Value* formatPtr = builder->CreateInBoundsGEP(
            formatConst->getType(), var, {builder->getInt32(0), builder->getInt32(0)});

        // 4. Llamar scanf("%d", &tempVar)
        builder->CreateCall(scanfFunc, {formatPtr, tempVar});

        // 5. Cargar y retornar el valor leído
        return (Value*)builder->CreateLoad(builder->getInt32Ty(), tempVar, "read_val");
    }
    std::any visitLengthExpr(EduCodeParser::LengthExprContext *ctx) override {
        std::string name = ctx->ID()->getText();
        if (namedValues.find(name) == namedValues.end()) return std::any();

        AllocaInst *alloca = namedValues[name];
        Type *type = alloca->getAllocatedType();

        if (type->isArrayTy()) {
            uint64_t len = type->getArrayNumElements();
            return (Value*)ConstantInt::get(*context, APInt(32, len));
        }
        return (Value*)ConstantInt::get(*context, APInt(32, 0));
    }
    std::any visitArrayAccessExpr(EduCodeParser::ArrayAccessExprContext *ctx) override {
        // La regla en grammar es: arrayAccess (que contiene ID y expression)
        // Pero en tu grammar expression llama a arrayAccess.
        // Necesitamos acceder al contexto interno de arrayAccess
        // NOTA: Según tu gramática (línea 16 y 13b), el nodo se llama arrayAccess
        
        std::string name = ctx->arrayAccess()->ID()->getText();
        if (namedValues.find(name) == namedValues.end()) return std::any();

        AllocaInst *alloca = namedValues[name];
        Type *allocatedType = alloca->getAllocatedType();

        if (!allocatedType->isArrayTy()) return std::any();

        // Evaluar índice
        std::any idxAny = visit(ctx->arrayAccess()->expression());
        Value *indexVal = std::any_cast<Value*>(idxAny);

        // GEP load
        std::vector<Value*> indices;
        indices.push_back(builder->getInt32(0));
        indices.push_back(indexVal);

        Value *ptr = builder->CreateInBoundsGEP(allocatedType, alloca, indices, "elemPtr");
        return (Value*)builder->CreateLoad(allocatedType->getArrayElementType(), ptr, "elemVal");
    }
};

#endif // DRIVER_H
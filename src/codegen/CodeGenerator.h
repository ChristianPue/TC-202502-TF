#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

#include "TypeSystem.h"
#include "SymbolTable.h"

#include <memory>
#include <string>
#include <system_error>
#include <iostream>

using namespace llvm;

class CodeGenerator {
protected:
    std::unique_ptr<LLVMContext> context;
    std::unique_ptr<Module> module;
    std::unique_ptr<IRBuilder<>> builder;
    std::unique_ptr<TypeSystem> typeSystem;
    std::unique_ptr<SymbolTable> symbolTable;

public:
    CodeGenerator() {
        context = std::make_unique<LLVMContext>();
        module = std::make_unique<Module>("EduCodeModule", *context);
        builder = std::make_unique<IRBuilder<>>(*context);
        typeSystem = std::make_unique<TypeSystem>(builder.get(), context.get());
        symbolTable = std::make_unique<SymbolTable>();
        
        setupRuntimeFunctions();
    }

    virtual ~CodeGenerator() = default;

    // Setup de funciones externas (printf, scanf)
    void setupRuntimeFunctions() {
        // printf: int printf(ptr, ...)
        std::vector<Type*> printfArgs;
        printfArgs.push_back(builder->getPtrTy());
        FunctionType* printfType = FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        module->getOrInsertFunction("printf", printfType);

        // scanf: int scanf(ptr, ...)
        std::vector<Type*> scanfArgs;
        scanfArgs.push_back(builder->getPtrTy());
        FunctionType* scanfType = FunctionType::get(builder->getInt32Ty(), scanfArgs, true);
        module->getOrInsertFunction("scanf", scanfType);
    }

    // Exportar IR a archivo
    void saveIR(const std::string& filename) {
        std::error_code EC;
        raw_fd_ostream dest(filename, EC, sys::fs::OF_None);
        if (EC) {
            std::cerr << "Error exportando IR: " << EC.message() << std::endl;
            return;
        }
        module->print(dest, nullptr);
    }

    // Crear función main
    Function* createMainFunction() {
        FunctionType* funcType = FunctionType::get(builder->getInt32Ty(), false);
        Function* mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", module.get());
        
        BasicBlock* entry = BasicBlock::Create(*context, "entry", mainFunc);
        builder->SetInsertPoint(entry);
        
        return mainFunc;
    }

    // Finalizar función main
    void finalizeMainFunction() {
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateRet(builder->getInt32(0));
        }
    }

    // Helpers para crear strings globales con formato
    Value* createFormatString(const std::string& format) {
        Constant* formatConst = ConstantDataArray::getString(*context, format);
        GlobalVariable* var = new GlobalVariable(
            *module, formatConst->getType(), true, GlobalValue::PrivateLinkage, formatConst, ".str");
        
        return builder->CreateInBoundsGEP(
            formatConst->getType(), var, {builder->getInt32(0), builder->getInt32(0)});
    }

    // Getters para subclases
    IRBuilder<>* getBuilder() { return builder.get(); }
    LLVMContext* getContext() { return context.get(); }
    Module* getModule() { return module.get(); }
    TypeSystem* getTypeSystem() { return typeSystem.get(); }
    SymbolTable* getSymbolTable() { return symbolTable.get(); }
};

#endif // CODE_GENERATOR_H
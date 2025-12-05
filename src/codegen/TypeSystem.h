#ifndef TYPE_SYSTEM_H
#define TYPE_SYSTEM_H

#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include <string>

using namespace llvm;

class TypeSystem {
private:
    IRBuilder<>* builder;
    LLVMContext* context;

public:
    TypeSystem(IRBuilder<>* builder, LLVMContext* context) 
        : builder(builder), context(context) {}

    // Convertir nombre de tipo EduCode a tipo LLVM
    Type* getLLVMType(const std::string& typeName) {
        if (typeName == "int" || typeName == "entero") 
            return builder->getInt32Ty();
        if (typeName == "float" || typeName == "real" || typeName == "decimal") 
            return builder->getFloatTy();
        if (typeName == "bool" || typeName == "booleano") 
            return builder->getInt1Ty();
        if (typeName == "string" || typeName == "cadena") 
            return builder->getPtrTy();
        return builder->getVoidTy();
    }

    // Convertir valor a float si es necesario
    Value* convertToFloat(Value* val) {
        if (val->getType()->isFloatTy()) 
            return val;
        if (val->getType()->isIntegerTy()) 
            return builder->CreateSIToFP(val, builder->getFloatTy(), "casttmp");
        return val;
    }

    // Convertir valor a booleano (i1)
    Value* convertToBool(Value* val) {
        if (val->getType()->isIntegerTy(1)) 
            return val;
        return builder->CreateICmpNE(val, ConstantInt::get(val->getType(), 0), "tobool");
    }

    // Crear alloca en el bloque de entrada de la función
    AllocaInst* createEntryBlockAlloca(Function* function, const std::string& varName, Type* type) {
        IRBuilder<> tmpBuilder(&function->getEntryBlock(), function->getEntryBlock().begin());
        return tmpBuilder.CreateAlloca(type, nullptr, varName);
    }

    // Determinar el tipo resultante de una operación binaria (promoción de tipos)
    Type* getResultType(Value* L, Value* R) {
        // Si alguno es float, el resultado es float
        if (L->getType()->isFloatTy() || R->getType()->isFloatTy()) {
            return builder->getFloatTy();
        }
        // Si ambos son enteros, mantener entero
        if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy()) {
            return builder->getInt32Ty();
        }
        // Por defecto, int32
        return builder->getInt32Ty();
    }

    // Promover ambos operandos al tipo resultado
    void promoteOperands(Value*& L, Value*& R) {
        Type* resultType = getResultType(L, R);
        
        if (resultType->isFloatTy()) {
            L = convertToFloat(L);
            R = convertToFloat(R);
        }
    }
};

#endif // TYPE_SYSTEM_H
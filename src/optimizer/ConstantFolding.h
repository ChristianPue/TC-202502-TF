#ifndef CONSTANT_FOLDING_H
#define CONSTANT_FOLDING_H

#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include <vector>

using namespace llvm;

class ConstantFolding {
public:
    // Aplica plegado de constantes a una función
    static bool runOnFunction(Function& F) {
        bool modified = false;
        std::vector<Instruction*> toRemove;

        for (BasicBlock& BB : F) {
            for (Instruction& I : BB) {
                if (Value* simplified = simplifyInstruction(&I)) {
                    // Reemplazar todos los usos de la instrucción por el valor constante
                    I.replaceAllUsesWith(simplified);
                    // Marcar para eliminación segura fuera del bucle
                    toRemove.push_back(&I);
                    modified = true;
                }
            }
        }

        // Eliminar instrucciones reemplazadas
        for (Instruction* I : toRemove) {
            I->eraseFromParent();
        }

        return modified;
    }

private:
    // Simplifica una instrucción si es posible
    static Value* simplifyInstruction(Instruction* I) {
        // Operaciones binarias con dos constantes o identidades
        if (auto* BO = dyn_cast<BinaryOperator>(I)) {
            return foldBinaryOp(BO);
        }

        // Comparaciones con dos constantes
        if (auto* Cmp = dyn_cast<CmpInst>(I)) {
            return foldComparison(Cmp);
        }

        // Cast con constante
        if (auto* Cast = dyn_cast<CastInst>(I)) {
            return foldCast(Cast);
        }

        return nullptr;
    }

    // Plegar operaciones binarias
    static Value* foldBinaryOp(BinaryOperator* BO) {
        Value* L = BO->getOperand(0);
        Value* R = BO->getOperand(1);

        // Identidades algebraicas (x+0, x*1, etc.)
        // Intentamos esto primero por si uno de los dos no es constante
        if (Value* V = foldAlgebraicIdentities(BO)) {
            return V;
        }

        // Para operaciones matemáticas, ambos deben ser constantes
        ConstantInt* CI_L = dyn_cast<ConstantInt>(L);
        ConstantInt* CI_R = dyn_cast<ConstantInt>(R);
        ConstantFP* CF_L = dyn_cast<ConstantFP>(L);
        ConstantFP* CF_R = dyn_cast<ConstantFP>(R);

        // Operaciones con enteros
        if (CI_L && CI_R) {
            APInt LVal = CI_L->getValue();
            APInt RVal = CI_R->getValue();
            APInt Result(LVal.getBitWidth(), 0);

            switch (BO->getOpcode()) {
                case Instruction::Add: Result = LVal + RVal; break;
                case Instruction::Sub: Result = LVal - RVal; break;
                case Instruction::Mul: Result = LVal * RVal; break;
                case Instruction::SDiv: 
                    if (!RVal.isZero()) Result = LVal.sdiv(RVal);
                    else return nullptr; 
                    break;
                case Instruction::SRem: 
                    if (!RVal.isZero()) Result = LVal.srem(RVal);
                    else return nullptr;
                    break;
                default: return nullptr;
            }
            return ConstantInt::get(BO->getType(), Result);
        }

        // Operaciones con floats
        if (CF_L && CF_R) {
            const APFloat& LVal = CF_L->getValueAPF();
            const APFloat& RVal = CF_R->getValueAPF();
            APFloat Result = LVal;

            switch (BO->getOpcode()) {
                case Instruction::FAdd: Result.add(RVal, APFloat::rmNearestTiesToEven); break;
                case Instruction::FSub: Result.subtract(RVal, APFloat::rmNearestTiesToEven); break;
                case Instruction::FMul: Result.multiply(RVal, APFloat::rmNearestTiesToEven); break;
                case Instruction::FDiv: Result.divide(RVal, APFloat::rmNearestTiesToEven); break;
                default: return nullptr;
            }
            return ConstantFP::get(BO->getContext(), Result);
        }

        return nullptr;
    }

    // Plegar identidades algebraicas
    static Value* foldAlgebraicIdentities(BinaryOperator* BO) {
        Value* L = BO->getOperand(0);
        Value* R = BO->getOperand(1);

        ConstantInt* CI_R = dyn_cast<ConstantInt>(R);
        ConstantFP* CF_R = dyn_cast<ConstantFP>(R);

        // x + 0 = x
        if (BO->getOpcode() == Instruction::Add && CI_R && CI_R->isZero()) return L;
        // x - 0 = x
        if (BO->getOpcode() == Instruction::Sub && CI_R && CI_R->isZero()) return L;
        // x * 1 = x
        if (BO->getOpcode() == Instruction::Mul && CI_R && CI_R->isOne()) return L;
        // x * 0 = 0
        if (BO->getOpcode() == Instruction::Mul && CI_R && CI_R->isZero()) 
            return ConstantInt::get(BO->getType(), 0);
        // x / 1 = x
        if (BO->getOpcode() == Instruction::SDiv && CI_R && CI_R->isOne()) return L;

        // Float identities
        if (CF_R) {
            const APFloat& RVal = CF_R->getValueAPF();
            if ((BO->getOpcode() == Instruction::FAdd || BO->getOpcode() == Instruction::FSub) && RVal.isZero()) return L;
            if (BO->getOpcode() == Instruction::FMul && RVal.isExactlyValue(1.0)) return L;
            if (BO->getOpcode() == Instruction::FMul && RVal.isZero()) 
                return ConstantFP::get(BO->getContext(), RVal);
        }
        return nullptr;
    }

    // Plegar comparaciones
    static Value* foldComparison(CmpInst* Cmp) {
        Value* L = Cmp->getOperand(0);
        Value* R = Cmp->getOperand(1);

        if (auto* ICI = dyn_cast<ICmpInst>(Cmp)) {
            if (auto* CI_L = dyn_cast<ConstantInt>(L)) {
                if (auto* CI_R = dyn_cast<ConstantInt>(R)) {
                    bool result = false;
                    APInt LVal = CI_L->getValue();
                    APInt RVal = CI_R->getValue();
                    switch (ICI->getPredicate()) {
                        case ICmpInst::ICMP_EQ:  result = LVal == RVal; break;
                        case ICmpInst::ICMP_NE:  result = LVal != RVal; break;
                        case ICmpInst::ICMP_SLT: result = LVal.slt(RVal); break;
                        case ICmpInst::ICMP_SLE: result = LVal.sle(RVal); break;
                        case ICmpInst::ICMP_SGT: result = LVal.sgt(RVal); break;
                        case ICmpInst::ICMP_SGE: result = LVal.sge(RVal); break;
                        default: return nullptr;
                    }
                    return ConstantInt::get(Type::getInt1Ty(Cmp->getContext()), result);
                }
            }
        }

        if (auto* FCI = dyn_cast<FCmpInst>(Cmp)) {
            if (auto* CF_L = dyn_cast<ConstantFP>(L)) {
                if (auto* CF_R = dyn_cast<ConstantFP>(R)) {
                    bool result = false;
                    const APFloat& LVal = CF_L->getValueAPF();
                    const APFloat& RVal = CF_R->getValueAPF();
                    switch (FCI->getPredicate()) {
                        case FCmpInst::FCMP_OEQ: result = (LVal.compare(RVal) == APFloat::cmpEqual); break;
                        case FCmpInst::FCMP_ONE: result = (LVal.compare(RVal) != APFloat::cmpEqual); break;
                        case FCmpInst::FCMP_OLT: result = (LVal.compare(RVal) == APFloat::cmpLessThan); break;
                        case FCmpInst::FCMP_OLE: result = (LVal.compare(RVal) == APFloat::cmpLessThan || LVal.compare(RVal) == APFloat::cmpEqual); break;
                        case FCmpInst::FCMP_OGT: result = (LVal.compare(RVal) == APFloat::cmpGreaterThan); break;
                        case FCmpInst::FCMP_OGE: result = (LVal.compare(RVal) == APFloat::cmpGreaterThan || LVal.compare(RVal) == APFloat::cmpEqual); break;
                        default: return nullptr;
                    }
                    return ConstantInt::get(Type::getInt1Ty(Cmp->getContext()), result);
                }
            }
        }
        return nullptr;
    }

    // Plegar casts
    static Value* foldCast(CastInst* Cast) {
        Value* Op = Cast->getOperand(0);
        if (Cast->getOpcode() == Instruction::SIToFP) {
            if (ConstantInt* CI = dyn_cast<ConstantInt>(Op)) {
                return ConstantFP::get(Cast->getType(), CI->getSExtValue());
            }
        }
        if (Cast->getOpcode() == Instruction::FPToSI) {
            if (ConstantFP* CF = dyn_cast<ConstantFP>(Op)) {
                return ConstantInt::get(Cast->getType(), (int64_t)CF->getValueAPF().convertToDouble());
            }
        }
        return nullptr;
    }
};

#endif // CONSTANT_FOLDING_H
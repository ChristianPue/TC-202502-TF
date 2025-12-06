#ifndef LOOP_OPTIMIZER_H
#define LOOP_OPTIMIZER_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/CFG.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/ADT/MapVector.h"
#include <vector>
#include <set>

using namespace llvm;

class LoopOptimizer {
private:
    // Estructura para representar un bucle simple
    struct SimpleLoop {
        BasicBlock* header;      // Bloque de condición
        BasicBlock* body;        // Bloque del cuerpo
        BasicBlock* exit;        // Bloque de salida
        PHINode* inductionVar;   // Variable de inducción (si existe)
    };

    // Helper para detectar bucles (evita duplicar código)
    static std::vector<SimpleLoop> findLoops(Function& F) {
        std::vector<SimpleLoop> loops;
        for (BasicBlock& BB : F) {
            if (auto* BI = dyn_cast<BranchInst>(BB.getTerminator())) {
                if (BI->isConditional()) {
                    BasicBlock* trueBranch = BI->getSuccessor(0);
                    BasicBlock* falseBranch = BI->getSuccessor(1);
                    
                    // Buscar backedge (salto hacia atrás desde el body al header)
                    for (BasicBlock* pred : predecessors(&BB)) {
                        if (pred == trueBranch) {
                            SimpleLoop loop;
                            loop.header = &BB;
                            loop.body = trueBranch;
                            loop.exit = falseBranch;
                            loop.inductionVar = nullptr;
                            loops.push_back(loop);
                        }
                    }
                }
            }
        }
        return loops;
    }

public:
    // Aplica optimizaciones de bucles a una función
    static bool runOnFunction(Function& F) {
        bool modified = false;
        
        // Buscar bucles una sola vez por pasada
        std::vector<SimpleLoop> loops = findLoops(F);

        // 1. Optimizaciones simples (Loop Unrolling stub / Strength Reduction stub)
        for (SimpleLoop& loop : loops) {
            modified |= optimizeLoop(loop);
        }
        
        // 2. Mover código invariante (LICM)
        for (SimpleLoop& loop : loops) {
            modified |= hoistInvariantCode(loop);
        }
        
        return modified;
    }

private:
    static bool optimizeLoop(SimpleLoop& loop) {
        bool modified = false;
        modified |= unrollLoopIfPossible(loop);
        modified |= strengthReduction(loop);
        return modified;
    }

    // Desenrollar bucle si tiene número constante y pequeño de iteraciones
    static bool unrollLoopIfPossible(SimpleLoop& loop) {
        // 1. Requisitos previos
        if (!loop.inductionVar || !loop.header || !loop.body || !loop.exit) return false;

        // 2. Analizar la condición de salida
        auto* branch = dyn_cast<BranchInst>(loop.header->getTerminator());
        if (!branch || !branch->isConditional()) return false;

        auto* cmp = dyn_cast<ICmpInst>(branch->getCondition());
        if (!cmp) return false;

        // Buscamos comparaciones tipo: i < Constante
        Value* op0 = cmp->getOperand(0);
        Value* op1 = cmp->getOperand(1);
        ConstantInt* tripCountConst = nullptr;

        if (op0 == loop.inductionVar && isa<ConstantInt>(op1)) {
            tripCountConst = cast<ConstantInt>(op1);
        } else {
            return false; 
        }

        // 3. Determinar número de iteraciones
        int64_t iterations = tripCountConst->getSExtValue();

        // Solo desenrollamos bucles pequeños (ej: hasta 4 iteraciones)
        if (iterations <= 0 || iterations > 4) return false;

        // 4. Identificar el Preheader
        BasicBlock* preheader = nullptr;
        for (BasicBlock* pred : predecessors(loop.header)) {
            if (pred != loop.body) {
                preheader = pred;
                break;
            }
        }
        if (!preheader) return false;

        // 5. EJECUTAR UNROLLING
        Instruction* insertPoint = preheader->getTerminator();

        for (int64_t k = 0; k < iterations; ++k) {
            ValueToValueMapTy VMap;

            // Mapear la variable de inducción al valor constante 'k'
            VMap[loop.inductionVar] = ConstantInt::get(loop.inductionVar->getType(), k);

            for (Instruction& I : *loop.body) {
                if (I.isTerminator()) continue; 

                Instruction* cloned = I.clone();
                
                RemapInstruction(cloned, VMap, RF_NoModuleLevelChanges | RF_IgnoreMissingLocals);
                
                // CORRECCIÓN: Usar getIterator()
                cloned->insertBefore(insertPoint->getIterator());
                
                VMap[&I] = cloned;
            }
        }

        // 6. Conectar preheader directamente al exit
        insertPoint->eraseFromParent();
        BranchInst::Create(loop.exit, preheader);

        return true;
    }

    // Reducción de fuerza: Convertir Mul por potencia de 2 en Shift Left
    static bool strengthReduction(SimpleLoop& loop) {
        bool modified = false;

        // Usamos un iterador manual para evitar problemas si modificamos la lista
        for (auto it = loop.body->begin(); it != loop.body->end(); ) {
            Instruction& I = *it++; // Avanzamos el iterador antes de procesar

            if (auto* Mul = dyn_cast<BinaryOperator>(&I)) {
                if (Mul->getOpcode() == Instruction::Mul) {
                    Value* op0 = Mul->getOperand(0);
                    Value* op1 = Mul->getOperand(1);
                    ConstantInt* constOp = nullptr;
                    Value* varOp = nullptr;

                    // 1. Identificar cuál operando es la constante
                    if (isa<ConstantInt>(op0)) {
                        constOp = cast<ConstantInt>(op0);
                        varOp = op1;
                    } else if (isa<ConstantInt>(op1)) {
                        constOp = cast<ConstantInt>(op1);
                        varOp = op0;
                    }

                    // 2. Verificar si es potencia de 2 (ej: 2, 4, 8, 16...)
                    if (constOp && constOp->getValue().isPowerOf2()) {
                        // Obtenemos el valor (ej: 8)
                        uint64_t val = constOp->getZExtValue();
                        
                        // Ignoramos x*1 (identidad) y x*0 (ya lo maneja ConstantFolding)
                        if (val > 1) { 
                            // Calculamos log2 para saber el shift (ej: log2(8) = 3)
                            unsigned shiftAmount = constOp->getValue().logBase2();
                            
                            // 3. Crear instrucción Shift Left (<<)
                            // Inserta la nueva instrucción justo antes de la multiplicación
                            Instruction* shl = BinaryOperator::CreateShl(
                                varOp, 
                                ConstantInt::get(Mul->getType(), shiftAmount),
                                "shl_strength_red",
                                Mul->getIterator() 
                            );
                            
                            // 4. Reemplazar usos
                            Mul->replaceAllUsesWith(shl);
                            modified = true;
                            
                            // Nota: No borramos 'Mul' aquí para no romper el iterador.
                            // El pase de DeadCodeElimination lo limpiará después.
                        }
                    }
                }
            }
        }
        return modified;
    }

    // Mover instrucciones invariantes fuera del bucle
    static bool hoistInvariantCode(SimpleLoop& loop) {
        bool modified = false;
        std::vector<Instruction*> toHoist;
        std::set<Value*> loopInvariant;

        bool changed = true;
        while (changed) {
            changed = false;
            for (Instruction& I : *loop.body) {
                if (loopInvariant.count(&I)) continue;
                if (I.mayHaveSideEffects() || I.isTerminator()) continue;

                bool allOperandsInvariant = true;
                for (Use& U : I.operands()) {
                    Value* Op = U.get();
                    if (isa<Constant>(Op)) continue;
                    if (auto* OpInst = dyn_cast<Instruction>(Op)) {
                        if (OpInst->getParent() != loop.body && OpInst->getParent() != loop.header) 
                            continue;
                    }
                    if (loopInvariant.count(Op)) continue;

                    allOperandsInvariant = false;
                    break;
                }

                if (allOperandsInvariant) {
                    loopInvariant.insert(&I);
                    toHoist.push_back(&I);
                    changed = true;
                    modified = true;
                }
            }
        }

        // Mover al preheader
        if (!toHoist.empty()) {
            BasicBlock* preheader = nullptr;
            for (BasicBlock* pred : predecessors(loop.header)) {
                if (pred != loop.body) {
                    preheader = pred;
                    break;
                }
            }

            if (preheader) {
                Instruction* insertPoint = preheader->getTerminator();
                for (Instruction* I : toHoist) {
                    I->moveBefore(insertPoint->getIterator());
                }
            }
        }

        return modified;
    }
};

#endif // LOOP_OPTIMIZER_H
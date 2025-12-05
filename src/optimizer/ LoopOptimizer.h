#ifndef LOOP_OPTIMIZER_H
#define LOOP_OPTIMIZER_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/LoopInfo.h"
#include <vector>
#include <set>

using namespace llvm;

class LoopOptimizer {
public:
    // Aplica optimizaciones de bucles a una función
    static bool runOnFunction(Function& F) {
        bool modified = false;
        
        // Detectar bucles simples manualmente
        modified |= optimizeSimpleLoops(F);
        
        // Mover código invariante fuera de bucles
        modified |= loopInvariantCodeMotion(F);
        
        return modified;
    }

private:
    // Estructura para representar un bucle simple
    struct SimpleLoop {
        BasicBlock* header;      // Bloque de condición
        BasicBlock* body;        // Bloque del cuerpo
        BasicBlock* exit;        // Bloque de salida
        PHINode* inductionVar;   // Variable de inducción (si existe)
    };

    // Detectar y optimizar bucles simples
    static bool optimizeSimpleLoops(Function& F) {
        bool modified = false;
        std::vector<SimpleLoop> loops;

        // Detectar bucles simples
        for (BasicBlock& BB : F) {
            if (auto* BI = dyn_cast<BranchInst>(BB.getTerminator())) {
                if (BI->isConditional()) {
                    // Verificar si hay un backedge (salto hacia atrás)
                    BasicBlock* trueBranch = BI->getSuccessor(0);
                    BasicBlock* falseBranch = BI->getSuccessor(1);
                    
                    // Patrón: header -> body -> header (bucle while)
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

        // Optimizar cada bucle detectado
        for (SimpleLoop& loop : loops) {
            modified |= optimizeLoop(loop);
        }

        return modified;
    }

    // Optimizar un bucle específico
    static bool optimizeLoop(SimpleLoop& loop) {
        bool modified = false;

        // 1. Desenrollado de bucles con iteraciones constantes
        modified |= unrollLoopIfPossible(loop);

        // 2. Reducción de fuerza (convertir multiplicaciones en sumas)
        modified |= strengthReduction(loop);

        return modified;
    }

    // Desenrollar bucle si tiene número constante de iteraciones
    static bool unrollLoopIfPossible(SimpleLoop& loop) {
        // Por simplicidad, solo detectamos bucles muy simples
        // En un compilador real, esto sería más complejo
        
        // Verificar si la condición del bucle es constante
        if (auto* BI = dyn_cast<BranchInst>(loop.header->getTerminator())) {
            if (auto* Cmp = dyn_cast<ICmpInst>(BI->getCondition())) {
                // Verificar si podemos determinar el número de iteraciones
                // Por ahora, solo lo marcamos como posible optimización
                return false; // No implementado completamente
            }
        }

        return false;
    }

    // Reducción de fuerza: i * c -> suma acumulativa
    static bool strengthReduction(SimpleLoop& loop) {
        bool modified = false;
        std::vector<Instruction*> toReplace;

        // Buscar multiplicaciones por constantes dentro del bucle
        for (Instruction& I : *loop.body) {
            if (auto* Mul = dyn_cast<BinaryOperator>(&I)) {
                if (Mul->getOpcode() == Instruction::Mul) {
                    // Verificar si uno de los operandos es constante
                    if (isa<ConstantInt>(Mul->getOperand(1))) {
                        // Marcar para optimización
                        // En un caso real, reemplazaríamos con suma incremental
                        // Por ahora solo lo detectamos
                    }
                }
            }
        }

        return modified;
    }

    // Mover código invariante fuera del bucle (LICM)
    static bool loopInvariantCodeMotion(Function& F) {
        bool modified = false;
        std::vector<SimpleLoop> loops;

        // Detectar bucles
        for (BasicBlock& BB : F) {
            if (auto* BI = dyn_cast<BranchInst>(BB.getTerminator())) {
                if (BI->isConditional()) {
                    BasicBlock* trueBranch = BI->getSuccessor(0);
                    
                    // Verificar backedge
                    for (BasicBlock* pred : predecessors(&BB)) {
                        if (pred == trueBranch) {
                            SimpleLoop loop;
                            loop.header = &BB;
                            loop.body = trueBranch;
                            loops.push_back(loop);
                        }
                    }
                }
            }
        }

        // Para cada bucle, mover instrucciones invariantes
        for (SimpleLoop& loop : loops) {
            modified |= hoistInvariantCode(loop);
        }

        return modified;
    }

    // Mover instrucciones invariantes fuera del bucle
    static bool hoistInvariantCode(SimpleLoop& loop) {
        bool modified = false;
        std::vector<Instruction*> toHoist;
        std::set<Value*> loopInvariant;

        // Primera pasada: identificar valores invariantes
        bool changed = true;
        while (changed) {
            changed = false;
            for (Instruction& I : *loop.body) {
                // Saltar instrucciones que ya sabemos que son invariantes
                if (loopInvariant.find(&I) != loopInvariant.end()) {
                    continue;
                }

                // No mover instrucciones con efectos secundarios
                if (I.mayHaveSideEffects() || I.isTerminator()) {
                    continue;
                }

                // Verificar si todos los operandos son invariantes
                bool allOperandsInvariant = true;
                for (Use& U : I.operands()) {
                    Value* Op = U.get();
                    
                    // Constantes son invariantes
                    if (isa<Constant>(Op)) {
                        continue;
                    }

                    // Instrucciones fuera del bucle son invariantes
                    if (auto* OpInst = dyn_cast<Instruction>(Op)) {
                        if (OpInst->getParent() != loop.body && 
                            OpInst->getParent() != loop.header) {
                            continue;
                        }
                    }

                    // Ya marcadas como invariantes
                    if (loopInvariant.find(Op) != loopInvariant.end()) {
                        continue;
                    }

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

        // Segunda pasada: mover instrucciones al preheader
        if (!toHoist.empty()) {
            // Buscar o crear un preheader (bloque antes del header del bucle)
            BasicBlock* preheader = nullptr;
            for (BasicBlock* pred : predecessors(loop.header)) {
                if (pred != loop.body) {
                    preheader = pred;
                    break;
                }
            }

            if (preheader) {
                // Mover instrucciones al final del preheader (antes del terminador)
                Instruction* insertPoint = preheader->getTerminator();
                
                for (Instruction* I : toHoist) {
                    I->moveBefore(insertPoint);
                }
            }
        }

        return modified;
    }

    // Eliminar variables de inducción redundantes
    static bool eliminateRedundantInductionVars(SimpleLoop& loop) {
        // Esta optimización identifica múltiples variables que cambian
        // en sincronía y elimina las redundantes
        // Implementación simplificada
        return false;
    }

    // Interchange de bucles anidados (mejorar localidad de caché)
    static bool loopInterchange(Function& F) {
        // Intercambiar bucles anidados cuando mejora el acceso a memoria
        // Requiere análisis de dependencias más complejo
        return false;
    }
};

#endif // LOOP_OPTIMIZER_H
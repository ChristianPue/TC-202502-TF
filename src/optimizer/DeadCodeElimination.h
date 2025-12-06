#ifndef DEAD_CODE_ELIMINATION_H
#define DEAD_CODE_ELIMINATION_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include <vector>
#include <set>
#include <map>

using namespace llvm;

class DeadCodeElimination {
public:
    // Aplica eliminación de código muerto a una función
    static bool runOnFunction(Function& F) {
        bool modified = false;
        bool changed = true;
        
        // Ejecutar en bucle hasta que no haya más cambios (convergencia)
        // Ojo: Para compiladores simples, una sola pasada suele bastar, 
        // pero el bucle asegura limpieza total.

        int passCount = 0;
        while (changed && passCount < 10) { // Límite de seguridad
            changed = false;

            // 1. Simplificar ramas constantes (if (true) ...)
            // Esto suele desconectar bloques, haciéndolos inalcanzables.
            changed |= simplifyBranches(F);

            // 2. Eliminar bloques inalcanzables
            changed |= removeUnreachableBlocks(F);

            // 3. Eliminar instrucciones sin uso
            changed |= removeDeadInstructions(F);

            // 4. Eliminar stores inútiles
            changed |= removeDeadStores(F);

            if (changed) modified = true;
            passCount++;
        }
        
        return modified;
    }

private:
    // Detectar bloques con ramas condicionales constantes
    static bool simplifyBranches(Function& F) {
        bool modified = false;
        std::vector<BranchInst*> toSimplify;

        for (BasicBlock& BB : F) {
            if (auto* BI = dyn_cast<BranchInst>(BB.getTerminator())) {
                if (BI->isConditional()) {
                    if (isa<ConstantInt>(BI->getCondition())) {
                        toSimplify.push_back(BI);
                        modified = true;
                    }
                }
            }
        }

        for (BranchInst* BI : toSimplify) {
            ConstantInt* CI = cast<ConstantInt>(BI->getCondition());
            BasicBlock* target = CI->isOne() ? BI->getSuccessor(0) : BI->getSuccessor(1);
            
            // Reemplazar con salto incondicional al target correcto
            BranchInst::Create(target, BI->getIterator());
            BI->eraseFromParent();
        }

        return modified;
    }

    // Eliminar bloques básicos inalcanzables
    static bool removeUnreachableBlocks(Function& F) {
        bool modified = false;
        std::set<BasicBlock*> reachable;
        std::vector<BasicBlock*> worklist;

        BasicBlock* entry = &F.getEntryBlock();
        reachable.insert(entry);
        worklist.push_back(entry);

        while (!worklist.empty()) {
            BasicBlock* BB = worklist.back();
            worklist.pop_back();

            for (BasicBlock* Succ : successors(BB)) {
                if (reachable.insert(Succ).second) {
                    worklist.push_back(Succ);
                }
            }
        }

        std::vector<BasicBlock*> toRemove;
        for (BasicBlock& BB : F) {
            if (reachable.find(&BB) == reachable.end()) {
                toRemove.push_back(&BB);
                modified = true;
            }
        }

        for (BasicBlock* BB : toRemove) {
            // Antes de borrar el bloque, debemos asegurarnos de que nadie lo referencie
            // (Drop all references). En LLVM simple sin PHI nodes complejos esto suele funcionar,
            // pero lo correcto es usar DeleteDeadBlock de Utils. 
            // Como estamos manual:
            BB->dropAllReferences(); 
            BB->eraseFromParent();
        }

        return modified;
    }

    // Eliminar instrucciones que no tienen usos
    static bool removeDeadInstructions(Function& F) {
        bool modified = false;
        bool changed = true;
        
        // Repetir mientras encontremos instrucciones muertas (cadenas de def-use)
        while (changed) {
            changed = false;
            std::vector<Instruction*> toRemove;

            for (BasicBlock& BB : F) {
                for (Instruction& I : BB) {
                    if (I.mayHaveSideEffects() || I.isTerminator()) continue;

                    if (I.use_empty()) {
                        toRemove.push_back(&I);
                        changed = true;
                        modified = true;
                    }
                }
            }

            for (Instruction* I : toRemove) {
                I->eraseFromParent();
            }
        }

        return modified;
    }

    // Eliminar stores a variables que nunca son leídas (Dead Store Elimination básico)
    static bool removeDeadStores(Function& F) {
        bool modified = false;
        std::vector<Instruction*> toRemove;
        std::map<AllocaInst*, std::vector<Instruction*>> allocaUses;

        // Recolectar usos
        for (BasicBlock& BB : F) {
            for (Instruction& I : BB) {
                if (auto* SI = dyn_cast<StoreInst>(&I)) {
                    if (auto* AI = dyn_cast<AllocaInst>(SI->getPointerOperand())) {
                        allocaUses[AI].push_back(SI);
                    }
                } else if (auto* LI = dyn_cast<LoadInst>(&I)) {
                    if (auto* AI = dyn_cast<AllocaInst>(LI->getPointerOperand())) {
                        allocaUses[AI].push_back(LI);
                    }
                }
            }
        }

        // Analizar allocas
        for (auto& pair : allocaUses) {
            // AllocaInst* AI = pair.first; // No usado en esta lógica simple
            std::vector<Instruction*>& uses = pair.second;

            bool hasLoad = false;
            for (Instruction* I : uses) {
                if (isa<LoadInst>(I)) {
                    hasLoad = true;
                    break;
                }
            }

            // Si la variable NUNCA se lee, todos sus stores son inútiles
            if (!hasLoad) {
                for (Instruction* I : uses) {
                    if (auto* SI = dyn_cast<StoreInst>(I)) {
                        toRemove.push_back(SI);
                        modified = true;
                    }
                }
            }
        }

        for (Instruction* I : toRemove) {
            I->eraseFromParent();
        }

        return modified;
    }
};

#endif // DEAD_CODE_ELIMINATION_H
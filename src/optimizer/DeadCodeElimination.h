#ifndef DEAD_CODE_ELIMINATION_H
#define DEAD_CODE_ELIMINATION_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include <vector>
#include <set>

using namespace llvm;

class DeadCodeElimination {
public:
    // Aplica eliminación de código muerto a una función
    static bool runOnFunction(Function& F) {
        bool modified = false;
        
        // Paso 1: Eliminar instrucciones sin usos
        modified |= removeDeadInstructions(F);
        
        // Paso 2: Eliminar bloques básicos inalcanzables
        modified |= removeUnreachableBlocks(F);
        
        // Paso 3: Eliminar stores a variables nunca leídas
        modified |= removeDeadStores(F);
        
        return modified;
    }

private:
    // Eliminar instrucciones que no tienen usos
    static bool removeDeadInstructions(Function& F) {
        bool modified = false;
        std::vector<Instruction*> toRemove;

        for (BasicBlock& BB : F) {
            for (Instruction& I : BB) {
                // No eliminar instrucciones con efectos secundarios
                if (I.mayHaveSideEffects() || I.isTerminator()) {
                    continue;
                }

                // Si no tiene usos, marcar para eliminación
                if (I.use_empty()) {
                    toRemove.push_back(&I);
                    modified = true;
                }
            }
        }

        // Eliminar instrucciones muertas
        for (Instruction* I : toRemove) {
            I->eraseFromParent();
        }

        return modified;
    }

    // Eliminar bloques básicos inalcanzables
    static bool removeUnreachableBlocks(Function& F) {
        bool modified = false;
        std::set<BasicBlock*> reachable;
        std::vector<BasicBlock*> worklist;

        // Comenzar desde el bloque de entrada
        BasicBlock* entry = &F.getEntryBlock();
        reachable.insert(entry);
        worklist.push_back(entry);

        // BFS para encontrar todos los bloques alcanzables
        while (!worklist.empty()) {
            BasicBlock* BB = worklist.back();
            worklist.pop_back();

            for (BasicBlock* Succ : successors(BB)) {
                if (reachable.insert(Succ).second) {
                    worklist.push_back(Succ);
                }
            }
        }

        // Eliminar bloques inalcanzables
        std::vector<BasicBlock*> toRemove;
        for (BasicBlock& BB : F) {
            if (reachable.find(&BB) == reachable.end()) {
                toRemove.push_back(&BB);
                modified = true;
            }
        }

        for (BasicBlock* BB : toRemove) {
            BB->eraseFromParent();
        }

        return modified;
    }

    // Eliminar stores a variables que nunca son leídas
    static bool removeDeadStores(Function& F) {
        bool modified = false;
        std::vector<Instruction*> toRemove;

        // Mapa de allocas y sus loads/stores
        std::map<AllocaInst*, std::vector<Instruction*>> allocaUses;

        // Primera pasada: recolectar información
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

        // Segunda pasada: eliminar stores sin loads posteriores
        for (auto& pair : allocaUses) {
            AllocaInst* AI = pair.first;
            std::vector<Instruction*>& uses = pair.second;

            // Si solo hay stores y no hay loads, eliminar stores
            bool hasLoad = false;
            for (Instruction* I : uses) {
                if (isa<LoadInst>(I)) {
                    hasLoad = true;
                    break;
                }
            }

            if (!hasLoad) {
                for (Instruction* I : uses) {
                    if (auto* SI = dyn_cast<StoreInst>(I)) {
                        toRemove.push_back(SI);
                        modified = true;
                    }
                }
            }
        }

        // Eliminar stores muertos
        for (Instruction* I : toRemove) {
            I->eraseFromParent();
        }

        return modified;
    }

    // Detectar bloques con ramas condicionales constantes
    static bool simplifyBranches(Function& F) {
        bool modified = false;
        std::vector<BranchInst*> toSimplify;

        for (BasicBlock& BB : F) {
            if (auto* BI = dyn_cast<BranchInst>(BB.getTerminator())) {
                if (BI->isConditional()) {
                    if (auto* CI = dyn_cast<ConstantInt>(BI->getCondition())) {
                        toSimplify.push_back(BI);
                        modified = true;
                    }
                }
            }
        }

        // Convertir ramas condicionales constantes en saltos directos
        for (BranchInst* BI : toSimplify) {
            ConstantInt* CI = cast<ConstantInt>(BI->getCondition());
            BasicBlock* target = CI->isOne() ? BI->getSuccessor(0) : BI->getSuccessor(1);
            BasicBlock* deadBranch = CI->isOne() ? BI->getSuccessor(1) : BI->getSuccessor(0);
            
            // Reemplazar con salto incondicional
            BranchInst::Create(target, BI);
            BI->eraseFromParent();
            
            // El bloque muerto se eliminará en removeUnreachableBlocks
        }

        return modified;
    }
};

#endif // DEAD_CODE_ELIMINATION_H
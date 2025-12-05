#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"

#include "ConstantFolding.h"
#include "DeadCodeElimination.h"
#include "LoopOptimizer.h"

#include <iostream>
#include <memory>

using namespace llvm;

class Optimizer {
private:
    Module* module;
    int optimizationLevel; // 0=ninguno, 1=básico, 2=agresivo

public:
    Optimizer(Module* M, int level = 1) 
        : module(M), optimizationLevel(level) {}

    // Ejecutar todas las optimizaciones
    void optimize() {
        if (optimizationLevel == 0) {
            std::cout << "[Optimizer] Optimizaciones deshabilitadas." << std::endl;
            return;
        }

        std::cout << "[Optimizer] Iniciando optimizaciones (nivel " 
                  << optimizationLevel << ")..." << std::endl;

        bool modified = true;
        int iteration = 0;
        const int maxIterations = 5; // Evitar bucles infinitos

        // Ejecutar pases hasta que no haya más cambios
        while (modified && iteration < maxIterations) {
            modified = false;
            iteration++;

            std::cout << "  [Iteración " << iteration << "]" << std::endl;

            // Pase 1: Plegado de constantes
            if (runConstantFolding()) {
                std::cout << "    ✓ Constant Folding aplicado" << std::endl;
                modified = true;
            }

            // Pase 2: Eliminación de código muerto
            if (runDeadCodeElimination()) {
                std::cout << "    ✓ Dead Code Elimination aplicado" << std::endl;
                modified = true;
            }

            // Pase 3: Optimizaciones de bucles (solo en nivel 2)
            if (optimizationLevel >= 2 && runLoopOptimizations()) {
                std::cout << "    ✓ Loop Optimizations aplicado" << std::endl;
                modified = true;
            }

            if (!modified) {
                std::cout << "    → Sin más optimizaciones posibles" << std::endl;
            }
        }

        std::cout << "[Optimizer] Optimizaciones completadas en " 
                  << iteration << " iteración(es)." << std::endl;
    }

    // Ejecutar optimizaciones LLVM estándar (opcional)
    void runStandardPasses() {
        legacy::PassManager PM;

        // Pases básicos de LLVM
        PM.add(createPromoteMemoryToRegisterPass());  // mem2reg
        PM.add(createInstructionCombiningPass());     // instcombine
        PM.add(createReassociatePass());              // reassociate
        PM.add(createGVNPass());                      // GVN
        PM.add(createCFGSimplificationPass());        // simplifycfg

        if (optimizationLevel >= 2) {
            PM.add(createLoopSimplifyPass());
            PM.add(createLICMPass());
            PM.add(createIndVarSimplifyPass());
        }

        std::cout << "[Optimizer] Ejecutando pases estándar de LLVM..." << std::endl;
        PM.run(*module);
        std::cout << "[Optimizer] Pases estándar completados." << std::endl;
    }

    // Mostrar estadísticas de optimización
    void printStats() {
        int totalInstructions = 0;
        int totalBlocks = 0;
        int totalFunctions = 0;

        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            
            totalFunctions++;
            for (BasicBlock& BB : F) {
                totalBlocks++;
                for (Instruction& I : BB) {
                    totalInstructions++;
                }
            }
        }

        std::cout << "\n[Estadísticas del módulo]" << std::endl;
        std::cout << "  Funciones:     " << totalFunctions << std::endl;
        std::cout << "  Bloques:       " << totalBlocks << std::endl;
        std::cout << "  Instrucciones: " << totalInstructions << std::endl;
    }

private:
    // Aplicar plegado de constantes
    bool runConstantFolding() {
        bool modified = false;
        
        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            modified |= ConstantFolding::runOnFunction(F);
        }
        
        return modified;
    }

    // Aplicar eliminación de código muerto
    bool runDeadCodeElimination() {
        bool modified = false;
        
        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            modified |= DeadCodeElimination::runOnFunction(F);
        }
        
        return modified;
    }

    // Aplicar optimizaciones de bucles
    bool runLoopOptimizations() {
        bool modified = false;
        
        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            modified |= LoopOptimizer::runOnFunction(F);
        }
        
        return modified;
    }
};

// Helper function para crear optimizador desde CodeGenerator
inline std::unique_ptr<Optimizer> createOptimizer(Module* module, int level) {
    return std::make_unique<Optimizer>(module, level);
}

#endif // OPTIMIZER_H
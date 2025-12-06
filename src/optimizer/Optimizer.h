#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar/GVN.h"

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
            std::cout << "[Optimizer] Optimizaciones deshabilitadas (-O0)." << std::endl;
            return;
        }

        std::cout << "[Optimizer] Iniciando optimizaciones manuales (nivel " 
                  << optimizationLevel << ")..." << std::endl;

        bool modified = true;
        int iteration = 0;
        const int maxIterations = 5; // Evitar bucles infinitos

        // --- FASE 1: Optimizaciones Manuales (Iterativas) ---
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
                std::cout << "    → Convergencia alcanzada." << std::endl;
            }
        }

        // --- FASE 2: Pases Estándar de LLVM (Opcional, para nivel 2+) ---
        // Esto limpiará lo que nuestras optimizaciones manuales hayan dejado sucio
        if (optimizationLevel >= 2) {
            runStandardPasses();
        }

        std::cout << "[Optimizer] Proceso completado." << std::endl;
        printStats();
    }

    // Ejecutar optimizaciones nativas de LLVM (Legacy Pass Manager)
    void runStandardPasses() {
        std::cout << "[Optimizer] Ejecutando pases nativos de LLVM..." << std::endl;
        
        legacy::PassManager PM;

        // Limpieza básica y canonicalización
        PM.add(createPromoteMemoryToRegisterPass());  // mem2reg (Convierte allocas a registros SSA)
        PM.add(createInstructionCombiningPass());     // instcombine
        PM.add(createReassociatePass());              // reassociate
        PM.add(createCFGSimplificationPass());        // simplifycfg
        PM.add(createGVNPass());                      // GVN

        if (optimizationLevel >= 2) {
            // Optimizaciones de bucles nativas
            PM.add(createLoopSimplifyPass());
            PM.add(createLICMPass());
        }

        PM.run(*module);
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
                // Forma optimizada de contar instrucciones
                totalInstructions += BB.size();
            }
        }

        std::cout << "\n[Estadísticas del módulo]" << std::endl;
        std::cout << "  Funciones:     " << totalFunctions << std::endl;
        std::cout << "  Bloques:       " << totalBlocks << std::endl;
        std::cout << "  Instrucciones: " << totalInstructions << std::endl;
    }

private:
    // Wrappers para las clases estáticas
    bool runConstantFolding() {
        bool modified = false;
        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            modified |= ConstantFolding::runOnFunction(F);
        }
        return modified;
    }

    bool runDeadCodeElimination() {
        bool modified = false;
        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            modified |= DeadCodeElimination::runOnFunction(F);
        }
        return modified;
    }

    bool runLoopOptimizations() {
        bool modified = false;
        for (Function& F : *module) {
            if (F.isDeclaration()) continue;
            modified |= LoopOptimizer::runOnFunction(F);
        }
        return modified;
    }
};

#endif // OPTIMIZER_H
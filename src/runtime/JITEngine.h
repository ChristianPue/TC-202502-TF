#ifndef JIT_ENGINE_H
#define JIT_ENGINE_H

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Transforms/Utils/Cloning.h"

#include "RuntimeSupport.h"

#include <memory>
#include <iostream>
#include <string>

using namespace llvm;

class JITEngine {
private:
    std::unique_ptr<ExecutionEngine> execEngine;
    // No guardamos el Module* como miembro porque el ExecutionEngine se vuelve su dueño
    bool initialized;

public:
    // El JITEngine tomará ownership de un clon del módulo para no afectar al original
    JITEngine(Module* M) : initialized(false) {
        if (!M) {
            std::cerr << "[JIT] Error: Módulo nulo" << std::endl;
            return;
        }

        // Verificar que el módulo sea válido
        if (verifyModule(*M, &errs())) {
            std::cerr << "[JIT] Error: El módulo contiene errores" << std::endl;
            return;
        }

        initializeJIT(M);
    }

    ~JITEngine() {
        // ExecutionEngine se limpia automáticamente y destruye el módulo que posee
    }

    // Ejecutar la función main del módulo
    int execute() {
        if (!initialized) {
            std::cerr << "[JIT] Error: JIT no inicializado" << std::endl;
            return -1;
        }

        RuntimeSupport::printExecutionBanner();

        // Buscar la función main dentro del JIT
        // Nota: Usamos FindFunctionNamed porque el módulo ahora vive dentro del engine
        Function* mainFunc = execEngine->FindFunctionNamed("main");
        if (!mainFunc) {
            std::cerr << "[JIT] Error: No se encontró la función 'main'" << std::endl;
            return -1;
        }

        std::cout << "[JIT] Ejecutando función 'main'...\n" << std::endl;

        // Ejecutar la función
        std::vector<GenericValue> noArgs;
        GenericValue result;

        try {
            result = execEngine->runFunction(mainFunc, noArgs);
        } catch (const std::exception& e) {
            std::cerr << "\n[JIT] Error durante la ejecución: " << e.what() << std::endl;
            return -1;
        }

        // Extraer código de salida
        int exitCode = result.IntVal.getSExtValue();
        
        RuntimeSupport::printExecutionComplete(exitCode);
        
        return exitCode;
    }

    // Verificar si el JIT está listo
    bool isReady() const {
        return initialized && execEngine != nullptr;
    }

private:
    void initializeJIT(Module* sourceModule) {
        // Inicializar el sistema de targets nativos
        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();
        InitializeNativeTargetAsmParser();

        // Cargar símbolos del proceso actual (printf, scanf, etc.)
        sys::DynamicLibrary::LoadLibraryPermanently(nullptr);

        // CLONAR el módulo para que el JIT tenga su propia copia y no destruya la del Driver
        // CloneModule devuelve un unique_ptr
        std::unique_ptr<Module> moduleClone = CloneModule(*sourceModule);

        std::string errStr;
        
        // CORRECCIÓN: Crear el builder correctamente evitando 'Most Vexing Parse'
        // y pasando el unique_ptr del clon.
        EngineBuilder builder(std::move(moduleClone));
        
        builder.setErrorStr(&errStr);
        builder.setEngineKind(EngineKind::JIT);
        
        // Crear ExecutionEngine
        execEngine.reset(builder.create());

        if (!execEngine) {
            std::cerr << "[JIT] Error al crear ExecutionEngine: " << errStr << std::endl;
            return;
        }

        // Finalizar generación de código de objeto
        execEngine->finalizeObject();

        initialized = true;
        std::cout << "[JIT] Motor JIT inicializado correctamente" << std::endl;
    }
};

// Función auxiliar para crear y ejecutar JIT
inline int executeModule(Module* module) {
    if (!module) {
        std::cerr << "Error: Módulo nulo para JIT" << std::endl;
        return -1;
    }

    JITEngine jit(module);
    
    if (!jit.isReady()) {
        std::cerr << "Error: No se pudo inicializar el JIT" << std::endl;
        return -1;
    }

    return jit.execute();
}

#endif // JIT_ENGINE_H
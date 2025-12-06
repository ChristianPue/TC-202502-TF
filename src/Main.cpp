#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "EduCodeLexer.h"
#include "EduCodeParser.h"
#include "Driver.h"
#include "optimizer/Optimizer.h"
#include "runtime/JITEngine.h"
#include "diagram/FlowchartGenerator.h"

using namespace antlr4;

// Función auxiliar para cambiar la extensión del archivo
// Ahora acepta la extensión deseada (ej: ".ll", ".dot")
std::string getOutputFilename(const std::string& inputPath, const std::string& extension) {
    size_t lastDot = inputPath.find_last_of(".");
    if (lastDot == std::string::npos) return inputPath + extension;
    return inputPath.substr(0, lastDot) + extension;
}

// Función para parsear flags de optimización (-O0, -O1, -O2)
int parseOptimizationLevel(int argc, const char* argv[]) {
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-O0") return 0;
        if (arg == "-O1") return 1;
        if (arg == "-O2") return 2;
    }
    return 1; // Por defecto O1
}

// Función para verificar si se debe ejecutar con JIT
bool shouldRunJIT(int argc, const char* argv[]) {
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-run" || arg == "--run" || arg == "-r") {
            return true;
        }
    }
    return false;
}

// Función para verificar si se debe generar diagrama de flujo
bool shouldGenerateDiagram(int argc, const char* argv[]) {
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-diagram" || arg == "--diagram" || arg == "-d") {
            return true;
        }
    }
    return false;
}

int main(int argc, const char* argv[]) {
    // 1. Verificación de argumentos
    if (argc < 2) {
        std::cerr << "Uso: EduCode <archivo_entrada.educ> [opciones]" << std::endl;
        std::cerr << "Opciones:" << std::endl;
        std::cerr << "  -O0  Sin optimizaciones" << std::endl;
        std::cerr << "  -O1  Optimizaciones básicas (por defecto)" << std::endl;
        std::cerr << "  -O2  Optimizaciones agresivas" << std::endl;
        std::cerr << "\nOpciones de ejecución:" << std::endl;
        std::cerr << "  -run|-r   Ejecutar el programa usando JIT" << std::endl;
        std::cerr << "  -diagram|-d  Generar diagrama de flujo (Graphviz DOT)" << std::endl;
        std::cerr << "\nEjemplos:" << std::endl;
        std::cerr << "  ./build/EduCode ./examples/programa.educ              # Compilar a IR" << std::endl;
        std::cerr << "  ./build/EduCode ./examples/programa.educ -O2          # Compilar con optimización" << std::endl;
        std::cerr << "  ./build/EduCode ./examples/programa.educ -run         # Compilar y ejecutar" << std::endl;
        std::cerr << "  ./build/EduCode ./examples/programa.educ -O2 -run     # Optimizar y ejecutar" << std::endl;
        std::cerr << "  ./build/EduCode ./examples/programa.educ -diagram     # Generar diagrama de flujo" << std::endl;
        return 1;
    }

    int optimizationLevel = parseOptimizationLevel(argc, argv);
    
    bool runJIT = shouldRunJIT(argc, argv);

    bool genDiagram = shouldGenerateDiagram(argc, argv);

    std::string inputPath = argv[1];
    
    std::ifstream stream(inputPath);
    
    if (!stream.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << inputPath << std::endl;
        return 1;
    }

    // 2. Configuración de ANTLR
    ANTLRInputStream input(stream);
    EduCodeLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    EduCodeParser parser(&tokens);

    // 3. Parsing
    EduCodeParser::ProgramContext* tree = parser.program();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Error: La compilación se detuvo debido a errores de sintaxis." << std::endl;
        return 1;
    }

    // ==========================================
    // OPCIONAL: GENERACIÓN DE DIAGRAMA DE FLUJO
    // ==========================================
    if (genDiagram) { // Ahora genDiagram ya existe
        std::cout << "\n════════════════════════════════════════" << std::endl;
        std::cout << "  GENERACIÓN DE DIAGRAMA DE FLUJO" << std::endl;
        std::cout << "════════════════════════════════════════" << std::endl;

        std::string dotPath = getOutputFilename(inputPath, ".dot");
        
        try {
            FlowchartGenerator generator;
            generator.generate(tree); 
            
            if (generator.exportDot(dotPath)) { 
                std::cout << "✓ Diagrama generado exitosamente." << std::endl;
                std::cout << "→ Archivo DOT: " << dotPath << std::endl;
                std::cout << "  (Para ver imagen: dot -Tpng " << dotPath << " -o diagrama.png)" << std::endl;
            } else {
                std::cerr << "Error al guardar el archivo DOT." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error generando diagrama: " << e.what() << std::endl;
        }
    }

    // 4. Generación de Código
    std::cout << "\n════════════════════════════════════════" << std::endl;
    std::cout << "  FASE 1: GENERACIÓN DE CÓDIGO LLVM IR" << std::endl;
    std::cout << "════════════════════════════════════════" << std::endl;
    
    Driver driver;
    try {
        driver.visitProgram(tree);
        std::cout << "✓ Generación de IR completada exitosamente." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error durante la generación de código: " << e.what() << std::endl;
        return 1;
    }

    // 5. Optimización del código IR
    std::cout << "\n════════════════════════════════════════" << std::endl;
    std::cout << "  FASE 2: OPTIMIZACIÓN DE CÓDIGO IR" << std::endl;
    std::cout << "════════════════════════════════════════" << std::endl;
    
    // Ahora 'optimizationLevel' ya está declarada
    Optimizer optimizer(driver.getModule(), optimizationLevel);
    optimizer.optimize();
    optimizer.printStats();
    
    // 6. Guardar el archivo .ll resultante
    std::cout << "\n════════════════════════════════════════" << std::endl;
    std::cout << "  EXPORTACIÓN" << std::endl;
    std::cout << "════════════════════════════════════════" << std::endl;
    
    std::string outputPath = getOutputFilename(inputPath, ".ll");
    driver.saveIR(outputPath);
    
    std::cout << "✓ Compilación exitosa." << std::endl;
    std::cout << "→ Código LLVM IR generado en: " << outputPath << std::endl;
    std::cout << "→ Nivel de optimización aplicado: -O" << optimizationLevel << std::endl;
    std::cout << "════════════════════════════════════════\n" << std::endl;

    // 7. Ejecución JIT (OBJETIVO 3) - si se especificó -run
    if (runJIT) {
        int exitCode = executeModule(driver.getModule());
        return exitCode;
    }

    return 0;
}
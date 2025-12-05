#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "EduCodeLexer.h"
#include "EduCodeParser.h"
#include "Driver.h"

using namespace antlr4;

// Función auxiliar para cambiar la extensión del archivo (ej: test.educ -> test.ll)
std::string getOutputFilename(const std::string& inputPath) {
    size_t lastDot = inputPath.find_last_of(".");
    if (lastDot == std::string::npos) return inputPath + ".ll";
    return inputPath.substr(0, lastDot) + ".ll";
}

int main(int argc, const char* argv[]) {
    // 1. Verificación de argumentos
    if (argc < 2) {
        std::cerr << "Uso: EduCode <archivo_entrada.educ>" << std::endl;
        return 1;
    }

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

    // 3. Parsing (comienza desde la regla 'program')
    EduCodeParser::ProgramContext* tree = parser.program();

    // Verificación básica de errores sintácticos
    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Error: La compilación se detuvo debido a errores de sintaxis." << std::endl;
        return 1;
    }

    // 4. Generación de Código (Recorrido del árbol con Driver)
    Driver driver;
    try {
        driver.visitProgram(tree);
    } catch (const std::exception& e) {
        std::cerr << "Error durante la generación de código: " << e.what() << std::endl;
        return 1;
    }

    // 5. Guardar el archivo .ll resultante
    std::string outputPath = getOutputFilename(inputPath);
    driver.saveIR(outputPath);
    
    std::cout << "✓ Compilación exitosa." << std::endl;
    std::cout << "→ Código LLVM IR generado en: " << outputPath << std::endl;

    return 0;
}
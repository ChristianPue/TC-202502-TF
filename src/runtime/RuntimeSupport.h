#ifndef RUNTIME_SUPPORT_H
#define RUNTIME_SUPPORT_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cstdlib>

// Funciones de runtime que serán llamadas desde el código JIT
extern "C" {
    // Wrapper para printf (ya existe en libc, pero por compatibilidad)
    int educode_printf(const char* format, ...) {
        va_list args;
        va_start(args, format);
        int result = vprintf(format, args);
        va_end(args);
        fflush(stdout);
        return result;
    }

    // Wrapper para scanf (ya existe en libc, pero por compatibilidad)
    int educode_scanf(const char* format, ...) {
        va_list args;
        va_start(args, format);
        int result = vscanf(format, args);
        va_end(args);
        return result;
    }

    // Función auxiliar para imprimir strings con salto de línea
    void educode_print_string(const char* str) {
        printf("%s\n", str);
        fflush(stdout);
    }

    // Función auxiliar para imprimir enteros
    void educode_print_int(int val) {
        printf("%d\n", val);
        fflush(stdout);
    }

    // Función auxiliar para imprimir floats
    void educode_print_float(float val) {
        printf("%f\n", (double)val);
        fflush(stdout);
    }

    // Función auxiliar para leer enteros
    int educode_read_int() {
        int val;
        if (scanf("%d", &val) != 1) {
            fprintf(stderr, "Error: Entrada inválida para entero\n");
            return 0;
        }
        return val;
    }

    // Función auxiliar para leer floats
    float educode_read_float() {
        float val;
        if (scanf("%f", &val) != 1) {
            fprintf(stderr, "Error: Entrada inválida para float\n");
            return 0.0f;
        }
        return val;
    }

    // Función para manejar errores de división por cero
    void educode_div_by_zero_error() {
        fprintf(stderr, "Error de ejecución: División por cero\n");
        exit(1);
    }

    // Función para manejar errores de acceso a arrays
    void educode_array_bounds_error(int index, int size) {
        fprintf(stderr, "Error de ejecución: Índice %d fuera de rango [0, %d)\n", index, size);
        exit(1);
    }
}

class RuntimeSupport {
public:
    // Registrar símbolos del runtime en el JIT
    static void registerSymbols() {
        // Las funciones extern "C" ya están disponibles automáticamente
        // Este método se puede usar para registro explícito si es necesario
    }

    // Imprimir mensaje de inicio de ejecución
    static void printExecutionBanner() {
        std::cout << "\n════════════════════════════════════════" << std::endl;
        std::cout << "  FASE 3: EJECUCIÓN JIT" << std::endl;
        std::cout << "════════════════════════════════════════" << std::endl;
    }

    // Imprimir mensaje de finalización
    static void printExecutionComplete(int exitCode) {
        std::cout << "\n════════════════════════════════════════" << std::endl;
        std::cout << "  EJECUCIÓN COMPLETADA" << std::endl;
        std::cout << "════════════════════════════════════════" << std::endl;
        std::cout << "Código de salida: " << exitCode << std::endl;
    }
};

#endif // RUNTIME_SUPPORT_H
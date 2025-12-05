cmake_minimum_required(VERSION 3.30)
project(EduCode)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =====================================
# Paths base
# =====================================
set(MY_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(ANTLR_EXECUTABLE "${MY_BASE_DIR}/antlr-4.13.2-complete.jar")
set(ANTLR_INCLUDE_DIR "/usr/include/antlr4-runtime")
list(APPEND CMAKE_MODULE_PATH ${MY_BASE_DIR})

# =====================================
# ANTLR CONFIG
# =====================================
if(NOT EXISTS "${ANTLR_EXECUTABLE}")
  message(STATUS "Couldn't find: ${ANTLR_EXECUTABLE}")
  file(DOWNLOAD
        "https://www.antlr.org/download/antlr-4.13.2-complete.jar"
        "${ANTLR_EXECUTABLE}"
        STATUS DOWNLOAD_STATUS TIMEOUT 60)
endif()

if(NOT EXISTS "${MY_BASE_DIR}/FindANTLR.cmake")
  message(STATUS "Couldn't find: FindANTLR.cmake")
  set(URL1 "https://raw.githubusercontent.com/antlr/antlr4/")
  set(URL2 "refs/heads/dev/runtime/Cpp/cmake/FindANTLR.cmake")
  file(DOWNLOAD
        "${URL1}${URL2}"
        "${MY_BASE_DIR}/FindANTLR.cmake"
        STATUS DOWNLOAD_STATUS TIMEOUT 60)
endif()

find_package(ANTLR REQUIRED)
message(STATUS "Found ANTLR: ${ANTLR_VERSION}")

file(GLOB G4_FILES "*.g4")
antlr_target(EduCodeGrammar ${G4_FILES} LEXER PARSER VISITOR)

# =====================================
# LLVM CONFIG
# =====================================
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Componentes mínimos y correctos para IR
set(REQ_LLVM LLVM)

# =====================================
# FUENTES DEL PROYECTO (ESTRUCTURA MODULAR)
# =====================================

# Archivos principales
set(MAIN_SOURCES
  Main.cpp
)

# Módulo CodeGen (Objetivo 1: Generación de LLVM IR)
set(CODEGEN_HEADERS
  codegen/SymbolTable.h
  codegen/TypeSystem.h
  codegen/CodeGenerator.h
  codegen/ExpressionGen.h
  codegen/StatementGen.h
)

# Driver (orquestador)
set(DRIVER_HEADERS
  Driver.h
)

# Combinar todas las fuentes
set(ALL_SOURCES
  ${MAIN_SOURCES}
  ${DRIVER_HEADERS}    # <--- Agrega esto
  ${CODEGEN_HEADERS}   # <--- Agrega esto
  ${ANTLR_EduCodeGrammar_CXX_OUTPUTS}
)

# =====================================
# EJECUTABLE
# =====================================
add_executable(EduCode ${ALL_SOURCES})

# =====================================
# INCLUDES y LIBRERÍAS
# =====================================
target_include_directories(EduCode PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}          # Para acceder a Driver.h
  ${CMAKE_CURRENT_SOURCE_DIR}/codegen  # Para acceder a codegen/*.h
  ${ANTLR_INCLUDE_DIR}
  ${ANTLR_EduCodeGrammar_OUTPUT_DIR}
  ${LLVM_INCLUDE_DIRS}
)

target_link_libraries(EduCode PRIVATE
  antlr4-runtime
  ${REQ_LLVM}
)

# =====================================
# CONFIGURACIÓN ADICIONAL
# =====================================

# Mostrar estructura del proyecto al configurar
message(STATUS "==============================================")
message(STATUS "Estructura del proyecto:")
message(STATUS "  CMake:    CMakeLists.txt ")
message(STATUS "  Main:     Main.cpp")
message(STATUS "  Driver:   Driver.h")
message(STATUS "  CodeGen:  codegen/")
message(STATUS "            ├── SymbolTable.h")
message(STATUS "            ├── TypeSystem.h")
message(STATUS "            ├── CodeGenerator.h")
message(STATUS "            ├── ExpressionGen.h")
message(STATUS "            └── StatementGen.h")
message(STATUS "==============================================")

# Opciones de compilación para mejor debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(EduCode PRIVATE -g -O0 -Wall -Wextra)
  message(STATUS "Modo Debug: habilitado (-g -O0)")
endif()

# =====================================
# TARGETS PERSONALIZADOS (OPCIONAL)
# =====================================

# Target para limpiar archivos generados por ANTLR
add_custom_target(clean-antlr
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${ANTLR_EduCodeGrammar_OUTPUT_DIR}
  COMMENT "Limpiando archivos generados por ANTLR..."
)

# Target para compilar y ejecutar un archivo de prueba
add_custom_target(test-compile
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target EduCode
  DEPENDS EduCode
  COMMENT "Compilando EduCode..."
)
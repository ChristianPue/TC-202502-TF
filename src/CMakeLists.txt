cmake_minimum_required(VERSION 3.30)
project(EduCode)

# =====================================
# 1. SETUP DE RUTAS BASE
# =====================================
set(MY_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(ANTLR_EXECUTABLE "${MY_BASE_DIR}/antlr-4.13.2-complete.jar")
set(ANTLR_INCLUDE_DIR "/usr/include/antlr4-runtime")
list(APPEND CMAKE_MODULE_PATH ${MY_BASE_DIR})

# =====================================
# 2. CONFIGURACIÓN ANTLR
# =====================================
if(NOT EXISTS "${ANTLR_EXECUTABLE}")
  message(STATUS "Downloading ANTLR jar...")
  file(DOWNLOAD
    "https://www.antlr.org/download/antlr-4.13.2-complete.jar"
    "${ANTLR_EXECUTABLE}"
    STATUS DOWNLOAD_STATUS TIMEOUT 60)
endif()

if(NOT EXISTS "${MY_BASE_DIR}/FindANTLR.cmake")
  message(STATUS "Downloading FindANTLR.cmake...")
  file(DOWNLOAD
    "https://raw.githubusercontent.com/antlr/antlr4/master/runtime/Cpp/cmake/FindANTLR.cmake"
    "${MY_BASE_DIR}/FindANTLR.cmake"
    STATUS DOWNLOAD_STATUS TIMEOUT 60)
endif()

find_package(ANTLR REQUIRED)
message(STATUS "Found ANTLR: ${ANTLR_VERSION}")

file(GLOB G4_FILES "*.g4")
antlr_target(EduCodeGrammar ${G4_FILES} LEXER PARSER VISITOR)

# =====================================
# 3. CONFIGURACIÓN LLVM (Manual vía llvm-config)
# =====================================
# Usamos directamente los comandos que ejecutaste en tu consola para configurar flags y libs

# Obtener flags de compilación (CXXFLAGS)
execute_process(
    COMMAND llvm-config --cxxflags
    OUTPUT_VARIABLE LLVM_CXXFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Limpiar flags que pueden confundir a CMake (como -O2 o -g que ya controlamos nosotros)
# 1. Limpiar flags de optimización/debug que controlamos nosotros
string(REPLACE "-O2" "" LLVM_CXXFLAGS "${LLVM_CXXFLAGS}")
string(REPLACE "-g" "" LLVM_CXXFLAGS "${LLVM_CXXFLAGS}")

# 2. IMPORTANTE: Habilitar excepciones y RTTI
# LLVM por defecto trae -fno-exceptions y -fno-rtti. 
# ANTLR y tu código usan try/catch/dynamic_cast, así que debemos revertirlo.
string(REPLACE "-fno-exceptions" "-fexceptions" LLVM_CXXFLAGS "${LLVM_CXXFLAGS}")
string(REPLACE "-fno-rtti" "-frtti" LLVM_CXXFLAGS "${LLVM_CXXFLAGS}")

# 3. Limpiar saltos de línea
string(REPLACE "\n" " " LLVM_CXXFLAGS "${LLVM_CXXFLAGS}")

# Obtener directorios de include
execute_process(
    COMMAND llvm-config --includedir
    OUTPUT_VARIABLE LLVM_INCLUDE_DIRS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Obtener directorio de librerías (LDFLAGS)
execute_process(
    COMMAND llvm-config --libdir
    OUTPUT_VARIABLE LLVM_LIBRARY_DIRS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Obtener las librerías exactas (LIBS) -> Esto devolverá "-lLLVM-21"
execute_process(
    COMMAND llvm-config --libs
    OUTPUT_VARIABLE LLVM_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\n" " " LLVM_LIBS "${LLVM_LIBS}")

# Obtener librerías del sistema (pthreads, dl, zlib, etc.)
execute_process(
    COMMAND llvm-config --system-libs
    OUTPUT_VARIABLE LLVM_SYSTEM_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\n" " " LLVM_SYSTEM_LIBS "${LLVM_SYSTEM_LIBS}")

message(STATUS "LLVM Include: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM Lib Dir: ${LLVM_LIBRARY_DIRS}")
message(STATUS "LLVM Libs: ${LLVM_LIBS}")

# Configurar el proyecto
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Añadir flags de LLVM al compilador
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXXFLAGS}")

# =====================================
# 4. DEFINICIÓN DE FUENTES
# =====================================
set(MAIN_SOURCES Main.cpp)
set(DRIVER_HEADERS Driver.h)

set(CODEGEN_HEADERS
  codegen/SymbolTable.h
  codegen/TypeSystem.h
  codegen/CodeGenerator.h
  codegen/ExpressionGen.h
  codegen/StatementGen.h
)

set(OPTIMIZER_HEADERS
  optimizer/Optimizer.h
  optimizer/ConstantFolding.h
  optimizer/DeadCodeElimination.h
  optimizer/LoopOptimizer.h
)

set(RUNTIME_HEADERS
  runtime/JITEngine.h
  runtime/RuntimeSupport.h
)

set(DIAGRAM_HEADERS
  diagram/FlowchartNodes.h
  diagram/DotExporter.h
  diagram/FlowchartGenerator.h
)

set(ALL_SOURCES
  ${MAIN_SOURCES}
  ${DRIVER_HEADERS}
  ${CODEGEN_HEADERS}
  ${OPTIMIZER_HEADERS}
  ${RUNTIME_HEADERS}
  ${DIAGRAM_HEADERS}
  ${ANTLR_EduCodeGrammar_CXX_OUTPUTS}
)

# =====================================
# 5. EJECUTABLE Y ENLACE
# =====================================
add_executable(EduCode ${ALL_SOURCES})

# Directorios de cabecera
target_include_directories(EduCode PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/codegen
  ${CMAKE_CURRENT_SOURCE_DIR}/optimizer
  ${CMAKE_CURRENT_SOURCE_DIR}/runtime
  ${CMAKE_CURRENT_SOURCE_DIR}/diagram
  ${ANTLR_INCLUDE_DIR}
  ${ANTLR_EduCodeGrammar_OUTPUT_DIR}
  ${LLVM_INCLUDE_DIRS}
)

# Directorios de librerías
link_directories(${LLVM_LIBRARY_DIRS})

# Enlace final
target_link_libraries(EduCode PRIVATE
  antlr4-runtime
  ${LLVM_LIBS}         # Esto expandirá a -lLLVM-21
  ${LLVM_SYSTEM_LIBS}
  ${CMAKE_DL_LIBS}
)

# =====================================
# 6. EXTRAS
# =====================================
add_custom_target(clean-antlr
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${ANTLR_EduCodeGrammar_OUTPUT_DIR}
)
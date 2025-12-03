cmake_minimum_required(VERSION 3.30)

project(EduCode)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
# FUENTES DEL PROYECTO
# =====================================
file(GLOB SOURCES "*.cpp")

add_executable(EduCode
  ${SOURCES}
  ${ANTLR_EduCodeGrammar_CXX_OUTPUTS}
)

# =====================================
# INCLUDES y LIBRERÍAS
# =====================================
target_include_directories(EduCode PRIVATE
  ${ANTLR_INCLUDE_DIR}
  ${ANTLR_EduCodeGrammar_OUTPUT_DIR}
  ${LLVM_INCLUDE_DIRS}
)

target_link_libraries(EduCode PRIVATE
  antlr4-runtime
  ${REQ_LLVM}
)
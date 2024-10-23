cmake_minimum_required(VERSION 3.1)

project(skibidi_lang)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

file(GLOB_RECURSE UNIVERSAL_SOURCES "src/universal/**.cpp")

file(GLOB_RECURSE COMPILER_SOURCES "src/compiler/**.cpp")
add_executable(compiler ${COMPILER_SOURCES} ${UNIVERSAL_SOURCES})

file(GLOB_RECURSE RUNTIME_SOURCES "src/runtime/**.cpp")
add_executable(runtime ${RUNTIME_SOURCES} ${UNIVERSAL_SOURCES})
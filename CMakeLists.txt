cmake_minimum_required(VERSION 3.1)

project(skibidi_lang)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

file(GLOB_RECURSE SOURCES "src/compiler/**.cpp" "src/universal/**.cpp")
add_executable(compiler ${SOURCES})
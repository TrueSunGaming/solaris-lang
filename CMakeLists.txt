cmake_minimum_required(VERSION 3.1)

project(skibidi_lang)

set(OUTDIR "${CMAKE_BINARY_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTDIR})

if (WIN32)
    set(LIB_EXTENSION "dll")
endif (WIN32)

if (UNIX)
    set(LIB_EXTENSION "so")
endif (UNIX)

set(LIB_PATH "${OUTDIR}/libskibidi.${LIB_EXTENSION}")

add_executable(compiler)
file(GLOB_RECURSE COMPILER_SOURCES "src/compiler/**.cpp")
target_sources(compiler PRIVATE ${COMPILER_SOURCES})
target_link_libraries(compiler ${LIB_PATH})

add_executable(runtime)
file(GLOB_RECURSE RUNTIME_SOURCES "src/runtime/**.cpp")
target_sources(runtime PRIVATE ${RUNTIME_SOURCES})
target_link_libraries(compiler ${LIB_PATH})

add_library(skibidi SHARED)
file(GLOB_RECURSE UNIVERSAL_SOURCES "src/universal/**.cpp")
target_sources(skibidi PUBLIC ${UNIVERSAL_SOURCES})
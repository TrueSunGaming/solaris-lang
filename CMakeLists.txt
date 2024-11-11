cmake_minimum_required(VERSION 3.5)

project(solaris_lang)

set(OUTDIR "${CMAKE_BINARY_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTDIR})

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(LIB_EXTENSION "dll")
endif (WIN32)

if (UNIX)
    set(LIB_EXTENSION "so")
endif (UNIX)

set(LIB_NAME "solaris")
set(LIB_PATH "${OUTDIR}/lib${LIB_NAME}.${LIB_EXTENSION}")

add_executable(compiler)
file(GLOB_RECURSE COMPILER_SOURCES "src/compiler/**.*pp")
target_sources(compiler PRIVATE ${COMPILER_SOURCES})
target_link_libraries(compiler ${LIB_PATH})

add_executable(runtime)
file(GLOB_RECURSE RUNTIME_SOURCES "src/runtime/**.*pp")
target_sources(runtime PRIVATE ${RUNTIME_SOURCES})
target_link_libraries(compiler ${LIB_PATH})

add_library(${LIB_NAME} SHARED)
file(GLOB_RECURSE UNIVERSAL_SOURCES "src/universal/**.*pp")
target_sources(${LIB_NAME} PUBLIC ${UNIVERSAL_SOURCES})
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-O3 -L .")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(PROJECT_NAME "CGamE")

project(${PROJECT_NAME})

include_directories(include)
include_directories(lib/glfw/include)
include_directories(lib)
include_directories(src/CGamEcore)

find_package(OpenGL REQUIRED)

add_subdirectory(lib/CommonCTypes) # CCT.a
add_subdirectory(lib/glfw) # glfw.lib
add_subdirectory(src/CGamEcore) # CGamEruntime.dll & CGamEcore.exe
add_subdirectory(src/Sandbox) # CGamEsandbox.exe

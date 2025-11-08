cmake_minimum_required(VERSION 4.0)

project(CGamE)

# define CGE_BUILD
if (MSVC)
	add_compile_options(/D CGE_BUILD)
else()
	add_compile_options(-D CGE_BUILD)
endif()

include_directories(core)
include_directories(lib/libglfw)
include_directories(lib/libglfw/include)

include_directories(lib/libglad/include)
add_library(glad STATIC lib/libglad/src/glad.c)

add_subdirectory(lib/libglfw)

add_subdirectory(core)


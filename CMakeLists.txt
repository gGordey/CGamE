cmake_minimum_required(VERSION 4.0)

project(CGamE)

# define CGE_BUILD
if (MSVC)
	add_compile_options(/D CGE_BUILD)
else()
	add_compile_options(-D CGE_BUILD)
endif()

include_directories(core)

add_subdirectory(core)


cmake_minimum_required(VERSION 4.0)

project(CGamE)

add_library(CGamEcore SHARED 
	CGamE_Object.c
	CGamE_Result.c
	CGamE_Registry.c 
	CGamE_Core.c)

target_link_libraries(CGamEcore PRIVATE glfw glad)

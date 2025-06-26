cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "CGE_Graphics")

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC glad/src/glad.c)
target_link_libraries(${PROJECT_NAME} 
	glfw
	OpenGL::GL
)

#pragma once

#include "include/CGamE.h"

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <string.h> 

CGE_Renderer CGE_CreateRenderer(
		const char *name,
		CGE_Vec2i size)
{
	CGE_Renderer r = {0};
	r.size = size;
	GLFWwindow *window = glfwCreateWindow(size.x, size.y, name, NULL, NULL);
	if (window == NULL) { 
		CGE_SetLastResult(CGE_RES_GLFW_FAIL);
		return (CGE_Renderer){0};
	}
	r.window = window;
	CGE_SetLastResult(CGE_RES_SUCCESS);
	return r;
}

void CGE_DestroyRenderer(
		CGE_Renderer *renderer) 
{
	if (renderer->window == NULL) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	glfwDestroyWindow(renderer->window);
	memset(renderer, 0, sizeof(CGE_Renderer));
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

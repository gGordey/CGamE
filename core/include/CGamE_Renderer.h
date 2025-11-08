#pragma once

/*
	Renderer is an abstraction window.
*/

#include "CGamE.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

struct CGE_Renderer {
	CGE_Vec2i size;		// heigth and width of window
	CGE_Vec2f pos;		// position of window on a screan
	GLFWwindow *window; // window handle from GLFW    
						// TODO: CGE_WindowApi macro for different window handles?
};

CGE_API CGE_Renderer CGE_CreateRenderer(
		const char *name, 		// window name
		CGE_Vec2i size);		// window size

// Destroys window and memsets entire renderer to 0.
// This function adds last result
CGE_API void CGE_DestroyRenderer(
		CGE_Renderer *renderer); // renderer to be deleted

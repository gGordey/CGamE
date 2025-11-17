#pragma once

/*
	Renderer is an abstraction window.
	CGamE can only hold up to CGE_RENDERERS_CAP renderer at once (64)
	redefine CGE_RENDERERS_CAP to change that number
*/

#include "CGamE.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#ifndef CGE_RENDERERS_CAP
	#define CGE_RENDERERS_CAP 64 
#endif

struct CGE_Renderer {
	CGE_Vec2i size;			// heigth and width of window
	CGE_Vec2f pos;			// position of window on a screan
	GLFWwindow *window; 	// window handle from GLFW    
							// TODO: CGE_WindowApi macro for different window handles?
	size_t id;				// id inside renderer registry 
};

// Creates a new renderer with malloc and returns a pointer to it,
// NULL in case of error
CGE_API CGE_Renderer *CGE_CreateRenderer(
		const char *name, 		// window name
		CGE_Vec2i size);		// window size

// Destroys window and memsets entire renderer to 0.
// This function adds last result
CGE_API void CGE_DestroyRenderer(
		CGE_Renderer *renderer); // renderer to be deleted

// close_callback is function that will be called whenever window is closed
// by default: if there are no more active windows, terminates core
// this function changes this behaviour
CGE_API void CGE_SetRendererCloseCallback(
		void(*close_callback)());

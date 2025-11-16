#include "include/CGamE.h"

#include "glad/glad.h"
#include "include/CGamE_Result.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <string.h> 
#include <stdlib.h>

#ifndef CGE_RENDERERS_CAP
	#define CGE_RENDERERS_CAP 64 
#endif

static void(*CloseCallback)(CGE_Renderer*);

static struct {
	CGE_Renderer *data[CGE_RENDERERS_CAP];
	size_t len;
} RendRegistry;

static size_t CGE_RegisterRenderer(
		CGE_Renderer *rend) {
	size_t new_id = SIZE_MAX;
	if (RendRegistry.len >= CGE_RENDERERS_CAP) {
		for (size_t i = 0; i < CGE_RENDERERS_CAP; ++i) {
			if (RendRegistry.data[i] == 0) {
				new_id = i;
				goto cont;
			}
		}
		CGE_SetLastResult(CGE_RES_TOO_MUCH_RENDERERS);
		return SIZE_MAX;
	}
cont:
	if (new_id == SIZE_MAX) { 
		new_id = RendRegistry.len;
	}
	RendRegistry.data[new_id] = rend;
	++RendRegistry.len;
	CGE_SetLastResult(CGE_RES_SUCCESS);
	return new_id;
}

static void CGE_UnregisterRenderer(
		CGE_Renderer *rend) {
	if (rend->id == SIZE_MAX) {
		// last rend failed to create (too much renderers)
		return;
	}
	if (rend == NULL || rend->id > RendRegistry.len) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	RendRegistry.data[rend->id] = 0;
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

// inner function, use extern to access
void CGE_RenderersPollEvents() {
	for (size_t i = 0; i < RendRegistry.len; ++i) {
		if (RendRegistry.data[i] == 0) {
			continue;
		}
		glfwMakeContextCurrent(RendRegistry.data[i]->window);
		if (glfwWindowShouldClose(RendRegistry.data[i]->window)) { 
			CloseCallback(RendRegistry.data[i]);
			continue;
		}
		glfwSwapBuffers(RendRegistry.data[i]->window);
		glfwPollEvents();
	}
}
extern void CGE_CoreTerminate();

//inner function, use extern to access
void CGE_DefaultRendCloseCallback(
		CGE_Renderer *rend)
{
	CGE_DestroyRenderer(rend);
	for (size_t i = 0; i < RendRegistry.len; ++i) {
		if (RendRegistry.data[i] != 0) {
			return;
		}
	}
	CGE_CoreTerminate();
}

// inner function, use extern to access
void CGE_CleanRendRegistry() {
	for (size_t i = 0; i < RendRegistry.len; ++i) {
		if (RendRegistry.data[i] != 0) {
			CGE_DestroyRenderer(RendRegistry.data[i]);
		}
	}
}

CGE_Renderer *CGE_CreateRenderer(
		const char *name,
		CGE_Vec2i size)
{
	CGE_Renderer *r = malloc(sizeof(CGE_Renderer));
	r->size = size;
	GLFWwindow *window = glfwCreateWindow(size.x, size.y, name, NULL, NULL);
	if (window == NULL) { 
		CGE_SetLastResult(CGE_RES_GLFW_FAIL);
		return NULL;
	}
	r->window = window;
	r->id = CGE_RegisterRenderer(r);
	if (CGE_GetLastResult() == CGE_RES_TOO_MUCH_RENDERERS) {
		CGE_DestroyRenderer(r);
		return NULL;
	}
	CGE_SetLastResult(CGE_RES_SUCCESS);
	return r;
}

void CGE_DestroyRenderer(
		CGE_Renderer *rend) 
{
	if (rend->id == SIZE_MAX) { // rend is already destroyed
		return;
	}
	if (rend->window == NULL) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	glfwDestroyWindow(rend->window);
	CGE_UnregisterRenderer(rend);
	memset(rend, 0, sizeof(CGE_Renderer));
	rend->id = SIZE_MAX;
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

void CGE_SetRendererCloseCallback(
		void(*close_callback)(CGE_Renderer*)) {
	CloseCallback = close_callback;
}

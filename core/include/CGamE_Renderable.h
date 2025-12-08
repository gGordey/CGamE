#pragma once

#include "CGamE.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

struct CGE_Renderable {
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	GLuint shader;
};

CGE_API CGE_Renderable CGE_CreateRenderable();

CGE_API void CGE_RenderablePushVertexAtrib(
		CGE_Renderable rable);

CGE_API void CGE_BindRenderable(
		CGE_Renderable rable);

CGE_API void CGE_DrawRenderable(
		CGE_Renderable rable);

// compiles shader program from 2 sources and sets it as shader field in 'rable'
// if compilation failed, sets shader field to 0
// when creating renderer called with NULL for sources
// this functions adds last result
CGE_API void CGE_RenderableShader(
		CGE_Renderable *rable,
		const char *vertex_src, // glsl source for vertex shader. NULL for default
		const char *frag_src);	// glsl source for fragment shader. NULL for default.

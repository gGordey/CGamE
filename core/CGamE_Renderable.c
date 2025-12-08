#include "include/CGamE.h"

#include "glad/glad.h"

static GLuint default_frag_shader;
static GLuint default_vertex_shader;

static GLuint CGE_CreateShader(
		GLenum shader_type,
		const char *src)
{
	if (src == NULL || shader_type != GL_FRAGMENT_SHADER ||
			shader_type != GL_VERTEX_SHADER) 
	{
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return 0;
	}

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

	// TODO: err here

	CGE_SetLastResult(CGE_RES_SUCCESS);
	return shader;
}

static void CGE_CreateDefaultShaders() {
	const char* default_vertex_src = "\
#version 330 core\n\
layout(location = 0) in vec2 aPos;\n\
void main() {\n\
	gl_Position = vec4(aPos, 0.0, 1.0);}";

	const char* default_frag_src = "\
#version 330 core\n\
out vec4 FragColor;\n\
void main() {\n\
	FragColor = vec4(1.0, 0.0, 0.0, 1.0);}";

	default_vertex_shader = CGE_CreateShader(GL_VERTEX_SHADER, default_vertex_src);
	default_frag_shader   = CGE_CreateShader(GL_FRAGMENT_SHADER, default_frag_src);
	// this (hopefully) should not fail
}

void CGE_RenderableShader(
		CGE_Renderable *rable,
		const char *vertex_src,
		const char *frag_src)
{
	if (rable == NULL) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	if (default_vertex_shader == 0 || default_frag_shader == 0) {
		CGE_CreateDefaultShaders();
	}
	GLuint vertex, frag, prog = 0;
	
	if (vertex_src == NULL) {
		vertex = default_vertex_shader;
	}
	else {
		vertex = CGE_CreateShader(GL_VERTEX_SHADER, vertex_src);
		if (CGE_GetLastResult() != CGE_RES_SUCCESS) {
			goto cleanup;
		}
	}
	if (frag_src == NULL) {
		frag = default_frag_shader;
	}
	else {
		frag = CGE_CreateShader(GL_FRAGMENT_SHADER, frag_src);
		if (CGE_GetLastResult() != CGE_RES_SUCCESS) {
			goto cleanup;
		}
	}

    prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

cleanup:
	if (vertex_src != NULL) glDeleteShader(vertex);
	if (frag_src != NULL) 	glDeleteShader(frag);

	rable->shader = prog; // prog will be 0 here if came form goto	
}

CGE_Renderable CGE_CreateRenderable() {
	CGE_Renderable rable = {0};
	
	
}

#include "include/CGamE.h"

#include "glad/glad.h"
#include "include/CGamE_Result.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>

/*
	Static functions region
*/


static void(*CloseCallback)(CGE_Renderer*);

static struct {
	CGE_Renderer *data[CGE_RENDERERS_CAP];
	size_t len;
} RendRegistry;

static struct {
	CGE_Vec2f *positions; 	// dynamic of positions of entries
	CGE_Vec2f *sizes;		// dynamic array of sizes of coresponding entries
	size_t len;				// len of positions and sizes
	size_t cap;				// cap of positions and sizes
} RendQueue;

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
		CGE_Renderer *rend) 
{
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

static void CGE_ResizeRendQueue() {
	CGE_Vec2f *new_pos 	 = malloc(sizeof(CGE_Vec2f*) * (RendQueue.cap + CGE_DYN_ARR_REALLOC_SIZE));
	CGE_Vec2f *new_sizes = malloc(sizeof(CGE_Vec2f*) * (RendQueue.cap + CGE_DYN_ARR_REALLOC_SIZE));
	
	if (!(new_pos && new_sizes)) {
		CGE_SetLastResult(CGE_RES_OUT_OF_MEMORY);
		free(new_pos);
		free(new_sizes);
		return;
	}
	if (RendQueue.len != 0) { // if RendQueue already has something in it
		memcpy(new_sizes, RendQueue.sizes, sizeof(CGE_Vec2f*) * RendQueue.cap);
		memcpy(new_pos, RendQueue.positions, sizeof(CGE_Vec2f*) * RendQueue.cap);
		free(RendQueue.positions);
		free(RendQueue.sizes);
	}
	RendQueue.sizes     = new_sizes;
	RendQueue.positions = new_pos;
	RendQueue.cap 	   += CGE_DYN_ARR_REALLOC_SIZE;
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

GLuint CGE_CreateShader() {
    const char* vertexSource = "\
        #version 330 core\n\
        layout(location = 0) in vec2 aPos;\n\
        void main() {\n\
            gl_Position = vec4(aPos, 0.0, 1.0);}";

    const char* fragmentSource = "\
        #version 330 core\n\
        out vec4 FragColor;\n\
        void main() {\n\
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);}";

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderProgram;
}

GLuint VBO;
GLuint VAO;
GLuint shader;
float buf[6] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f
};
/* static */ void CGE_DrawRenderable(
		size_t id) 
{ 
	glfwMakeContextCurrent(RendRegistry.data[0]->window);
	if (VBO == 0 || VAO == 0) {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, buf, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0 /* 2 * sizeof(float) */, (void*)0);
		shader = CGE_CreateShader();
	}
	glUseProgram(shader);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


/*
	Inner functions region (use extern to access)
*/

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

void CGE_DefaultRendCloseCallback(
		CGE_Renderer *rend)
{
	extern void CGE_CoreTerminate();
	CGE_DestroyRenderer(rend);
	for (size_t i = 0; i < RendRegistry.len; ++i) {
		if (RendRegistry.data[i] != 0) {
			return;
		}
	}
	CGE_CoreTerminate();
}

void CGE_CleanRendRegistry() {
	for (size_t i = 0; i < RendRegistry.len; ++i) {
		if (RendRegistry.data[i] != 0) {
			CGE_DestroyRenderer(RendRegistry.data[i]);
		}
	}
}

void CGE_DrawRendQueue() {
	for (size_t i = 0; i < RendQueue.len; ++i) {
		CGE_DrawRenderable(i);
	}
}

/*
	API functions region (form .h files)
*/

static bool is_gl_loaded = false;
CGE_Renderer *CGE_CreateRenderer(
		const char *name,
		CGE_Vec2i size)
{
	CGE_Renderer *r = malloc(sizeof(CGE_Renderer));
	r->size = size;
	GLFWwindow *window = glfwCreateWindow(size.x, size.y, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL) { 
		CGE_SetLastResult(CGE_RES_GLFW_FAIL);
		return NULL;
	}
	if (!is_gl_loaded) {
		gladLoadGL();
		is_gl_loaded = true;
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

void CGE_AddRenderTarget(
		CGE_Vec2f pos,
		CGE_Vec2f size) {
	if (RendQueue.len >= RendQueue.cap) {
		CGE_ResizeRendQueue();
		if (CGE_GetLastResult() != CGE_RES_SUCCESS) {
			return;
		}
	}
	RendQueue.positions[RendQueue.len] = pos;
	RendQueue.sizes[RendQueue.len] = size;
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

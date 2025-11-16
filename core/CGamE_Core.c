#include "include/CGamE.h"

#include "GLFW/glfw3.h"

static int should_terminate = 0;

void CGE_CoreTerminate() {
	should_terminate = 1;
}

int CGE_ShouldCoreTerminate() {
	return should_terminate;
}

extern void CGE_DefaultRendCloseCallback(CGE_Renderer *);

void CGE_StartCore() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CGE_SetRendererCloseCallback(CGE_DefaultRendCloseCallback);
}

extern void CGE_CleanObjRegistry(); // CGamE_Registry.c
extern void CGE_CleanRendRegistry(); // CGamE_Renderer.c

void CGE_ShutdownCore() {
	glfwTerminate();
	CGE_CleanObjRegistry();
	CGE_CleanRendRegistry();
}


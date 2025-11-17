#include "include/CGamE.h"

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

static int should_terminate = 0;

void CGE_CoreTerminate() {
	should_terminate = 1;
}

int CGE_ShouldCoreTerminate() {
	return should_terminate;
}


void CGE_StartCore() {
	extern void CGE_DefaultRendCloseCallback(CGE_Renderer*);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CGE_SetRendererCloseCallback(CGE_DefaultRendCloseCallback);
}


void CGE_ShutdownCore() {
	extern void CGE_CleanObjRegistry(); 
	extern void CGE_CleanRendRegistry();
	glfwTerminate();
	CGE_CleanObjRegistry();
	CGE_CleanRendRegistry();
}


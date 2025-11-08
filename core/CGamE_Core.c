#include "include/CGamE.h"

#include "GLFW/glfw3.h"

void CGE_StartCore() {
	glfwInit();
}

extern void CGE_CleanObjRegistry(); // CGamE_Registry.c

void CGE_ShutdownCore() {
	glfwTerminate();
	CGE_CleanObjRegistry();
}


#include <CGamE.h>

#include <GLFW/glfw3.h>

CGE_Bool CGE_CreateGLFWwindow (CGE_Context *Context, CGE_Object_id RendererId, int W, int H, const char *Tilte) {
    CGE_Object *RendererObj = CGE_IndexObject(Context, RendererId);
    if (RendererObj->type != CGE_OBJ_TYPE_RENDERER) {
        CGE_LogErrorWrongObjectType(
            Context, RendererId, 
            "CGE_OBJ_TYPE_RENDERER", "CGE_CreateGLFWwindow"
        );
        return CGE_False;
    }
    CGE_Renderer *Renderer = &RendererObj->data.Renderer;
    Renderer->Window = glfwCreateWindow(W, H, Tilte, NULL, NULL);
    if (!Renderer->Window) {
	char *ErrorLogBuf;
	int glfwErrorCode = glfwGetError((const char**)&ErrorLogBuf);
	CGE_LogString (
	    CGE_LOG_MSG_ERROR " Failed to init GLFW Window\n"
            CGE_LOG_MSG_ERROR " Couldn't continue any further\n"
	    CGE_LOG_MSG_ERROR " GLFW Error:\n",
	    CGE_MSG_TYPE_ERROR 
	);
	CGE_LogString(ErrorLogBuf, CGE_MSG_TYPE_ERROR);
	CGE_LogString("\n\n", CGE_MSG_TYPE_ERROR);
        glfwTerminate();
        return CGE_False;
    }
    return CGE_True;
}

CGE_Object_id CGE_CreateRenderer (CGE_Context *Context) {
    CGE_Object_id Renderer = CGE_CreateObject(Context, CGE_OBJ_TYPE_RENDERER, 0);

    if (!glfwInit()) {
	    char *ErrorLogBuf;
	    int glfwErrorCode = glfwGetError((const char**)&ErrorLogBuf);
        CGE_LogString (
            CGE_LOG_MSG_ERROR " Failed to init GLFW\n"
            CGE_LOG_MSG_ERROR " Couldn't continue any further\n\n",
            CGE_MSG_TYPE_ERROR
        );
        CGE_LogString(ErrorLogBuf, CGE_MSG_TYPE_ERROR);
        glfwTerminate();
        return 0;
    }
    if (!CGE_CreateGLFWwindow(Context, Renderer, 640, 360, "CGamE Runtime")) {
	return 0;
    }

    return Renderer;
}

void CGE_DestroyRenderer (CGE_Context *Context, CGE_Object_id RendererId) {
    glfwDestroyWindow(CGE_IndexObject(Context, RendererId)->data.Renderer.Window);
    CGE_DestroyObject(Context, RendererId);
}

void CGE_ChangeGlfwContext (CGE_Context *Context, CGE_Object_id RendererId) {
    CGE_Object *RendererObj = CGE_IndexObject(Context, RendererId);
    if (RendererObj->type != CGE_OBJ_TYPE_RENDERER) {
        CGE_LogErrorWrongObjectType(Context, RendererId, 
            "CGE_OBJ_TYPE_RENDERER", "CGE_ChangeGlfwContext"
        );
        CGE_Terminate();
        return;
    }
    glfwMakeContextCurrent(RendererObj->data.Renderer.Window);
}

CGE_Bool CGE_RendererDrawFrame (CGE_Context *Context, CGE_Object_id RendererId) {
    CGE_Object *RendererObj = CGE_IndexObject(Context, RendererId);
    if (RendererObj->type != CGE_OBJ_TYPE_RENDERER) {
        CGE_LogErrorWrongObjectType(Context, RendererId, 
            "CGE_OBJ_TYPE_RENDERER", "CGE_RendererDrawFrame"
        );
        CGE_Terminate();
        return CGE_False;
    }
    CGE_Renderer *Renderer = &RendererObj->data.Renderer;
    CGE_ChangeGlfwContext(Context, RendererId);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(Renderer->Window);

    glfwPollEvents();

    if (glfwWindowShouldClose(Renderer->Window)) {
        return CGE_False;
    }
    return CGE_True;
}

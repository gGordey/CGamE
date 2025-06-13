#include <CGamE.h>

#include <GLFW/glfw3.h>

CGE_Bool CGE_CreateGLFWwindow (CGE_Context *Context, CGE_Object_id RendererId, int W, int H, const char *Tilte) {
    CGE_Renderer *Renderer = (CGE_Renderer*)(CGE_IndexObject(Context, RendererId)->data);
    Renderer->Window = glfwCreateWindow(W, H, Tilte, NULL, NULL);
    if (!Renderer->Window) {
        glfwTerminate();
        return CGE_False;
    }
    return CGE_True;
}

CGE_Object_id CGE_CreateRenderer (CGE_Context *Context) {
    CGE_Object_id Renderer = CGE_CreateObject(Context, CGE_OBJ_TYPE_RENDERER, 0);

    if (!glfwInit()) {
        CGE_LogString (
            CGE_LOG_MSG_ERROR " Failed to init GLFW\n"
            CGE_LOG_MSG_ERROR " Couldn't continue any further\n",
            CGE_MSG_TYPE_ERROR
        );
        glfwTerminate();
        return 0;
    }
    CGE_CreateGLFWwindow(Context, Renderer, 640, 360, "CGamE Runtime");

    return Renderer;
}

void CGE_DestroyRenderer (CGE_Context *Context, CGE_Object_id RendererId) {
    glfwDestroyWindow(((CGE_Renderer*)(CGE_IndexObject(Context, RendererId)->data))->Window);
    CGE_DestroyObject(Context, RendererId);
}

void CGE_ChangeGlfwContext (CGE_Context *Context, CGE_Object_id RendererId) {
    glfwMakeContextCurrent(((CGE_Renderer*)(CGE_IndexObject(Context, RendererId)->data))->Window);
}

CGE_Bool CGE_RendererDrawFrame (CGE_Context *Context, CGE_Object_id RendererId) {
    CGE_Renderer *Renderer = (CGE_Renderer*)(CGE_IndexObject(Context, RendererId)->data);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(Renderer->Window);

    glfwPollEvents();

    if (glfwWindowShouldClose(Renderer->Window)) {
        CGE_DestroyRenderer(Context, RendererId);
        return CGE_False;
    }
    return CGE_True;
}

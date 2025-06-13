#ifndef CGamE_window_h
#define CGamE_window_h

#include <GLFW/glfw3.h>

#include <CGamE.h>

struct CGE_Renderer {
    GLFWwindow *Window;
};

CGE_API CGE_Bool CGE_CreateGLFWwindow (CGE_Context *Context, CGE_Object_id RendererId, int W, int H, const char *Tilte);

CGE_API CGE_Object_id CGE_CreateRenderer (CGE_Context *Context);

CGE_API void CGE_DestroyRenderer (CGE_Context *Context, CGE_Object_id RendererId);

CGE_API void CGE_ChangeGlfwContext (CGE_Context *Context, CGE_Object_id RendererId);

CGE_API CGE_Bool CGE_RendererDrawFrame (CGE_Context *Context, CGE_Object_id RendererId);
// returns CGE_True  if everything went successfully
//         CGE_False if window got closed


#endif
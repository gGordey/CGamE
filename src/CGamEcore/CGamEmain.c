/*
    Entry point of CGamE project.
*/

#include <CGamE.h>
#include <stdio.h>

void LogInfo(CGE_Context *Context, CGE_Object_id ObjId, int64_t inf) {
    printf("on hook created %d\n", ObjId);
}
void LogInfo1(CGE_Context *Context, CGE_Object_id ObjId, int64_t inf) {
    printf("on hook destroyed %d\n", ObjId);
}


int main() {
    CGE_Context Context = CGE_CreateContext();
    CGE_CreateObject(&Context, CGE_OBJ_TYPE_UNDEFINED, CGE_OBJECT_TAG_ETERNAL);
    // Create that Zero-object for safety reasons
    
    // CGE_Object_id createdHook = CGE_CreateHook(&Context, &LogInfo, CGE_HOOK_OBJECT_CREATED);
    // CGE_Object_id destroyedHook = CGE_CreateHook(&Context, &LogInfo1, CGE_HOOK_OBJECT_DESTROYED);
    CGE_Object_id Renderer = CGE_CreateRenderer(&Context);
    CGE_Bool RendererDestroyed = CGE_False;
    while (1) {
        // main loop
        CGE_ActivateHookUpdate(&Context);

        if (!RendererDestroyed && !CGE_RendererDrawFrame(&Context, Renderer)) {
            CGE_DestroyRenderer(&Context, Renderer);
            RendererDestroyed = CGE_True;
            break;
        }

        CGE_DestroyTemporaryObjectes(&Context);
        if (CGE_ShouldTerminate()) {           
            break;
        }
    }
    if (!RendererDestroyed) {
        CGE_DestroyRenderer(&Context, Renderer);
    }
    
    CGE_DestroyContext(&Context);
    glfwTerminate();
    
    printf("Press ENTER key to Continue\n");  
    getchar(); 
    
    return 0;
}

/*
    Entry point of CGamE project.
*/

#include <CGamE.h>
#include <stdio.h>


int main() {
    CGE_Context Context = CGE_CreateContext();
    // Create that Zero-object for safety reasons
    CGE_CreateObject(&Context, CGE_OBJ_TYPE_UNDEFINED, CGE_OBJECT_TAG_ETERNAL);
    CGE_Object_id cs = CGE_CreateComponentSystem(&Context);
    CGE_ComponentSystemAddComponent(&Context, cs, 0, CGE_COMPONENT_TYPE_3D_TRANSFORM);   
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

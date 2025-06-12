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
    
    CGE_Object_id createdHook = CGE_CreateHook(&Context, &LogInfo, CGE_HOOK_OBJECT_CREATED);
    CGE_Object_id destroyedHook = CGE_CreateHook(&Context, &LogInfo1, CGE_HOOK_OBJECT_DESTROYED);

    CGE_CreateObject(&Context, CGE_OBJ_TYPE_UNDEFINED, CGE_OBJECT_TAG_TEMPORARY);
    while (1) {
        // main loop
        CGE_ActivateHookUpdate(&Context);

        printf("frame past\n");

        CGE_DestroyTemporaryObjectes(&Context);
    }

    CGE_DestroyContext(&Context);
    return 0;
}
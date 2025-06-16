#include <CGamE.h>

CGE_Object_id CGE_CreateHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type) {
    CGE_Object_id hookId = CGE_CreateSpaceForObject(Context, CGE_CONTEXT_TARGET_TYPE_HOOKS);
    CGE_Hook *Hook = CGE_IndexHook(Context, hookId);
    
    CGE_ActivateHookCreatedObject(Context, hookId);
    
    CGE_AttachHook(Context, Callback, type, hookId);
    return hookId;
}

void CGE_AttachHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type, CGE_Object_id hook) {
    CGE_Hook *Hook = CGE_IndexHook(Context, hook);
    // if (Hook->type != CGE_OBJ_TYPE_RENDERER) {
    //     CGE_LogErrorWrongObjectType(Context, hook, 
    //         "CGE_OBJ_TYPE_HOOK", "CGE_AttachHook"
    //     );
    //     CGE_Terminate();
    //     return;
    // }
    *Hook = (CGE_Hook){
        // set CGE_Object.data to CGE_Hook struct
        .Callback = Callback,
        .type = type
    };
}

void CGE_DeattachHook (CGE_Context *Context, CGE_Object_id hook) {
    if (CGE_IndexObject(Context, hook)->type != CGE_OBJ_TYPE_RENDERER) {
        CGE_LogErrorWrongObjectType(Context, hook, 
            "CGE_OBJ_TYPE_HOOK", "CGE_DeattachHook"
        );
        CGE_Terminate();
        return;
    }
    CGE_AttachHook (Context, &CGE_NullCallback, CGE_HOOK_DEATTACHED, hook);
}

void CGE_ActivateHookUpdate (CGE_Context *Context) {
    for (CGE_Object_id i = 0; i < Context->Hooks.size; ++i) {
        CGE_Hook *Hook = CGE_IndexHook(Context, i);
        if (Hook->type == CGE_HOOK_UPDATE) {
            Hook->Callback(Context, 0, 0);
        }
    }
}
void CGE_ActivateHookDestroyedObject (CGE_Context *Context, CGE_Object_id ObjId) {
    for (CGE_Object_id i = 0; i < Context->Hooks.size; ++i) {
        CGE_Hook *Hook = CGE_IndexHook(Context, i);
        if (Hook->type == CGE_HOOK_OBJECT_DESTROYED) {
            Hook->Callback(Context, ObjId, 0);
        }
    }
}
void CGE_ActivateHookCreatedObject (CGE_Context *Context, CGE_Object_id ObjId) {
    for (CGE_Object_id i = 0; i < Context->Hooks.size; ++i) {
        CGE_Hook *Hook = CGE_IndexHook(Context, i);
        if (Hook->type == CGE_HOOK_OBJECT_CREATED) {
            Hook->Callback(Context, ObjId, 0);
        }
    }
}

void CGE_NullCallback (CGE_Context* Context, CGE_Object_id zeroObj, int64_t zero) {}
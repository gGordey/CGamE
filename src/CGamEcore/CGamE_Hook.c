#include <CGamE.h>

CGE_Object_id CGE_CreateHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type) {
    CGE_Object_id hook = CGE_CreateObject(Context, CGE_OBJ_TYPE_HOOK, 0);
    CGE_AttachHook(Context, Callback, type, hook);
    return hook;
}

void CGE_AttachHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type, CGE_Object_id hook) {
    CGE_Object *HookObj = CGE_IndexObject(Context, hook);
    if (HookObj->type != CGE_OBJ_TYPE_RENDERER) {
        CGE_LogErrorWrongObjectType(Context, hook, 
            "CGE_OBJ_TYPE_HOOK", "CGE_AttachHook"
        );
        CGE_Terminate();
        return;
    }
    *((CGE_Hook*)HookObj->data) = (CGE_Hook){
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
    for (CGE_Object_id i = 0; i < Context->Objects.size; ++i) {
        CGE_Object *obj = CGE_IndexObject(Context, i);
        if (obj->objId == UINT32_MAX ||
            obj->type != CGE_OBJ_TYPE_HOOK) {
                continue;
        }
        if (((CGE_Hook*)obj->data)->type == CGE_HOOK_UPDATE) {
            ((CGE_Hook*)obj->data)->Callback(Context, 0, 0);
        }
    }
}
void CGE_ActivateHookDestroyedObject (CGE_Context *Context, CGE_Object_id ObjId) {
    for (CGE_Object_id i = 0; i < Context->Objects.size; ++i) {
        CGE_Object *obj = CGE_IndexObject(Context, i);
        if (obj->objId == UINT32_MAX ||
            obj->type != CGE_OBJ_TYPE_HOOK) {
                continue;
        }
        if (((CGE_Hook*)obj->data)->type == CGE_HOOK_OBJECT_DESTROYED) {
            ((CGE_Hook*)obj->data)->Callback(Context, ObjId, 0);
        }
    }
}
void CGE_ActivateHookCreatedObject (CGE_Context *Context, CGE_Object_id ObjId) {
        for (CGE_Object_id i = 0; i < Context->Objects.size; ++i) {
        CGE_Object *obj = CGE_IndexObject(Context, i);
        if (obj->objId == UINT32_MAX ||
            obj->type != CGE_OBJ_TYPE_HOOK) {
                continue;
        }
        if (((CGE_Hook*)obj->data)->type == CGE_HOOK_OBJECT_CREATED) {
            ((CGE_Hook*)obj->data)->Callback(Context, ObjId, 0);
        }
    }
}

void CGE_NullCallback (CGE_Context* Context, CGE_Object_id zeroObj, int64_t zero) {}
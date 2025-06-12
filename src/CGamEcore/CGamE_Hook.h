#ifndef CGamE_hook_h
#define CGamE_hook_h

#include <CGamE.h>

enum CGE_Hook_type {
    CGE_HOOK_DEATTACHED, 
    // empty hook, isn't called anywhere
    CGE_HOOK_UPDATE, 
    // called at the start of each frame
    CGE_HOOK_OBJECT_CREATED,
    // called once object is loaded into context and ready to use
    CGE_HOOK_OBJECT_DESTROYED
    // called AFTER destroying object, dont try to access its data
};

struct CGE_Hook { // Hooks are CGE_Objects
    CGE_Hook_type type;
    CGE_Hook_Callback_t Callback;
    CGE_Object_id hookedObj;
    //  hookedObj isn't always used but it is needed for traking objects
    //  general hooks (eg CGEHOOK_UPDATE, CGE_HOOK_OBJECT_CREATED etc) set it to UINT32_MAX
};

CGE_API CGE_Object_id CGE_CreateHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type);

CGE_API void CGE_AttachHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type, CGE_Object_id hook);
CGE_API void CGE_DeattachHook (CGE_Context *Context, CGE_Object_id hook);

CGE_API void CGE_ActivateHookUpdate (CGE_Context *Context);
CGE_API void CGE_ActivateHookDestroyedObject (CGE_Context *Context, CGE_Object_id ObjId);
CGE_API void CGE_ActivateHookCreatedObject (CGE_Context *Context, CGE_Object_id ObjId);

CGE_API void CGE_NullCallback (CGE_Context*, CGE_Object_id, int64_t);
// when CGE_Hook is deattached, its Callback is set to this function

#endif
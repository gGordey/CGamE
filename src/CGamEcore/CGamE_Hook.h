#ifndef CGamE_hook_h
#define CGamE_hook_h

#include <CGamE.h>

enum CGE_Hook_type {
    HOOK_DEATTACHED, // empty hook, isn't called anywhere
    HOOK_UPDATE,
    HOOK_OBJECT_CREATED,
    HOOK_OBJECT_DESTROYED
};

struct CGE_Hook { // Hooks are CGE_Objects
    CGE_Hook_type type;
    CGE_Hook_Callback_t Callback;
    CGE_Object_id hookedObj;
    //  hookedObj isn't always used but it is needed for traking objects
    //  general hooks (eg HOOK_UPDATE, HOOK_OBJECT_CREATED etc) set it to UINT32_MAX
};

CGE_DEF CGE_Object_id CGE_CreateHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type);

CGE_DEF void CGE_AttachHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type, CGE_Object_id hook);
CGE_DEF void CGE_DeattachHook (CGE_Context *Context, CGE_Object_id hook);

CGE_DEF void CGE_ActivateHookUpdate (CGE_Context *Context);

CGE_DEF void CGE_NullCallback (CGE_Context*, int64_t);
// when CGE_Hook is deattached, its Callback is set to this function

#endif
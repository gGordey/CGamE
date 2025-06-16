#ifndef CGamE_hook_h
#define CGamE_hook_h

#include <CGamE.h>

enum CGE_Hook_type {
    // empty hook, isn't called anywhere
    CGE_HOOK_DEATTACHED,
    // called at the start of each frame 
    CGE_HOOK_UPDATE, 
    // called once object is loaded into context and ready to use
    CGE_HOOK_OBJECT_CREATED,
    // called AFTER destroying object, dont try to access its data
    CGE_HOOK_OBJECT_DESTROYED
};

// Hooks are CGE_Objects
struct CGE_Hook { 
    CGE_Hook_type type;
    // Calles callback function once hook is activated
    // &CGE_NullCallback for no callback
    CGE_Hook_Callback_t Callback;
    //  hookedObj isn't always used but it is needed for traking objects
    //  general hooks (eg CGEHOOK_UPDATE, CGE_HOOK_OBJECT_CREATED etc) set it to UINT32_MAX
    CGE_Object_id hookedObj;
};

CGE_API CGE_Object_id CGE_CreateHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type);

CGE_API void CGE_AttachHook (CGE_Context *Context, CGE_Hook_Callback_t Callback, CGE_Hook_type type, CGE_Object_id hook);
CGE_API void CGE_DeattachHook (CGE_Context *Context, CGE_Object_id hook);

// Activates all hooks with type CGE_HOOK_UPDATE
// At the start of the frame
// Arguments `CGE_Object_id` and `int64_t` are 0
CGE_API void CGE_ActivateHookUpdate (CGE_Context *Context);
// Activates all hooks with type CGE_HOOK_OBJECT_DESTROYED
// Once object is destroyed
// Arguments
//      CGE_Object_id -> index of destroyed object
//      in64_t -> 0 
CGE_API void CGE_ActivateHookDestroyedObject (CGE_Context *Context, CGE_Object_id ObjId);
// Activates all hooks with type CGE_HOOK_OBJECT_CREATED
// Once object is created
// Arguments
//      CGE_Object_id -> index of created object
//      in64_t -> 0 
CGE_API void CGE_ActivateHookCreatedObject (CGE_Context *Context, CGE_Object_id ObjId);

// when CGE_Hook is deattached, its Callback is set to this function
CGE_API void CGE_NullCallback (CGE_Context*, CGE_Object_id, int64_t);

#endif
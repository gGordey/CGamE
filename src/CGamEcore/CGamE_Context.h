#ifndef CGamE_context_h
#define CGamE_context_h

#include <CGamE.h>

#include <CommonCTypes/vector.h>

struct CGE_Context {
    // Contains all object
    // vec<CGE_Object>
    vector Objects;
    // if object is destroyed, adds it index here so it can be overrided in future    
    // vec<CGE_Object_id>
    vector FreeSpaces;

    // vec<CGE_Hook>
    vector Hooks; 
    // if hook is destroyed, adds it index here so it can be overrided in future
    // vec<CGE_Object_id>
    vector FreeHooks;
};

enum CGE_Context_TargetType {
    // Context.Objects and Context.FreeSpaces
    // value by default
    CGE_CONTEXT_TARGET_TYPE_OBJECTS,
    // Context.Hooks and Context.FreeHooks
    CGE_CONTEXT_TARGET_TYPE_HOOKS
};

// creates and returns new CGE_Context
CGE_API CGE_Context CGE_CreateContext ();

// destroys context and frees all objects
CGE_API void CGE_DestroyContext (CGE_Context *Context);

// locates space for new object
// returns index of ready-to-use new object
CGE_API CGE_Object_id CGE_CreateSpaceForObject (CGE_Context *Context, CGE_Context_TargetType Target);

// destroys object and makes it overrideble for the future
CGE_API void CGE_FreeSpaceFromObject (CGE_Context *Context, CGE_Object_id ObjId);

// returns pointer to a CGE_Object by its index
CGE_API CGE_Object* CGE_IndexObject (CGE_Context *Context, CGE_Object_id ObjId);

CGE_API CGE_Hook* CGE_IndexHook (CGE_Context *Context, CGE_Object_id HookId);

#endif
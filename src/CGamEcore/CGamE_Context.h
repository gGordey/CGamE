#ifndef CGamE_context_h
#define CGamE_context_h

#include <CGamE.h>
#include <CGamE_Object.h>

#include <CommonCTypes/vector.h>

struct CGE_Context {
    vector Objects; // vec<CGE_Object>
    //contains all object
    vector FreeSpaces; // vec<CGE_Object_id>
    // if object is destroyed, adds it index here so it can be overrided in future
    vector Hooks; // vec<CGE_Hook>
    vector FreeHooks;
};

CGE_API CGE_Context CGE_CreateContext ();
// creates and returns new CGE_Context

CGE_API void CGE_DestroyContext (CGE_Context *Context);
// destroys context and frees all objects

CGE_API CGE_Object_id CGE_CreateSpaceForObject (CGE_Context *Context);
// returns index of ready-to-use new object

CGE_API void CGE_FreeSpaceFromObject (CGE_Context *Context, CGE_Object_id ObjId);
// destroys object and makes it overrideble for the future

CGE_API CGE_Object* CGE_IndexObject (CGE_Context *Context, CGE_Object_id ObjId);
// returns pointer to a CGE_Object by its index

#endif
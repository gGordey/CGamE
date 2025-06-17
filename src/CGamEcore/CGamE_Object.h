#ifndef CGamE_object_h
#define CGamE_object_h

#include <CGamE.h>

#include <stdint.h>

/*
    CGE_Object is core part of game. Pretty much everything is an CGE_Object.
*/

enum CGE_Object_type {
    CGE_OBJ_TYPE_UNDEFINED,
    CGE_OBJ_TYPE_RESOURCE,
    CGE_OBJ_TYPE_COMPONENT_SYSTEM,
    CGE_OBJ_TYPE_RENDERER,
    CGE_OBJ_TYPE_IO
};

struct CGE_Object {
    // index in the CGE_Context. 
    //UINT32_MAX if obj is deleted but not overrided or isn't initializes yet 
    CGE_Object_id objId; 
    CGE_Object_tag tags;
    CGE_Object_type type;
    CGE_pVoid_t data;
};

// Creates a CGE_Object in the given CGE_Context. Returns an index of the created object inside the CGE_Context
CGE_API CGE_Object_id CGE_CreateObject (CGE_Context *Context, CGE_Object_type type, CGE_Object_tag tags);

CGE_API void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index);

CGE_API CGE_Bool CGE_ObjectHasTag (CGE_Context *Context, CGE_Object_id ObjId, CGE_Object_tag tag);

// returns object type by its id
// return CGE_OBJ_TYPE_UNDEFINED if object is deleted or it's actual type
CGE_API CGE_Object_type CGE_GetObjectType (CGE_Context *Context, CGE_Object_id ObjId);

// unsafe, make sure to do all type checks because of scary `void *`
CGE_API CGE_pVoid_t CGE_GetObjectData (CGE_Context *Context, CGE_Object_id ObjId);

#endif
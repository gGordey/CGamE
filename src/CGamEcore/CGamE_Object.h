#ifndef CGamE_object_h
#define CGamE_object_h

#include <CGamE.h>

#include <stdint.h>

/*
    CGE_Object is core part of game. Pretty much everything is an CGE_Object.
*/

enum CGE_Object_type {
    CGE_OBJ_TYPE_UNDEFINED,
    CGE_OBJ_TYPE_HOOK,
    CGE_OBJ_TYPE_RESOURCE,
    CGE_OBJ_TYPE_ENTITY,
    CGE_OBJ_TYPE_RENDERER
};

struct CGE_Object {
    CGE_Object_id objId; // index in the CGE_Context. 
    //UINT32_MAX if obj is deleted but not overrided or isn't initializes yet 
    CGE_Object_tag tags; // some kind of traking thing for engine
    CGE_Object_type type;
    char *name;
    void *data;
};

CGE_API CGE_Object_id CGE_CreateObject (CGE_Context *Context, CGE_Object_type type, CGE_Object_tag tags);
// Creates a CGE_Object in the given CGE_Context. Returns an index of the created object inside the CGE_Context

CGE_API void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index);

CGE_API CGE_Bool CGE_ObjectHasTag (CGE_Context* Context, CGE_Object_id ObjId, CGE_Object_tag tag);

#endif
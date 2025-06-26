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
    CGE_OBJ_TYPE_IO,
    CGE_OBJ_TYPE_CAMERA
};

struct CGE_Object {
    CGE_Object_tag tags;
    CGE_Object_type type;
    union CGE_ObjectInneer {
        CGE_ComponentSystem ComponentSystem;
        CGE_Renderer Renderer;
        CGE_IO IO;
        CGE_Camera Camera;
		CGE_Resource Resource;
        CGE_Vec2 Vec2;
        CGE_Vec3 Vec3;
        CGE_Vec4 Vec4;
    } data;
};

// Creates a CGE_Object in the given CGE_Contesxt. Returns an index of the created object inside the CGE_Context
CGE_API CGE_Object_id CGE_CreateObject (CGE_Context *Context, CGE_Object_type type, CGE_Object_tag tags);

CGE_API void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index);

// CGE_False if object is not valid
CGE_API CGE_Bool CGE_ObjectHasTag (CGE_Context *Context, CGE_Object_id ObjId, CGE_Object_tag tag);

// returns object type by its id
// return CGE_OBJ_TYPE_UNDEFINED if object is deleted or it's actual type
CGE_API CGE_Object_type CGE_GetObjectType (CGE_Context *Context, CGE_Object_id ObjId);

#endif

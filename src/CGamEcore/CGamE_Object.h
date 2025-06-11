#ifndef CGamE_object_h
#define CGamE_object_h

#include <CGamE.h>

#include <stdint.h>

/*
    CGE_Object is core part of game. Pretty much everything is an CGE_Object.
*/

struct CGE_Object {
    CGE_Object_id objId; // index in the CGE_Context. 
    //UINT32_MAX if obj is deleted but not overrided or isn't initializes yet 
    uint32_t tags; // some kind of traking thing for engine
    char *name;
    void *data;
};

CGE_DEF CGE_Object_id CGE_CreateObject (CGE_Context *Context, uint32_t tags);
// Creates a CGE_Object in the given CGE_Context. Returns an index of the created object inside the CGE_Context

CGE_DEF void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index);

#endif
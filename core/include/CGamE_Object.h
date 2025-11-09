#pragma once

/*
	Object is base. 
	You can turn it into anything by customizing its properties and pipeline functions
*/

#include "CGamE.h"

struct CGE_Object {
	CGE_PipelineFunc *pipeline; // list of `CGE_PipelineFunc` 
	CGE_Property *properties;	// list of `CGE_Property` 
	void *props_data;			// raw data of properties themselves
	size_t funcs_count;			// len of `CGE_PipelineFunc *pipeline;`
	size_t props_count;			// len of `CGE_Property *properties;`
	size_t id;					// id in object registry
};

// Creates a new CGE_Object, allocates space for `props_data`, `properties`, `pipeline` with malloc.
// registries object automatically.
// returns (CGE_Object){0} in case of error.
// This functions adds last result.
CGE_API CGE_Object CGE_CreateObject(
		size_t props_count,		// associated with field if CGE_Object
		size_t funcs_count,		// associated with field if CGE_Object
		size_t props_space);	// length (in bytes) for `props_data`

// Frees all allocated fields of given object and memsets entire object to 0
// unregistries object automatically.
// This functions adds last result.
CGE_API void CGE_DestroyObject(
		CGE_Object *obj); 		// pointer to an object to be destroyed

// Searches for CGE_Property by its name.
// returns NULL if failed to find.
// This functions adds last result.
CGE_API CGE_Property *CGE_ObjectFindProperty(
		const CGE_Object *obj,	// object where searching for CGE_Property
		const char *name);		// name of property

// memcpy `obj->props_count` elements from `CGE_Property *props` to `obj->properties`.
// This functions adds last result.
CGE_API void CGE_ObjectFillProps(
		CGE_Object *obj,		// object where props will be copied to
		CGE_Property *props);	// properties to copy form

// memcpy `obj->funcs_count` elements from `CGE_PipelineFunc *funcs` to `obj->pipeline`.
// This functions adds last result.
CGE_API void CGE_ObjectFillPipeline(
		CGE_Object *obj, 		// object where funcs will be copied to
		CGE_PipelineFunc *funcs); // functions to copy form 

// returns the pointer to raw data of property.
// returns NULL in case of error if hasnt found.
// This functions adds last result.
CGE_API void *CGE_ObjectPropertyDataPtr(
		const CGE_Object *obj,
		const char *name);

#pragma once

/*
	Object is base. 
	You can turn it into anything by customizing its properties and pipeline functions
*/

#include "CGamE.h"
#include <stddef.h>

struct CGE_Object {
	CGE_PipelineFunc *pipeline; // list of `CGE_PipelineFunc`
	CGE_Property *properties;	// list of `CGE_Property` 
	void *props_data;			// raw data of properties themselves
	size_t funcs_count;			// len of `CGE_PipelineFunc *pipeline;`
	size_t props_count;			// len of `CGE_Property *properties;`
};

// Creates a new CGE_Object, allocates space for `props_data`, `properties`, `pipeline` with malloc
CGE_API CGE_Object CGE_CreateObject(
		size_t props_count,		// associated with field if CGE_Object
		size_t funcs_count,		// associated with field if CGE_Object
		size_t props_space);	// length (in bytes) for `props_data`

// Frees all allocated fields of given object and memsets entire object to 0
CGE_API void CGE_DestroyObject(
		CGE_Object *obj); 		// pointer to an object to be destroyed

// Searches for CGE_Property by its name.
// returns NULL if failed to find.
CGE_API CGE_Property *CGE_ObjectFindProperty(
		const CGE_Object *obj,	// object where searching for CGE_Property
		const char *name);		// name of property

// memcpy `obj->props_count` elements from `CGE_Property *props` to `obj->properties` 
CGE_API void CGE_ObjectFillProps(
		CGE_Object *obj,		// object where props will be copied to
		CGE_Property *props);	// properties to copy form

CGE_API void CGE_ObjectFillPipeline(
		CGE_Object *obj, 		// object where funcs will be copied to
		CGE_PipelineFunc *funcs); // functions to copy form 

#include "include/CGamE.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

CGE_Object CGE_CreateObject(
		size_t props_count,
		size_t funcs_count,
		size_t props_space) 
{
	CGE_Object obj 	= {0};
	obj.props_count = props_count;
	obj.funcs_count = funcs_count;
	obj.props_data 	= malloc(props_space);
	obj.properties 	= malloc(sizeof(CGE_Property) * props_count);
	obj.pipeline 	= malloc(sizeof(CGE_PipelineFunc) * funcs_count); 
	if (!(obj.props_data && obj.properties && obj.pipeline)) {
		CGE_SetLastResult(CGE_RES_OUT_OF_MEMORY);
	}

	CGE_SetLastResult(CGE_RES_SUCCESS);
	return obj;
}

void CGE_DestroyObject(
		CGE_Object *obj)
{
	free(obj->properties);
	free(obj->props_data);
	free(obj->pipeline);
	memset(obj, 0, sizeof(CGE_Object));
}

CGE_Property *CGE_ObjectFindProperty(
		const CGE_Object *obj,	
		const char *name)
{
	// TODO: make this bin search based on hash of name
	if (!(obj && name)) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return NULL;
	}
	for (size_t i = 0; i < obj->props_count; ++i) {
		if (strcmp(obj->properties[i].name, name) == 0) { return &obj->properties[i]; }
	}

	CGE_SetLastResult(CGE_RES_SUCCESS);
	return NULL;
}

void CGE_ObjectFillProps(
		CGE_Object *obj,
		CGE_Property *props)
{
	// TODO: sort props by hashes of names
	if (!(obj && props && obj->properties)) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	memcpy(obj->properties, props, sizeof(CGE_Property) * obj->props_count);
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

void CGE_ObjectFillPipeline(
		CGE_Object *obj,
		CGE_PipelineFunc *funcs)
{
	if (!(obj && funcs && obj->pipeline)) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	memcpy(obj->pipeline, funcs, sizeof(CGE_PipelineFunc) * obj->funcs_count);
	CGE_SetLastResult(CGE_RES_SUCCESS);
}


// inner function, use extern to access 
void CGE_ExecuteObjectPipeline(
		CGE_Object *obj)
{
	for (size_t i = 0; i < obj->funcs_count; ++i) {
		obj->pipeline[i](obj);
	}
}

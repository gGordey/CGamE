#include "include/CGamE.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// SOA
static struct CGE_ObjectRegistry {
	CGE_Object **objs; 	// dynamic array of CGE_Object pointers
	bool *is_active; 	// dynamic array, shows is coresponding entry in `**objs` should be executed
	size_t cap;
	size_t len;
} ObjRegistry;

#define CGE_REGISTRY_ALLOC_CHACK_SIZE 1024

static void CGE_ObjRegistryResize() {
	CGE_Object **new_objs 	= malloc(sizeof(CGE_Object *) * (ObjRegistry.cap + CGE_REGISTRY_ALLOC_CHACK_SIZE));
	bool *new_is_active   	= malloc(sizeof(bool) * (ObjRegistry.cap + CGE_REGISTRY_ALLOC_CHACK_SIZE));
	
	if (!(new_objs && new_is_active)) {
		CGE_SetLastResult(CGE_RES_OUT_OF_MEMORY);
		return;
	}
	if (ObjRegistry.len != 0) { // if ObjRegistry has something in in
		memcpy(new_objs, ObjRegistry.objs, sizeof(CGE_Object *) * ObjRegistry.cap);
		memcpy(new_is_active, ObjRegistry.is_active, sizeof(bool) * ObjRegistry.cap);
		free(ObjRegistry.objs);
		free(ObjRegistry.is_active);
	}
	ObjRegistry.objs 		= new_objs;
	ObjRegistry.is_active 	= new_is_active;
	ObjRegistry.cap 	   += CGE_REGISTRY_ALLOC_CHACK_SIZE;
	CGE_SetLastResult(CGE_RES_SUCCESS);
}

size_t CGE_ObjectRegister(
		CGE_Object *obj)
{
	if (ObjRegistry.len == ObjRegistry.cap) {
		CGE_ObjRegistryResize();
		if (CGE_GetLastResult() == CGE_RES_OUT_OF_MEMORY) { return SIZE_MAX; }
	}
	size_t empty_obj_id = SIZE_MAX;
	for (size_t i = 0; i < ObjRegistry.len; ++i) {
		if (!ObjRegistry.is_active[i]) {
			empty_obj_id = i;
			break;
		}
	}
	if (empty_obj_id == SIZE_MAX) { empty_obj_id = ObjRegistry.len; }

	ObjRegistry.is_active[empty_obj_id] = true;
	ObjRegistry.objs[empty_obj_id] 		= obj;
	ObjRegistry.len 				   += 1;
	
	return empty_obj_id;
}

void CGE_ObjectUnregister(
		size_t id)
{
	if (id >= ObjRegistry.len) {
		CGE_SetLastResult(CGE_RES_INVALID_PARAM);
		return;
	}
	ObjRegistry.is_active[id] = false;
}

extern void CGE_ExecuteObjectPipeline(CGE_Object *);

// inner funtion, use extern to access
void CGE_ExecuteObjectRegistry()
{
	for (size_t i = 0; i < ObjRegistry.len; ++i) {
		if (!ObjRegistry.is_active[i]) { continue; }
		CGE_ExecuteObjectPipeline(ObjRegistry.objs[i]);
	}
}

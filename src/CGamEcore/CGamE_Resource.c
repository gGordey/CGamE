#include <CGamE.h>


CGE_Object_id CGE_CreateResource (CGE_Context *Context, CGE_ResourceType type) {
	CGE_Object_id ResourceId = CGE_CreateObject(Context, CGE_OBJ_TYPE_RESOURCE, 0);
	CGE_Resource *Resource = &CGE_IndexObject(Context, ResourceId)->data.Resource;
	Resource->type = type;
	return ResourceId;
}

CGE_Resource *CGE_IndexResource (CGE_Context *Context, CGE_Object_id ResourceId) {
	if (!CGE_IsObjectIdValid(Context, ResourceId)) {
		return NULL;
	}
	CGE_Object *ResourceObj = CGE_IndexObject(Context, ResourceId);
	if (ResourceObj == NULL) {
		return NULL;
	}
	if (ResourceObj->type != CGE_OBJ_TYPE_RESOURCE) {
		return NULL;
	}
	return &ResourceObj->data.Resource;
}

CGE_Bool CGE_IsResourceTextValid (const char *string, int bufSize) {
	if (bufSize <= 5) {
		return CGE_False;
	}
	// str[0] -> type 
	// str[1..4] -> datasize
	return CGE_True;
}

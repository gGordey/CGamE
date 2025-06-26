#ifndef CGamE_resource_h
#define CGamE_resource_h

#include <CGamE.h>

enum CGE_ResourceType {
	CGE_RESOURCE_TYPE_IMAGE,
	CGE_RESOURCE_TYPE_TEXT,
};

struct CGE_Resource {
	CGE_ResourceType type;
	union CGE_ResourceInner {
		const char *Text;
	} data;
};

// Creates new CGE_Resource
CGE_API CGE_Object_id CGE_CreateResource (CGE_Context *Context, CGE_ResourceType type);

// returns NULL if errored,
// or actual ptr if ok
CGE_API CGE_Resource *CGE_IndexResource (CGE_Context *Context, CGE_Object_id ResourceId);

CGE_API CGE_Bool CGE_IsResourceTextValid (const char *string, int bufSize);

#endif

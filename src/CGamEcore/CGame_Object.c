#include <CGamE.h>

#include <memory.h>
#include <malloc.h>

CGE_Object_id CGE_CreateObject (CGE_Context *Context, uint32_t tags) {
    CGE_Object_id objId = CGE_CreateSpaceForObject(Context);
    CGE_Object *Object = CGE_IndexObject(Context, objId);
    
    Object->data = malloc(1);
    Object->tags = tags;
    
    return objId;
}

void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index) {
    CGE_Object *Object = CGE_IndexObject(Context, index);
    free(Object->data);
    CGE_FreeSpaceFromObject(Context, index);
}
#include <CGamE.h>

#include <memory.h>
#include <malloc.h>

CGE_Object_id CGE_CreateObject (CGE_Context *Context, CGE_Object_type type, uint32_t tags) {
    CGE_Object_id objId = CGE_CreateSpaceForObject(Context);
    CGE_Object *Object = CGE_IndexObject(Context, objId);
    
    Object->type = type;
    switch (type) {
        case (OBJ_TYPE_HOOK):
            Object->data = malloc(sizeof(CGE_Hook));
            break;
        default:
            Object->data = malloc(1);
            break;
    }
    Object->tags = tags;
    
    return objId;
}

void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index) {
    CGE_Object *Object = CGE_IndexObject(Context, index);
    free(Object->data);
    CGE_FreeSpaceFromObject(Context, index);
}
#include <CGamE.h>

#include <memory.h>
#include <malloc.h>

CGE_Object_id CGE_CreateObject (CGE_Context *Context, CGE_Object_type type, CGE_Object_tag tags) {
    CGE_Object_id objId = CGE_CreateSpaceForObject(Context, CGE_CONTEXT_TARGET_TYPE_OBJECTS);
    CGE_Object *Object = CGE_IndexObject(Context, objId);
    
    Object->type = type;
    switch (type) {
        case CGE_OBJ_TYPE_RENDERER:
            Object->data = malloc(sizeof(CGE_Renderer));
            break;
        case CGE_OBJ_TYPE_COMPONENT_SYSTEM:
            Object->data = malloc(sizeof(CGE_ComponentSystem));
            break;
        case CGE_OBJ_TYPE_IO:
            Object->data = malloc(sizeof(CGE_IO));
            break;
        case CGE_OBJ_TYPE_CAMERA:
            Object->data = malloc(sizeof(CGE_Camera));
            break;
        default:
            Object->data = malloc(1);
            break;
    }
    Object->tags = tags;

    CGE_ActivateHookCreatedObject(Context, objId);
    
    return objId;
}

void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index) {
    CGE_Object *Object = CGE_IndexObject(Context, index);
    if (CGE_ObjectHasTag(Context, index, CGE_OBJECT_TAG_ETERNAL)) {
        CGE_LogString(
            CGE_LOG_MSG_WARNING " Trying delete Eternal Object with id:\n"
            CGE_LOG_MSG_WARNING "\t", CGE_MSG_TYPE_WARNING
        );
        CGE_LogInt(index, CGE_MSG_TYPE_WARNING);
        CGE_LogString("\n", CGE_MSG_TYPE_WARNING);
        return;
    }
    free(Object->data);
    CGE_FreeSpaceFromObject(Context, index);
    CGE_ActivateHookDestroyedObject(Context, index);
}

CGE_Bool CGE_ObjectHasTag (CGE_Context* Context, CGE_Object_id ObjId, CGE_Object_tag tag) {
    CGE_Object *Object = CGE_IndexObject(Context, ObjId);
    if (Object->objId == UINT32_MAX) {
        CGE_LogString(
            CGE_LOG_MSG_WARNING " Trying to access deleted Object\n"
            CGE_LOG_MSG_WARNING " Object ID:\n" 
            CGE_LOG_MSG_WARNING "\t", 
            CGE_MSG_TYPE_WARNING
        );
        CGE_LogInt(ObjId, CGE_MSG_TYPE_WARNING);
        CGE_LogString( "\n"
            CGE_LOG_MSG_WARNING " In funtion 'CGE_ObjectHasTag'\n"
            CGE_LOG_MSG_WARNING " May lead to unexpected behaviour!\n", 
            CGE_MSG_TYPE_WARNING
        );
        return CGE_False;
    }
    return Object->tags & tag;
}

CGE_Object_type CGE_GetObjectType(CGE_Context *Context, CGE_Object_id ObjId) {
    CGE_Object *Object = CGE_IndexObject(Context, ObjId);
    if (Object->objId == UINT32_MAX) {
        return CGE_OBJ_TYPE_UNDEFINED;
    }
    return Object->type;
}

CGE_pVoid_t CGE_GetObjectData (CGE_Context *Context, CGE_Object_id ObjId) {
    return (CGE_pVoid_t)CGE_IndexObject(Context, ObjId)->data;
}
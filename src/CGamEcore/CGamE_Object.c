#include <CGamE.h>

#include <memory.h>
#include <malloc.h>

CGE_Object_id CGE_CreateObject (CGE_Context *Context, CGE_Object_type type, CGE_Object_tag tags) {
    CGE_Object_id objId = CGE_CreateSpaceForObject(Context, CGE_CONTEXT_TARGET_TYPE_OBJECTS);
    CGE_Object *Object = CGE_IndexObject(Context, objId);
    
    Object->type = type;
    Object->tags = tags;

    CGE_ActivateHookCreatedObject(Context, objId);
    
    return objId;
}

void CGE_DestroyObject (CGE_Context *Context, CGE_Object_id index) {
    if (!CGE_IsObjectIdValid(Context, index)) {
        return;
    }
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
    CGE_FreeSpaceFromObject(Context, index);
    CGE_ActivateHookDestroyedObject(Context, index);
}

CGE_Bool CGE_ObjectHasTag (CGE_Context* Context, CGE_Object_id ObjId, CGE_Object_tag tag) {
    if (!CGE_IsObjectIdValid(Context, ObjId)) {
        return CGE_False;
    }
    CGE_Object *Object = CGE_IndexObject(Context, ObjId);
    if (Object == NULL) {
        return CGE_False;
    }
    return Object->tags & tag;
}

CGE_Object_type CGE_GetObjectType(CGE_Context *Context, CGE_Object_id ObjId) {
    CGE_Object *Object = CGE_IndexObject(Context, ObjId);
    if (Object == NULL) {
        return CGE_OBJ_TYPE_UNDEFINED;
    }
    return Object->type;
}

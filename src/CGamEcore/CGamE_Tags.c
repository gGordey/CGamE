#include <CGamE.h>

void CGE_DestroyTemporaryObjectes (CGE_Context *Context) {
    for (CGE_Object_id i = 0; i < Context->Objects.size; ++i) {
        CGE_Object *obj = CGE_IndexObject(Context, i);
        if (CGE_ObjectHasTag(Context, i, CGE_OBJECT_TAG_TEMPORARY)) {
            CGE_DestroyObject(Context, i);
        }        
    }
}
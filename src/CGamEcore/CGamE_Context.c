#include <CGamE.h>

#include <stdlib.h>

const int SPACE_TO_RESERVE = 512;

CGE_Context CGE_CreateContext () {
    CGE_Context Context;
    
    Context.Objects = _cvec_new(sizeof(CGE_Object));
    Context.FreeSpaces = _cvec_new(sizeof(CGE_Object_id));
    Context.Hooks = _cvec_new(sizeof(CGE_Hook));
    Context.FreeHooks = _cvec_new(sizeof(CGE_Object_id));

    _cvec_reserve(&Context.Objects, SPACE_TO_RESERVE);
    _cvec_reserve(&Context.FreeSpaces, SPACE_TO_RESERVE);
    _cvec_reserve(&Context.Hooks, SPACE_TO_RESERVE);
    _cvec_reserve(&Context.FreeHooks, SPACE_TO_RESERVE);

    return Context;
}

void CGE_DestroyContext (CGE_Context *Context) {
    for (int i = 0; i < Context->Objects.size; ++i) {
        if (((CGE_Object*)_cvec_at(&Context->Objects, i))->objId != UINT32_MAX) {
            CGE_DestroyObject(Context, i);
        }
    }
    _cvec_free(&Context->Objects);
    _cvec_free(&Context->FreeSpaces);
    _cvec_free(&Context->Hooks);
    _cvec_free(&Context->FreeHooks);
}

CGE_Object_id CGE_CreateSpaceForObject (CGE_Context *Context, CGE_Context_TargetType Target) {
    int freeId;
    vector* VecTarget;
    vector* VecTargetFree;
    
    switch (Target)
    {
        case CGE_CONTEXT_TARGET_TYPE_HOOKS:
            VecTarget = &Context->Hooks;
            VecTargetFree = &Context->FreeHooks;
            break;
        case CGE_CONTEXT_TARGET_TYPE_OBJECTS:
        default:
            VecTarget = &Context->Objects;
            VecTargetFree = &Context->FreeSpaces;
            break;
    }

    if (VecTargetFree->size > 0) {
        freeId = *(CGE_Object_id*)_cvec_at(VecTargetFree, VecTargetFree->size-1);
        _cvec_pop(VecTargetFree);
    }
    else {
        if (VecTarget->size >= VecTarget->cap-1) {
            _cvec_reserve(VecTarget, SPACE_TO_RESERVE);
        }
        CGE_Object o;
        _cvec_push(VecTarget, &o);
        freeId = VecTarget->size - 1;
    }

    ((CGE_Object*)_cvec_at(VecTarget, freeId))->objId = freeId;
    return freeId;
}

void CGE_FreeSpaceFromObject (CGE_Context *Context, CGE_Object_id ObjId) {
    ((CGE_Object*)_cvec_at(&Context->Objects, ObjId))->objId = UINT32_MAX;

    if (Context->FreeSpaces.size >= Context->FreeSpaces.cap-1) {
        _cvec_reserve(&Context->FreeSpaces, SPACE_TO_RESERVE);
    }
    _cvec_push(&Context->FreeSpaces, &ObjId);
}

CGE_Object* CGE_IndexObject (CGE_Context *Context, CGE_Object_id ObjId) {
    if (ObjId > Context->Objects.size) {
        CGE_LogErrorInvalidIndexVector(
            Context, 
            &Context->Objects, 
            ObjId, 
            "CGE_IndexObject", 
            "Context->Objects"
        );
        return NULL;
    } 
    CGE_Object *Object = (CGE_Object*)_cvec_at(&Context->Objects, ObjId);
    
    // if (Object->objId == UINT32_MAX) {
    //     // ERROR HERE;
    //     exit(1);
    // }
    return Object;
}

CGE_Hook* CGE_IndexHook (CGE_Context *Context, CGE_Object_id HookId) {
    if (HookId > Context->Hooks.size || HookId < 0) {
        CGE_LogErrorInvalidIndexVector(
            Context, 
            &Context->Hooks, 
            HookId, 
            "CGE_IndexHook", 
            "Context->Hooks"
        );
        return NULL;
    } 
    return (CGE_Hook*)_cvec_at(&Context->Hooks, HookId);
}
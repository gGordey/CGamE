#include <CGamE.h>

CGE_Object_id CGE_CreateComponentSystem (CGE_Context *Context) {
    CGE_Object_id CompSysId = CGE_CreateObject(Context, CGE_OBJ_TYPE_COMPONENT_SYSTEM, 0);
    *CGE_GetComponentSystem(Context, CompSysId) = (CGE_ComponentSystem){
        .ComponentIds = {0}
    };
    return CompSysId;
}

CGE_Bool CGE_ComponentSystemAddComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Object_id NewComponentId, CGE_Component_type ComponentType) {
    CGE_ComponentSystem *ComponentSystem = CGE_GetComponentSystem(Context, ComponentSystemId);
    if (ComponentSystem == NULL) {
        return CGE_False;
    }
    if (CGE_ComponentSystemHasComponent(Context, ComponentSystemId, ComponentType)) {
        CGE_LogString (
            CGE_LOG_MSG_WARNING " Trying to add component to Component System\n"
            CGE_LOG_MSG_WARNING " That already have such component\n"
            CGE_LOG_MSG_WARNING " (Couldn't overide components!)\n\n", 
            CGE_MSG_TYPE_WARNING
        );
        return CGE_False;
    }
    ComponentSystem->ComponentIds[ComponentType] = NewComponentId;
    return CGE_True;
}
void CGE_ComponentSystemAddComponent_unsafe (CGE_ComponentSystem *ComponentSystem, CGE_Object_id NewComponentId, CGE_Component_type ComponentType) {
    ComponentSystem->ComponentIds[ComponentType] = NewComponentId;
}

CGE_Bool CGE_ComponentSystemHasComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type ComponentType) {
    CGE_ComponentSystem *ComponentSystem = CGE_GetComponentSystem(Context, ComponentSystemId);
    if (ComponentSystem == NULL) {
        return CGE_False;
    }
    return ComponentSystem->ComponentIds[(CGE_ui32_t)ComponentType] > 0;
}
CGE_Bool CGE_ComponentSystemHasComponent_unsafe (CGE_ComponentSystem *ComponentSystem, CGE_Component_type ComponentType) {
    return ComponentSystem->ComponentIds[(CGE_ui32_t)ComponentType] > 0;
}

CGE_ComponentSystem *CGE_GetComponentSystem (CGE_Context *Context, CGE_Object_id ComponentSystemId) {
    CGE_Object *CompSysObj = CGE_IndexObject(Context, ComponentSystemId);
    if (CompSysObj->type != CGE_OBJ_TYPE_COMPONENT_SYSTEM) {
        CGE_LogErrorWrongObjectType(
            Context, ComponentSystemId,
            "CGE_OBJ_TYPE_COMPONENT_SYSTEM", 
            "CGE_GetComponentSystem"
        );
        return NULL;
    }
    return (CGE_ComponentSystem*)CompSysObj->data;
}

CGE_Object_id CGE_ComponentSystemGetComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type TargetComponent) {
    if (CGE_GetObjectType(Context, ComponentSystemId) != CGE_OBJ_TYPE_COMPONENT_SYSTEM) {
        CGE_LogErrorWrongObjectType(
            Context, ComponentSystemId,
            "CGE_OBJ_TYPE_COMPONENT_SYSTEM", 
            "CGE_ComponentSystemGetComponent"
        );
        return 0;
    }
    // dont use CGE_GetComponentSystem for perfomance reasons,
    // here we are sure that object is CGE_CGE_ComponentSystem
    CGE_Object_id TargetId = (
        (CGE_ComponentSystem*)CGE_IndexObject(Context, ComponentSystemId)->data)
        ->ComponentIds[(CGE_ui32_t)TargetComponent];
    if (CGE_GetObjectType(Context, TargetId) == CGE_OBJ_TYPE_UNDEFINED) {
        return 0;
    }
    return TargetId;
}
CGE_Object_id CGE_ComponentSystemGetComponent_unsafe (CGE_ComponentSystem *ComponentSystem, CGE_Component_type TargetComponent) {
    return ComponentSystem->ComponentIds[TargetComponent];
}

void CGE_ComponentSystemDeattachComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type TargetComponent) {
    if (CGE_GetObjectType(Context, ComponentSystemId) != CGE_OBJ_TYPE_COMPONENT_SYSTEM) {
        CGE_LogErrorWrongObjectType(
            Context, ComponentSystemId,
            "CGE_OBJ_TYPE_COMPONENT_SYSTEM", 
            "CGE_ComponentSystemDeattachComponent"
        );
        return;
    }
    ((CGE_ComponentSystem*)CGE_GetObjectData(Context, ComponentSystemId))
        ->ComponentIds[TargetComponent] = 0;
}
void CGE_ComponentSystemDeattachComponent_unsafe (CGE_ComponentSystem *ComponentSystem, CGE_Component_type TargetType) {
    ComponentSystem->ComponentIds[TargetType] = 0;
}

void CGE_DestroyComponentSystem (CGE_Context *Context, CGE_Object_id ComponentSystemId) {
    CGE_ComponentSystem *ComponentSystem = CGE_GetComponentSystem(Context, ComponentSystemId);
    if (ComponentSystem == NULL) {
        return;
    }
    for (int i = 0; i < CGE_COMPONENT_TYPES_COUNT; ++i) {
        if (ComponentSystem->ComponentIds[i] == 0) {
            continue;
        }
        CGE_DestroyObject(Context, ComponentSystem->ComponentIds[i]);
    }
    CGE_DestroyObject(Context, ComponentSystemId);
}
#include <CGamE.h>

CGE_Object_id CGE_CreateComponentSystem (CGE_Context *Context) {
    CGE_Object_id CompSysId = CGE_CreateObject(Context, CGE_OBJ_TYPE_COMPONENT_SYSTEM, 0);
    *CGE_GetComponentSystem(Context, CompSysId) = (CGE_ComponentSystem){
        .ActiveComponents = 0,
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
    CGE_ComponentSystemSetActiveComponent(Context, ComponentSystemId, ComponentType, CGE_True);
    ComponentSystem->ComponentIds[ComponentType] = NewComponentId;
    return CGE_True;
}

CGE_Bool CGE_ComponentSystemHasComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type ComponentType) {
    CGE_ComponentSystem *ComponentSystem = CGE_GetComponentSystem(Context, ComponentSystemId);
    if (ComponentSystem == NULL) {
        return CGE_False;
    }
    return ComponentSystem->ActiveComponents & (CGE_ui32_t)1 << (CGE_ui32_t)ComponentType;
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

CGE_Bool CGE_ComponentSystemSetActiveComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type TargetComponent, CGE_Bool State) {
    CGE_ComponentSystem *ComponentSystem = CGE_GetComponentSystem(Context, ComponentSystemId);
    if (ComponentSystem == NULL) {
        return CGE_False;
    }
    if (!State && ComponentSystem->ActiveComponents & (CGE_ui32_t)1 << (CGE_ui32_t)TargetComponent) {
        // component is active
        ComponentSystem->ActiveComponents ^= (CGE_ui32_t)1 << (CGE_ui32_t)TargetComponent;
    }
    if (State && !(ComponentSystem->ActiveComponents & (CGE_ui32_t)1 << (CGE_ui32_t)TargetComponent)) {
        // component is disabled
        ComponentSystem->ActiveComponents |= (CGE_ui32_t)1 << (CGE_ui32_t)TargetComponent;
    }
    return CGE_True;
}
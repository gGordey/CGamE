#ifndef CGamE_component_h
#define CGamE_component_h

#include <CGamE.h>

// The amount of possible component types 
// needed for easier managing of engine development
#define CGE_COMPONENT_TYPES_COUNT 2
enum CGE_Component_type {
    CGE_COMPONENT_TYPE_3D_TRANSFORM,
    CGE_COMPONENT_TYPE_MESH  
};

struct CGE_ComponentSystem {
    // contains adresses of components
    // static array for constant-time indexing
    CGE_Object_id ComponentIds[CGE_COMPONENT_TYPES_COUNT];
    CGE_ui32_t ActiveComponents;
};

CGE_API CGE_Object_id CGE_CreateComponentSystem (CGE_Context *Context);

// Tries adding component to given Component system 
// CGE_True if sucseeded
// CGE_False if something went wrong
CGE_API CGE_Bool CGE_ComponentSystemAddComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Object_id NewComponentId, CGE_Component_type ComponentType);

// CGE_False if errored OR actual false
CGE_API CGE_Bool CGE_ComponentSystemHasComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type ComponentType);

// returns pointer to Component system by id
// NULL if errored
CGE_API CGE_ComponentSystem *CGE_GetComponentSystem (CGE_Context *Context, CGE_Object_id ComponentSystemId);

// sets active component to given state
// CGE_True if sucseeded
// CGE_False if something went wrong
CGE_API CGE_Bool CGE_ComponentSystemSetActiveComponent (CGE_Context *Context, CGE_Object_id ComponentSystemId, CGE_Component_type TargetComponent, CGE_Bool State);

#endif
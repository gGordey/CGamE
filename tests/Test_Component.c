#include <CGamE.h>
#include "CGamE_Test.h"

int main (void) {
    int testId = 0;
    
    CGE_Context Context = CGE_CreateContext();

    for (int i = 0; i < 10; ++i) {
        CGE_CreateObject(&Context, CGE_OBJ_TYPE_UNDEFINED, 0);
    }
    
    CGE_Object_id CSid =  CGE_CreateComponentSystem(&Context);
        CGE_ComponentSystem *CS = &CGE_IndexObject(&Context, CSid)->data.ComponentSystem;
    
    // test 0: CS created and indexed
    CGE_LogResultTest(testId, CS != NULL);
    // test 1: Initially all component are zeros
    ++testId;
    CGE_Bool res = CGE_False;
    for (int i = 0; i < CGE_COMPONENT_TYPES_COUNT; ++i) {
        res |= CS->ComponentIds[i];
    }
    CGE_LogResultTest(testId, !res);
    // test 2: Succesfuly added component 
    ++testId;
    CGE_ComponentSystemAddComponent(&Context, CSid, 2, CGE_COMPONENT_TYPE_MESH);
    CGE_LogResultTest(testId, CS->ComponentIds[CGE_COMPONENT_TYPE_MESH] == 2);
    // test 3: Deattached component
    ++testId;
    CGE_ComponentSystemDeattachComponent(&Context, CSid, CGE_COMPONENT_TYPE_MESH);
    CGE_LogResultTest(testId, CS->ComponentIds[CGE_COMPONENT_TYPE_MESH] == 0);
    // clear
    for (int i = 0; i < CGE_COMPONENT_TYPES_COUNT; ++i) {
        CS->ComponentIds[i] = 0;
    }
    // test 4: How Add Component handles invallid CSid
    ++testId;
    CGE_ComponentSystemAddComponent(&Context, 1234, 3, CGE_COMPONENT_TYPE_MESH);
    CGE_LogResultTest(testId, CS->ComponentIds[CGE_COMPONENT_TYPE_MESH] == 0);
    // test 5: How Add Component handles invalid ComponentId
    ++testId;
    CGE_ComponentSystemAddComponent(&Context, CSid, 1234, CGE_COMPONENT_TYPE_MESH);
    CGE_LogResultTest(testId, CS->ComponentIds[CGE_COMPONENT_TYPE_MESH] == 0);
    // test 6: How Add Component handles invalid type
    ++testId;
    CGE_ComponentSystemAddComponent(&Context, CSid, 2, 4000);
    res = CGE_False;
    for (int i = 0; i < CGE_COMPONENT_TYPES_COUNT; ++i) {
        res |= CS->ComponentIds[i];
    }
    CGE_LogResultTest(testId, !res);
    // test 7: How Add Component handles overiding component
    ++testId;
    CGE_ComponentSystemAddComponent(&Context, CSid, 2, CGE_COMPONENT_TYPE_MESH);
    CGE_ComponentSystemAddComponent(&Context, CSid, 3, CGE_COMPONENT_TYPE_MESH);
    CGE_LogResultTest(testId, CS->ComponentIds[CGE_COMPONENT_TYPE_MESH] == 2);
    // test 8: Has Component
    ++testId;
    CGE_LogResultTest(testId, CGE_ComponentSystemHasComponent(&Context, CSid, CGE_COMPONENT_TYPE_MESH) &&
        !CGE_ComponentSystemHasComponent(&Context, CSid, CGE_COMPONENT_TYPE_3D_TRANSFORM));
    // test 9: Has Component handles invalid CSid
    ++testId;
    CGE_LogResultTest(testId, !CGE_ComponentSystemHasComponent(&Context, 1234, CGE_COMPONENT_TYPE_MESH));
    // test 10: Has Component handles invalid Component Type
    ++testId;
    CGE_LogResultTest(testId, !CGE_ComponentSystemHasComponent(&Context, CSid, 4000));
    // test 11: Get Component
    ++testId;
    res = CGE_False;
    for (int i = 0; i < CGE_COMPONENT_TYPES_COUNT; ++i) {
        CS->ComponentIds[i] = i + 1; // i + 1 so it is non-zero
        if (CGE_ComponentSystemGetComponent(&Context, CSid, i) != i + 1) {
            res = CGE_True;
        }
    }
    CGE_LogResultTest(testId, !res);
    // test 12: Get Component handles invalid CSid
    ++testId;
    CGE_LogResultTest(testId, CGE_ComponentSystemGetComponent(&Context, 1234, CGE_COMPONENT_TYPE_MESH) == 0);
    // test 13: Get Component handles invatid Component Id
    ++testId;
    CGE_LogResultTest(testId, CGE_ComponentSystemGetComponent(&Context, CSid, 4000) == 0);


    CGE_DestroyContext(&Context);
    CGE_LogString("ALL TEST ARE FINISHED!\n", CGE_MSG_TYPE_INFO);
}
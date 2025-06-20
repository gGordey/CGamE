#include <CGamE.h>
#include "CGamE_Test.h"

#include <stdio.h>

CGE_Bool CallbacksStatus[3] = {CGE_False};

void Callback1(CGE_Context *Context, CGE_Object_id ObjId, int64_t i64) {
    printf("\t\tActivated Callback 1 ObjId:%d i64:%d\n");
    CallbacksStatus[0] = !CallbacksStatus[0];
}
void Callback2(CGE_Context *Context, CGE_Object_id ObjId, int64_t i64) {
    printf("\t\tActivated Callback 2 ObjId:%d i64:%d\n");
    CallbacksStatus[1] = !CallbacksStatus[1];
}
void Callback3(CGE_Context *Context, CGE_Object_id ObjId, int64_t i64) {
    printf("\t\tActivated Callback 3 ObjId:%d i64:%d\n");
    CallbacksStatus[2] = !CallbacksStatus[2];
}

int main(void) {
    int testId = 0;
    CGE_Context Context = CGE_CreateContext();
    
    CGE_Object_id Hook1Id = CGE_CreateHook(&Context, &Callback1, CGE_HOOK_UPDATE);
        CGE_Hook *Hook1 = CGE_IndexHook(&Context, Hook1Id);
    CGE_Object_id Hook2Id = CGE_CreateHook(&Context, &Callback2, CGE_HOOK_OBJECT_DESTROYED);
        CGE_Hook *Hook2 = CGE_IndexHook(&Context, Hook2Id);
    CGE_Object_id Hook3Id = CGE_CreateHook(&Context, &Callback3, CGE_HOOK_OBJECT_CREATED);
        CGE_Hook *Hook3 = CGE_IndexHook(&Context, Hook3Id);

    // test 0: all hooks are created and indexed
        CGE_LogResultTest(testId, Hook1 != NULL && Hook2 != NULL && Hook3 != NULL);
    // test 1: IndexHook works and returns null
    ++testId;
    CGE_LogResultTest(testId, CGE_IndexHook(&Context, 100) == NULL);
    // test 2: IndexHook handles negative number
    // (just to check because CGE_Object_id is unsigned, maybe not in the future)
    ++testId;
    CGE_LogResultTest(testId, CGE_IndexHook(&Context, -100) == NULL);
    // test 3: Hook types filled successfuly
    ++testId;
    CGE_LogResultTest(testId, 
        Hook1->type == CGE_HOOK_UPDATE &&
        Hook2->type == CGE_HOOK_OBJECT_DESTROYED &&
        Hook3->type == CGE_HOOK_OBJECT_CREATED
    );
    // test 4: Hook Callbacks filled successfuly
    ++testId;
    CGE_LogResultTest(testId, 
        Hook1->Callback == &Callback1 &&
        Hook2->Callback == &Callback2 &&
        Hook3->Callback == &Callback3
    );
    // test 5: UpdateHook Activation
    ++testId;
    CGE_ActivateHookUpdate(&Context);
    CGE_LogResultTest(testId, CallbacksStatus[0]);
    // test 6: ObjDestroyed Hook Activation
    ++testId;
    CGE_ActivateHookDestroyedObject(&Context, 12);
    CGE_LogResultTest(testId, CallbacksStatus[1]);
    // test 7: ObjCreated Hook Activation
    ++testId;
    CGE_ActivateHookCreatedObject(&Context, 160);
    CGE_LogResultTest(testId, CallbacksStatus[2]);
    // test 8: All hooks were activated once
    ++testId;
    CGE_LogResultTest(testId, CallbacksStatus[0] && CallbacksStatus[1] && CallbacksStatus[2]);
    //test 9: None of hooks are acivated when deattached
    ++testId;
    CGE_DeattachHook(&Context, Hook1Id);
    CGE_DeattachHook(&Context, Hook2Id);
    CGE_DeattachHook(&Context, Hook3Id);

    CGE_ActivateHookCreatedObject(&Context, 0);
    CGE_ActivateHookDestroyedObject(&Context, 0);
    CGE_ActivateHookUpdate(&Context);

    CGE_LogResultTest(testId, CallbacksStatus[0] && CallbacksStatus[1] && CallbacksStatus[2]);

    CGE_DestroyContext(&Context);
    CGE_LogString("ALL TEST ARE FINISHED!\n", CGE_MSG_TYPE_INFO);
}
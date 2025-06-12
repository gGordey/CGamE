/*
    Entry point of CGamE project.
*/

#include <CGamE.h>
#include <stdio.h>

void TestCallback(CGE_Context *Context, int64_t zero) {
    printf("entered callback\n");
}
void TestCallback1(CGE_Context *Context, int64_t zero) {
    printf("another callback\n");
}

int main() {
    CGE_Context Context = CGE_CreateContext();  

    CGE_Object_id h1 = CGE_CreateHook(&Context, &TestCallback, HOOK_UPDATE);
    CGE_Object_id h2 = CGE_CreateHook(&Context, &TestCallback1, HOOK_UPDATE);

    // main loop
    while (1) {
        CGE_ActivateHookUpdate(&Context);
    }

    CGE_DestroyContext(&Context);
    return 0;
}
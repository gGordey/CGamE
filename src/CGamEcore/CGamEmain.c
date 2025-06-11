/*
    Entry point of CGamE project.
*/

#include <CGamE.h>
#include <stdio.h>
int main() {
    CGE_Context context = CGE_CreateContext();

    CGE_DestroyContext(&context);
    return 0;
}
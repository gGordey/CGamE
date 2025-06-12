/*
    Entry point of CGamE project.
*/

#include <CGamE.h>
#include <stdio.h>

int main() {
    CGE_Context context = CGE_CreateContext();  

    CGE_LogString("Hello From Success\n", SUCCESS);
    CGE_LogString("Hello From Error\n", ERROR);
    CGE_LogString("Hello From Warning\n", WARNING);
    CGE_LogString("Hello From Info\n", INFO);
    CGE_LogString("Hello From Debug\n", DEBUG);

    CGE_LogInt(25, SUCCESS);
    printf("\n");
    CGE_LogFloat(235.23f, ERROR);
    // main loop
    while (1) {

    }

    CGE_DestroyContext(&context);
    return 0;
}
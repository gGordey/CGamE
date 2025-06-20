#ifndef CGamE_Test_h
#define CGamE_Test_h

#include <CGamE.h>

void CGE_LogResultTest(int testId, CGE_Bool result) {
    CGE_Message_type type = result ? CGE_MSG_TYPE_SUCCESS : CGE_MSG_TYPE_ERROR;
    CGE_LogString (
            CGE_LOG_MSG_SUCCESS " Test N ",
            type
    );
    CGE_LogInt(testId, type);
    if (result) {
        CGE_LogString(" ran successfuly!\n", CGE_MSG_TYPE_SUCCESS);
    }
    else {
        CGE_LogString(" ran with Error! :(\n", CGE_MSG_TYPE_ERROR);
    }
}

#endif
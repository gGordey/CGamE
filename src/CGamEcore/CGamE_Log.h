#ifndef CGamE_log_h
#define CGamE_lof_h

#include <CGamE.h>

enum CGE_Message_type {
    CGE_MSG_TYPE_SUCCESS,
    CGE_MSG_TYPE_ERROR,
    CGE_MSG_TYPE_WARNING,
    CGE_MSG_TYPE_INFO,
    CGE_MSG_TYPE_DEBUG
};

CGE_API const char* CGE_LoggingColor (CGE_Message_type type);

CGE_API void CGE_LogString (const char *msg, CGE_Message_type type);

CGE_API void CGE_LogInt (int64_t msg, CGE_Message_type type);

CGE_API void CGE_LogFloat (double msg, CGE_Message_type type);

#endif
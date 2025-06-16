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

CGE_API CGE_Bool CGE_ShouldTerminate(void);
CGE_API void CGE_Terminate(void);

CGE_API const char* CGE_LoggingColor (CGE_Message_type type);

CGE_API void CGE_LogString (const char *msg, CGE_Message_type type);

CGE_API void CGE_LogInt (int64_t msg, CGE_Message_type type);

CGE_API void CGE_LogFloat (double msg, CGE_Message_type type);

CGE_API void CGE_LogErrorWrongObjectType (CGE_Context *Context, CGE_Object_id ObjId, const char *Expected, const char *FunctionName);

CGE_API void CGE_LogErrorInvalidIndexVector (CGE_Context *Context, vector *Vector, size_t index, const char *Caller, const char *VecName);

#endif
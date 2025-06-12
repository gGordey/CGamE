#ifndef CGamE_log_h
#define CGamE_lof_h

#include <CGamE.h>

enum CGE_Message_type {
    SUCCESS,
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

CGE_DEF const char* CGE_LoggingColor (CGE_Message_type type);

CGE_DEF void CGE_LogString (const char *msg, CGE_Message_type type);

CGE_DEF void CGE_LogInt (int64_t msg, CGE_Message_type type);

CGE_DEF void CGE_LogFloat (double msg, CGE_Message_type type);

#endif
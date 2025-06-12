#ifndef CGamE_log_h
#define CGamE_lof_h

#include <CGamE.h>

enum CGE_MessageType {
    SUCCESS,
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

CGE_DEF const char* CGE_LoggingColor (CGE_MessageType type);

CGE_DEF void CGE_LogString (const char *msg, CGE_MessageType type);

CGE_DEF void CGE_LogInt (int64_t msg, CGE_MessageType type);

CGE_DEF void CGE_LogFloat (double msg, CGE_MessageType type);

#endif
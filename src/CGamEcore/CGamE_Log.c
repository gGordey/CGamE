#include <CGamE.h>

#include <stdio.h>

const char* CGE_LoggingColor (CGE_Message_type type) {
    switch (type) {
        case CGE_MSG_TYPE_SUCCESS:
            return "\e[0;92m";
        case CGE_MSG_TYPE_ERROR:
            return "\e[0;91m";
        case CGE_MSG_TYPE_WARNING:
            return "\e[0;33m";
        case CGE_MSG_TYPE_INFO:
            return "\e[0;36m";
        case CGE_MSG_TYPE_DEBUG:
            return "\e[0;37m";
        default:
            return "\e[0m";
    }
}

void CGE_LogString (const char *msg, CGE_Message_type type) {
    printf (CGE_LoggingColor(type));
    printf (msg);
    printf (CGE_LOG_COL_RESET);
}

void CGE_LogInt (int64_t msg, CGE_Message_type type) {
    printf (CGE_LoggingColor(type));
    printf ("%lld", msg);
    printf (CGE_LOG_COL_RESET);
}

void CGE_LogFloat (double msg, CGE_Message_type type) {
    printf (CGE_LoggingColor(type));
    printf ("%.2f", msg);
    printf (CGE_LOG_COL_RESET);
}
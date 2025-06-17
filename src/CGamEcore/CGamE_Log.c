#include <CGamE.h>

#include <stdio.h>

static CGE_Bool terminateStatus = CGE_False;
CGE_Bool CGE_ShouldTerminate(void) {
    return terminateStatus;
}

void CGE_Terminate(void) {
    glfwTerminate();
    terminateStatus = CGE_True;
}

#ifdef _WIN32
void CGE_LogEnableColors () {
    DWORD consoleMode;
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleMode(outputHandle, &consoleMode)) {
        SetConsoleMode(outputHandle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}
#else
void CGE_LogEnableColors () {}
#endif

const char* CGE_LoggingColor (CGE_Message_type type) {
    // No colors for Visual Studio because it doesnt want to recognize "\e...." 
#ifndef _MSC_VER
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
#else
    return "";
#endif
}

void CGE_LogString (const char *msg, CGE_Message_type type) {
    printf(CGE_LoggingColor(type));
    printf(msg);
    printf(CGE_LOG_COL_RESET);
}

void CGE_LogInt (int64_t msg, CGE_Message_type type) {
    printf(CGE_LoggingColor(type));
    printf("%lld", msg);
    printf(CGE_LOG_COL_RESET);
}

void CGE_LogFloat (double msg, CGE_Message_type type) {
    printf(CGE_LoggingColor(type));
    printf("%.2f", msg);
    printf(CGE_LOG_COL_RESET);
}

void CGE_LogErrorWrongObjectType(CGE_Context *Context, CGE_Object_id ObjId, const char *Expected, const char *FunctionName) {
    CGE_LogString(
        CGE_LOG_MSG_ERROR " Passing Object with wrong type!\n"
        CGE_LOG_MSG_ERROR " Expected:\n"
        CGE_LOG_MSG_ERROR "\t", 
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogString(Expected, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n"
        CGE_LOG_MSG_ERROR " Actual type:\n"
        CGE_LOG_MSG_ERROR "\t",
        CGE_MSG_TYPE_ERROR
    );
    CGE_Object *Object = CGE_IndexObject(Context, ObjId);
    CGE_LogInt(Object->type, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n"
        CGE_LOG_MSG_ERROR " Object Id:\n"
        CGE_LOG_MSG_ERROR "\t",
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogInt(ObjId, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n"
        CGE_LOG_MSG_ERROR " In funtion:\n"
        CGE_LOG_MSG_ERROR "\t", 
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogString(FunctionName, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n\n", CGE_MSG_TYPE_ERROR);
}

void CGE_LogErrorInvalidIndexVector (CGE_Context *Context, vector *Vector, size_t index, const char *Caller, const char *VecName) {
    CGE_LogString(
        CGE_LOG_MSG_ERROR " Out-of-bounds vector index\n"
        CGE_LOG_MSG_ERROR " Got:\n"
        CGE_LOG_MSG_ERROR "\t", 
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogInt(index, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n"
        CGE_LOG_MSG_ERROR " Actual size:\n"
        CGE_LOG_MSG_ERROR "\t",
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogInt(Vector->size, CGE_MSG_TYPE_ERROR);
        CGE_LogString("\n"
        CGE_LOG_MSG_ERROR " In vector:\n"
        CGE_LOG_MSG_ERROR "\t",
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogString(VecName, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n"
        CGE_LOG_MSG_ERROR " In funtion:\n"
        CGE_LOG_MSG_ERROR "\t", 
        CGE_MSG_TYPE_ERROR
    );
    CGE_LogString(Caller, CGE_MSG_TYPE_ERROR);
    CGE_LogString("\n\n", CGE_MSG_TYPE_ERROR);
}
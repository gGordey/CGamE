#ifndef CGamE_io_h
#define CGamE_io_h

#include <CGamE.h>

struct CGE_IO {
    char *StringBuf;
    CGE_ui32_t BufSize;
};


CGE_API CGE_Object_id CGE_CreateIO (CGE_Context *Context);

CGE_API void CGE_DestroyIO (CGE_Context *Context, CGE_Object_id IOid);

// Read file inside given file to CGE_IO.StringBuf
// returns CGE_True if success
// CGE_False if error
CGE_API CGE_Bool CGE_IOReadFile (CGE_Context *Context, CGE_Object_id IOid, const char *FileName);

// returns CGE_IO.StringBuf
// NULL if error
CGE_API char *CGE_IOGetString (CGE_Context *Context, CGE_Object_id IOid);

#endif
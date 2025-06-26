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
// unsafe versionf of CGE_IOReadFile
CGE_API CGE_Bool CGE_IOReadFile_unsafe (CGE_IO *IO, const char *FileName);

// returns CGE_IO.StringBuf
// NULL if error
CGE_API const char *CGE_IOGetString (CGE_Context *Context, CGE_Object_id IOid);
// unsafe version of CGE_IOGEtString
CGE_API const char *CGE_IOGetString_unsafe (CGE_IO *IO);

// Sets current buffer of given IO to `string`
CGE_API void CGE_IOSetString (CGE_Context *Context, CGE_Object_id IOid, char *string);
// unsafe version of CGE_IOSetString
CGE_API void CGE_IOSetString_unsafe (CGE_IO *IO, char *string);

// writes current buffer of given IO to file
// CGE_True if succeded
// CGE_False if errored
CGE_API CGE_Bool CGE_IOWriteToFile (CGE_Context *Context, CGE_Object_id IOid, const char *FileName);
// unsafe version of CGE_IOWriteToFile 
CGE_API CGE_Bool CGE_IOWriteToFile_unsafe (CGE_IO *IO, const char *FileName);

#endif

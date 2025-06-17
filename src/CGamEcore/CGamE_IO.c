#include <CGamE.h>

#include <stdio.h>
#include <malloc.h> 

CGE_Object_id CGE_CreateIO(CGE_Context *Context) {
    CGE_Object_id IOid = CGE_CreateObject(Context, CGE_OBJ_TYPE_IO, 0);
    *((CGE_IO*)CGE_GetObjectData(Context, IOid)) = (CGE_IO) {
        .StringBuf = (char*)malloc(1),
        .BufSize = 0
    };
    return IOid;
}

void CGE_DestroyIO(CGE_Context *Context, CGE_Object_id IOid) {
    if (CGE_GetObjectType(Context, IOid) != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_DestroyIO"
        );
        return;
    }
    free(((CGE_IO*)CGE_GetObjectData(Context, IOid))->StringBuf);
    CGE_DestroyObject(Context, IOid);
}

CGE_Bool CGE_IOReadFile(CGE_Context *Context, CGE_Object_id IOid, const char *FileName) {
    if (CGE_GetObjectType(Context, IOid) != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_IOReadFile"
        );
        return CGE_False;
    }
    FILE *File = fopen(FileName, "r");
    if (File == NULL) {
        CGE_LogString (
            CGE_LOG_MSG_ERROR " No such File or Directory:\n"
            CGE_LOG_MSG_ERROR "\t'",
            CGE_MSG_TYPE_ERROR
        );
        CGE_LogString (FileName, CGE_MSG_TYPE_ERROR);
        CGE_LogString ("'\n\n", CGE_MSG_TYPE_ERROR);
        return CGE_False;
    }
    CGE_IO *IO = (CGE_IO*)CGE_GetObjectData(Context, IOid);
    free(IO->StringBuf);

    fseek(File, 0, SEEK_END);
    IO->BufSize = ftell(File);
    fseek(File, 0, SEEK_SET);
    
    IO->StringBuf = (char*)malloc(IO->BufSize+1);

    fread(IO->StringBuf, 1, IO->BufSize, File);
    IO->StringBuf[IO->BufSize] = 0;

    return CGE_True;
}

char *CGE_IOGetString (CGE_Context *Context, CGE_Object_id IOid) {
    if (CGE_GetObjectType(Context, IOid) != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_IOGetString"
        );
        return NULL;
    }
    return ((CGE_IO*)CGE_GetObjectData(Context, IOid))->StringBuf;
}
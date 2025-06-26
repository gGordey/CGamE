#include <CGamE.h>

#include <stdio.h>
#include <malloc.h> 
#include <CommonCTypes/string.h>

CGE_Object_id CGE_CreateIO(CGE_Context *Context) {
    CGE_Object_id IOid = CGE_CreateObject(Context, CGE_OBJ_TYPE_IO, 0);
    CGE_IndexObject(Context, IOid)->data.IO = (CGE_IO) {
        .StringBuf = (char*)malloc(1),
        .BufSize = 0
    };
    return IOid;
}

void CGE_DestroyIO(CGE_Context *Context, CGE_Object_id IOid) {
    CGE_Object *IOobj = CGE_IndexObject(Context, IOid);
    if (IOobj->type != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_DestroyIO"
        );
        return;
    }
    free(IOobj->data.IO.StringBuf);
    CGE_DestroyObject(Context, IOid);
}

CGE_Bool CGE_IOReadFile(CGE_Context *Context, CGE_Object_id IOid, const char *FileName) {
	if (!CGE_IsObjectIdValid(Context, IOid)) {
		return CGE_False;
	}
    CGE_Object *IOobj = CGE_IndexObject(Context, IOid);
	if (IOobj == NULL) {
		return CGE_False;
	}
    if (IOobj->type != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_IOReadFile"
        );
        return CGE_False;
    }
    CGE_IO *IO = &IOobj->data.IO;

    return CGE_IOReadFile_unsafe(IO, FileName);
}
CGE_Bool CGE_IOReadFile_unsafe (CGE_IO *IO, const char *FileName) {
    FILE *File = fopen(FileName, "r");
	if (File == NULL) {
		return CGE_False;
	}
    free(IO->StringBuf);
    
	fseek(File, 0, SEEK_END);
    IO->BufSize = ftell(File);
    fseek(File, 0, SEEK_SET);
    
    IO->StringBuf = (char*)malloc(IO->BufSize+1);

    fread(IO->StringBuf, 1, IO->BufSize, File);
    IO->StringBuf[IO->BufSize] = 0;

    fclose(File);
	return CGE_True;
}

const char *CGE_IOGetString (CGE_Context *Context, CGE_Object_id IOid) {
    CGE_Object *IOobj = CGE_IndexObject(Context, IOid);
    if (IOobj->type != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_IOGetString"
        );
        return NULL;
    }
    return IOobj->data.IO.StringBuf;
}
const char *CGE_IOGetString_unsafe (CGE_IO *IO) {
	return IO->StringBuf;
}

void CGE_IOSetString (CGE_Context *Context, CGE_Object_id IOid, char *string) {
	if (!CGE_IsObjectIdValid(Context, IOid)) {
		return;
	}
	CGE_Object *IOobj = CGE_IndexObject(Context, IOid);
	if (IOobj == NULL) {
		return;
	}
	if (IOobj->type != CGE_OBJ_TYPE_IO) {
		CGE_LogErrorWrongObjectType(Context, IOid, "CGE_OBJ_TYPE_IO", "CGE_IOGetString");
		return;
	}
	CGE_IO *IO = &IOobj->data.IO;
    IO->StringBuf = string;
	IO->BufSize = _str_size_cstr(string);
}
void CGE_IOSetString_unsafe (CGE_IO *IO, char *string) {
    IO->StringBuf = string;
	IO->BufSize = _str_size_cstr(string);
}

CGE_Bool CGE_IOWriteToFile (CGE_Context *Context, CGE_Object_id IOid, const char *FileName) {
	if (!CGE_IsObjectIdValid(Context, IOid)) {
		return CGE_False;
	}
    CGE_Object *IOobj = CGE_IndexObject(Context, IOid);
	if (IOobj == NULL) {
		return CGE_False;
	}
    if (IOobj->type != CGE_OBJ_TYPE_IO) {
        CGE_LogErrorWrongObjectType ( 
            Context, IOid, 
            "CGE_OBJ_TYPE_IO", "CGE_IOWriteToFile"
        );
        return CGE_False;
    }
	CGE_IO *IO = &IOobj->data.IO;
	return CGE_IOWriteToFile_unsafe(IO, FileName);
}
CGE_Bool CGE_IOWriteToFile_unsafe (CGE_IO *IO, const char *FileName) {
    FILE *File = fopen(FileName, "w");
	if (File == NULL) {
		return CGE_False;
	}
	fwrite(IO->StringBuf, IO->BufSize, 1,File);
	return CGE_True;
}

CGE_Object_id CGE_IOLoadResource (CGE_Context *Context, CGE_Object_id IOid, const char *FileName) {
	if (!CGE_IOReadFile(Context, IOid, FileName)) { // all safety checks are here
		return 0;
	}
  	CGE_IO *IO = &CGE_IndexObject(Context, IOid)->data.IO;  
	
}


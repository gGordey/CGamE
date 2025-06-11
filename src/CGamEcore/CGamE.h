/*
    Include this file to get all you need
*/

#ifndef CGamE_h
#define CGamE_h

#include <stdint.h>

#define CGE_DEF extern

typedef int CGE_Bool;
#define CGE_True    1
#define CGE_False   0

typedef uint32_t CGE_Object_id;
typedef struct CGE_Object CGE_Object;
typedef struct CGE_Context CGE_Context;

#include <CGamE_Context.h>
#include <CGamE_Object.h>

#endif
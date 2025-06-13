/*
    Include this file to get all you need
*/

#ifndef CGamE_h
#define CGamE_h

#include <stdint.h>

#define CGE_API extern
#define CGE_LOG_COL_RESET "\e[0m"

#define CGE_LOG_MSG_SUCCESS "[ + ]"
#define CGE_LOG_MSG_ERROR   "[ X ]"
#define CGE_LOG_MSG_WARNING "[ ! ]"

typedef int CGE_Bool;
#define CGE_True    1
#define CGE_False   0

typedef uint32_t CGE_Object_id;
// Main CGE_Context inteface is CGE_Object_id, not CGE_Object*
// That's because this way program have more checks to do and therefore its safer
// That insures that CGE_Object that it refers to actualy exist in the CGE_Context
// This adds extra layer of abstraction. But I decided to go for it
typedef uint32_t CGE_Object_tag;
typedef struct CGE_Object CGE_Object;
typedef struct CGE_Context CGE_Context;
typedef struct CGE_Hook CGE_Hook;
typedef struct CGE_Window CGE_Window;

typedef enum CGE_Message_type CGE_Message_type;
typedef enum CGE_Hook_type CGE_Hook_type;
typedef enum CGE_Object_type CGE_Object_type;

typedef void (*CGE_Hook_Callback_t)(CGE_Context*, CGE_Object_id, int64_t);
//  CGE_Context is context where everything is happening
//  int64_t is additional information needed for some functions
//      0 if not used

#include <CGamE_Tags.h>

#include <CGamE_Context.h>
#include <CGamE_Object.h>
#include <CGamE_Hook.h>
#include <CGamE_Log.h>
#include <CGamE_Window.h>

#endif
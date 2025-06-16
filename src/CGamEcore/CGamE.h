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

typedef uint32_t CGE_ui32_t;
typedef int32_t CGE_i32_t;
typedef uint8_t CGE_ui8_t;
typedef int8_t CGE_i8_t;

#ifdef _MSC_VER
    // mostly to shut up MSC
    typedef char *CGE_pVoid_t;
#else
    typedef void *CGE_pVoid_t;
#endif


// Main CGE_Context inteface is CGE_Object_id, not CGE_Object*
// That's because this way program have more checks to do and therefore its safer
// That insures that CGE_Object that it refers to actualy exist in the CGE_Context
// This adds extra layer of abstraction. But I decided to go for it
typedef CGE_ui32_t CGE_Object_id;
// Tags help controling objects (see CGamE_Tags.h)
typedef CGE_ui32_t CGE_Object_tag;
typedef struct CGE_Object CGE_Object;
// CGE_Context contains everything created by CGamE api functions
typedef struct CGE_Context CGE_Context;
// CGE_Hook allowes you to set Callback for specific event
typedef struct CGE_Hook CGE_Hook;
// CGE_Renderer contains all window-layer stuff
typedef struct CGE_Renderer CGE_Renderer;
// Component system is object with type CGE_OBJ_TYPE_COMPONENT_SYSTEM
typedef struct CGE_ComponentSystem CGE_ComponentSystem;

typedef enum CGE_Message_type CGE_Message_type;
typedef enum CGE_Hook_type CGE_Hook_type;
typedef enum CGE_Object_type CGE_Object_type;
// Used to interact with CGE_Context and spicify which vector you want 
typedef enum CGE_Context_TargetType CGE_Context_TargetType;
typedef enum CGE_Component_type CGE_Component_type;

//  CGE_Context is context where everything is happening
//  int64_t is additional information needed for some functions
//      0 if not used
//  CGE_Object_id is more information
//      0 if not used
typedef void (*CGE_Hook_Callback_t)(CGE_Context*, CGE_Object_id, int64_t);

#include <CGamE_Tags.h>

#include <CGamE_Context.h>
#include <CGamE_Object.h>
#include <CGamE_Hook.h>
#include <CGamE_Log.h>
#include <CGamE_Renderer.h>
#include <CGamE_Component.h>

#endif
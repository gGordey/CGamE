#pragma once

/*
	This is the only file needed to be included,
		as it includes everything CGamE has to offer	
*/

#ifdef _MSC_VER
	/*
		make CGE_API dllimport or dllexport,
		based on wether CGamE is beeing built or just included
	*/
    #ifdef CGE_BUILD
        #define CGE_API __declspec(dllexport)
    #else
        #define CGE_API __declspec(dllimport)
    #endif
#else
    #define CGE_API extern
#endif

#include <stddef.h>

typedef enum CGE_Result CGE_Result;
typedef struct CGE_Object CGE_Object; // CGamE_Object.h 
typedef struct CGE_Property CGE_Property; // CGamE_Prop.h 
typedef void (*CGE_PipelineFunc)(CGE_Object *); // CGamE_Pipeline.h
typedef struct CGE_Renderer CGE_Renderer;
typedef struct CGE_Vec2f { float x, y; } CGE_Vec2f;
typedef struct CGE_Vec3f { float x, y, z; } CGE_Vec3f;
typedef struct CGE_Vec2i { int x, y; } CGE_Vec2i;
typedef struct CGE_Vec3i { int x, y, z; } CGE_Vec3i;

#define TO_VEC2F(x, y) ((CGE_Vec2f){ .x = x, .y = y})
#define TO_VEC2I(x, y) ((CGE_Vec2i){ .x = x, .y = y})

#include "CGamE_Result.h"
#include "CGamE_Object.h"
#include "CGamE_Prop.h"
#include "CGamE_Pipeline.h"
#include "CGmaE_ObjRegistry.h"
#include "CGamE_Renderer.h"



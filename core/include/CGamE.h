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

typedef struct CGE_Object CGE_Object; // CGamE_Object.h 
typedef struct CGE_Property CGE_Property; // CGamE_Prop.h 
typedef void (*CGE_PipelineFunc)(CGE_Object *); // CGamE_Pipeline.h

#include "CGamE_Object.h"
#include "CGamE_Prop.h"
#include "CGamE_Pipeline.h"


#pragma once

/*
	Some functions might not only return something, but also `CGE_Result`. 
	This is done throgh a single static global varriable.
	To get result that functions gave use `CGE_GetLastResult`
	If function adds a result, it will be stated
*/

#include "CgamE.h"

enum CGE_Result {
	CGE_RES_SUCCESS = 0,
	CGE_RES_OUT_OF_MEMORY,
	CGE_RES_INVALID_PARAM,
	CGE_RES_GLFW_FAIL,
};


// Sets the last result to `res`
CGE_API void CGE_SetLastResult(
		CGE_Result res);

// Returns the last result that was set
CGE_API CGE_Result CGE_GetLastResult();

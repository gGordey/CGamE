#include "include/CGamE.h"

static CGE_Result last_result = 0;


void CGE_SetLastResult(
		CGE_Result res)
{
	last_result = res;
}

// Returns the last result that was set
CGE_Result CGE_GetLastResult() {
	return last_result;
}


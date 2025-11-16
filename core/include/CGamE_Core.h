#pragma once

/*
	This file provides defenitions for essential core functions.
	They are probably not ment to be used by anything but CGamE itself
*/

#include "CGamE.h"

// Startup routine for core
CGE_API void CGE_StartCore();

// Destroy everything and free resources
CGE_API void CGE_ShutdownCore();

CGE_API void CGE_CoreTerminate();

CGE_API int CGE_ShouldCoreTerminate();

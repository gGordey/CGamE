#pragma once

/*
	Objects Registry is used by CGamE to exeute objects pipeline each frame.
*/

#include "CGamE.h"

// Adds obj to Registry.
// returns its id or SIZE_MAX in case of error.
// This function adds last error
CGE_API size_t CGE_ObjectRegister(
		CGE_Object *obj);

// Marks objects by its id ad inactive.
// inactive objects in registry will be rewriten with another objects.
// This function adds last error
CGE_API void CGE_ObjectUnregister(
		size_t id);			// id of an object to be removed

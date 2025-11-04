#pragma once

/*
	Properties are basically fields of object.
	They are passed as arguments for function of object pipeline.
	You can create your own properties.
	Pipeline function can require having certain fields to work.
	CGE_Property is actually metadata, a key for property data in CGE_Object.
*/

struct CGE_Property {
	char *name; 	// property name
	size_t offset; 	// property offset in bytes 
	size_t size; 	// property size in bytes
};

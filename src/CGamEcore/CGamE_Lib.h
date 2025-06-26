#ifndef CGamE_lib_h
#define CGamE_lib_h

#include <CGamE.h>

CGE_API CGE_Bool CGE_IsAlpha(char c);
CGE_API CGE_Bool CGE_IsNumeric(char c);

CGE_API int CGE_Parse(const char *str);

// Basic Lerp
CGE_API float CGE_Lerp(float a, float b, float t);


#endif

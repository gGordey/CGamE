#ifndef CGamE_vector_h
#define CGamE_vector_h

#include <CGamE.h>

struct CGE_Vec2 {
    float x, y;
};
struct CGE_Vec3 {
    float x, y, z;
};
struct CGE_Vec4 {
    float x, y, z, w;
};

CGE_API CGE_Vec2 CGE_newVec2 (float x, float y);
CGE_API CGE_Vec3 CGE_newVec3 (float x, float y, float z);
CGE_API CGE_Vec4 CGE_newVec4 (float x, float y, float z, float w);

#endif
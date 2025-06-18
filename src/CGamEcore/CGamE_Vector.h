#ifndef CGamE_vector_h
#define CGamE_vector_h

struct CGE_Vec2 {
    float x, y;
};
struct CGE_Vec3 {
    float x, y, z;
};
struct CGE_Vec4 {
    float x, y, z, w;
};

static inline CGE_Vec2 CGE_newVec2 (float x, float y) {
    return (CGE_Vec2){x,y};
}
static inline CGE_Vec3 CGE_newVec3 (float x, float y, float z) {
    return (CGE_Vec3){x,y,z};
}
static inline CGE_Vec4 CGE_newVec4 (float x, float y, float z, float w) {
    return (CGE_Vec4){x,y,z,w};
}

#endif
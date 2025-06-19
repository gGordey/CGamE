#include <CGamE.h>

CGE_Vec2 CGE_newVec2 (float x, float y) {
    return (CGE_Vec2){x,y};
}
CGE_Vec3 CGE_newVec3 (float x, float y, float z) {
    return (CGE_Vec3){x,y,z};
}
CGE_Vec4 CGE_newVec4 (float x, float y, float z, float w) {
    return (CGE_Vec4){x,y,z,w};
}
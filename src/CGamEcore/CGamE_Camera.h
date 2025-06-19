#ifndef CGamE_camera_h
#define CGamE_camera_h

#include <CGamE.h>

struct CGE_Camera {
    CGE_Vec2 Size;
    CGE_Vec2 Pos;
};


// returns id of new CGE_Camera
CGE_API CGE_Object_id CGE_CreateCamera (CGE_Context *Context, CGE_Vec2 Size);

CGE_API CGE_Bool CGE_IsPointInCameraRange (CGE_Context *Context, CGE_Object_id CameraId, CGE_Vec2 Point);
// unsafe version of CGE_IsPointInCameraRange
CGE_API CGE_Bool CGE_IsPointInCameraRange_unsafe (CGE_Camera *Camera, CGE_Vec2 Point);

#endif
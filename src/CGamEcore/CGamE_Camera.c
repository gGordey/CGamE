#include <CGamE.h>

CGE_Object_id CGE_CreateCamera (CGE_Context *Context, CGE_Vec2 Size) {
    CGE_Object_id CameraId = CGE_CreateObject(Context, CGE_OBJ_TYPE_CAMERA, 0);
    *((CGE_Camera*)CGE_GetObjectData(Context, CameraId)) = (CGE_Camera){
        .Pos = CGE_newVec2(0,0),
        .Size = Size
    };
    return CameraId;  
}

CGE_Bool CGE_IsPointInCameraRange (CGE_Context *Context, CGE_Object_id CameraId, CGE_Vec2 Point) {
    if (CGE_GetObjectType(Context, CameraId) != CGE_OBJ_TYPE_CAMERA) {
        CGE_LogErrorWrongObjectType (
            Context, CameraId,
            "CGE_OBJ_TYPE_CAMERA", "CGE_IsPointInCameraRange"
        );
        return CGE_False;
    }
    CGE_Camera *Camera = (CGE_Camera*)CGE_GetObjectData(Context, CameraId);
    const CGE_Vec2 CameraTopLeft = CGE_newVec2(
        Camera->Pos.x - Camera->Size.x/2,
        Camera->Pos.y - Camera->Size.y/2
    );
    const CGE_Vec2 CameraBottomRight = CGE_newVec2(
        Camera->Pos.x + Camera->Size.x/2,
        Camera->Pos.y + Camera->Size.y/2
    );
    return  Point.x > CameraTopLeft.x &&
            Point.x < CameraBottomRight.x &&
            Point.y > CameraTopLeft.y &&
            Point.y < CameraBottomRight.y;
}

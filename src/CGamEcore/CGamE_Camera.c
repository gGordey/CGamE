#include <CGamE.h>

CGE_Object_id CGE_CreateCamera (CGE_Context *Context, CGE_Vec2 Size) {
    CGE_Object_id CameraId = CGE_CreateObject(Context, CGE_OBJ_TYPE_CAMERA, 0);
    CGE_IndexObject(Context, CameraId)->data.Camera = (CGE_Camera){
        .Pos = CGE_newVec2(0,0),
        .Size = Size
    };
    return CameraId;  
}

CGE_Bool CGE_IsPointInCameraRange (CGE_Context *Context, CGE_Object_id CameraId, CGE_Vec2 Point) {
    CGE_Object *CameraObj = CGE_IndexObject(Context, CameraId);
    if (CameraObj == NULL) {
        return CGE_False;
    }
    if (CameraObj->type != CGE_OBJ_TYPE_CAMERA) {
        CGE_LogErrorWrongObjectType (
            Context, CameraId,
            "CGE_OBJ_TYPE_CAMERA", "CGE_IsPointInCameraRange"
        );
        return CGE_False;
    }
    CGE_Camera *Camera = &CameraObj->data.Camera;
    return CGE_IsPointInCameraRange_unsafe(Camera, Point);
}
CGE_Bool CGE_IsPointInCameraRange_unsafe (CGE_Camera *Camera, CGE_Vec2 Point) {
    return  Point.x > Camera->Pos.x - Camera->Size.x/2 &&
            Point.x < Camera->Pos.x + Camera->Size.x/2 &&
            Point.y > Camera->Pos.y - Camera->Size.y/2 &&
            Point.y < Camera->Pos.y + Camera->Size.y/2;
}

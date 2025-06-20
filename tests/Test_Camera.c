#include <CGamE.h>
#include "CGamE_Test.h"

int main(void) {
    int testId = 0;
    CGE_Context Context = CGE_CreateContext();

    CGE_Object_id CameraId = CGE_CreateCamera(&Context, CGE_newVec2(100, 102));
        CGE_Camera *Camera = &CGE_IndexObject(&Context, CameraId)->data.Camera;
       
    // test 0: Camera created and index successfuly
    CGE_LogResultTest(testId, Camera != NULL);
    // test 1: Camera data filled
    ++testId;
    CGE_LogResultTest(testId, Camera->Size.x == 100 && Camera->Size.y == 102);
    // test 2: Point checks
    ++testId;
    CGE_LogResultTest(testId, CGE_IsPointInCameraRange(&Context, CameraId, CGE_newVec2(0,0)));
    // test 3:
    ++testId;
    CGE_LogResultTest(testId, CGE_IsPointInCameraRange(&Context, CameraId, CGE_newVec2(-49,49)));
    // test 4:
    ++testId;
    CGE_LogResultTest(testId, !CGE_IsPointInCameraRange(&Context, CameraId, CGE_newVec2(80,100)));
    // test 5:
    ++testId;
    CGE_LogResultTest(testId, !CGE_IsPointInCameraRange(&Context, CameraId, CGE_newVec2(100,0)));
    // test 6: Handle invalid id
    ++testId;
    CGE_LogResultTest(testId, !CGE_IsPointInCameraRange(&Context, 1234, CGE_newVec2(0,0)));

    CGE_DestroyContext(&Context);
    CGE_LogString("ALL TEST ARE FINISHED!\n", CGE_MSG_TYPE_INFO);
}
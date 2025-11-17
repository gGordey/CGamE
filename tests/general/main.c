#include "../../core/include/CGamE.h"
#include "include/CGamE_Object.h"

#include <stdio.h>

extern void CGE_RenderersPollEvents();
extern void CGE_StartCore();
extern void CGE_ShutdownCore();
extern void CGE_ExecuteObjectRegistry();
extern void CGE_DrawRenderable();

int main() {
	printf("START!\n");

	CGE_StartCore();
	
	CGE_Object *obj = CGE_CreateObject(2,0,sizeof(CGE_Renderer*)*2);
	if (obj == NULL) {
		printf("ggwp\n");
		return -1;
	}
	printf("Obj Created\n");

	CGE_Property obj_props[2] = {
		(CGE_Property){.name = "rend", .offset = 0, .size = sizeof(CGE_Renderer*)},
		(CGE_Property){.name = "rend1",.offset = 0, .size = sizeof(CGE_Renderer*)},
	};
	CGE_ObjectFillProps(obj, obj_props);
	printf("Props filed\n");

	CGE_Renderer **rend  = (CGE_Renderer**)CGE_ObjectPropertyDataPtr(obj, "rend");
	CGE_Renderer **rend1 = (CGE_Renderer**)CGE_ObjectPropertyDataPtr(obj, "rend1");
	printf("Rend prop found\n");
	
	*rend  = CGE_CreateRenderer("Test window", TO_VEC2I(500, 500));
	//*rend1 = 1; //CGE_CreateRenderer("Test window1", TO_VEC2I(800, 200));
	if (!*rend) {//if (!(*rend1 && *rend)) {
		printf("rends kinda dont work\n");
		return -1;
	}
	printf("Renderer Created\n");

	while(!CGE_ShouldCoreTerminate()) {
		CGE_ExecuteObjectRegistry();	
		CGE_DrawRenderable();
		CGE_RenderersPollEvents();
	}

	CGE_ShutdownCore();
	printf("END!!\n");
}
	

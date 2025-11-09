#include "../../core/include/CGamE.h"

extern void CGE_StartupCore();
extern void CGE_ShutdownCore();

int main() {
	CGE_StartupCore();
	
	CGE_Object obj = CGE_CreateObject(1,1,sizeof(CGE_Renderer));

	CGE_Property obj_props[1] = {(CGE_Property){.name = "rend", .offset = 0, .size = sizeof(CGE_Renderer)}};

	CGE_Renderer *rend = (CGE_Renderer*)CGE_ObjectPropertyDataPtr(&obj, "rend");
	
	*rend = CGE_CreateRenderer("Test window", TO_VEC2I(500, 500));

	while(1) {

	}

	CGE_ShutdownCore();
}
	

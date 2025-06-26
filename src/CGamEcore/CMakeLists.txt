cmake_minimum_required(VERSION 3.10)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Runtime")
set(PROJECT_NAME "CGamEcore")
set(SHARED_LIB_NAME "CGamEruntime")

project(${SHARED_LIB_NAME})

set(CCT_DIR "../../include/CommonCTypes")

add_library(${SHARED_LIB_NAME} SHARED 
    CGamE_Context.c
    CGamE_Object.c
    CGamE_Hook.c
    CGamE_Log.c
    CGamE_Tags.c
    CGamE_Renderer.c
    CGamE_Component.c
    CGamE_IO.c
    CGamE_Vector.c
    CGamE_Camera.c
	CGamE_Resource.c
	CGamE_Lib.c 
)
target_link_libraries(${SHARED_LIB_NAME} 
    CCT 
	CGE_Graphics
)
set_target_properties(${SHARED_LIB_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    PREFIX ""
)

add_executable(CGamEcore
    CGamEmain.c
)
set_target_properties(CGamEcore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_link_libraries(CGamEcore
    ${SHARED_LIB_NAME}
)

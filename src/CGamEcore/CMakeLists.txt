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
)
target_link_libraries(${SHARED_LIB_NAME} 
    CCT 
    glfw 
    "opengl32.lib"
)
set_target_properties(${SHARED_LIB_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
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

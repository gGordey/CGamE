cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")

set(CMAKE_C_FLAGS "-O3 -L .")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(PROJECT_NAME "CGamEcore")

project(${PROJECT_NAME})

include_directories(.)
include_directories(../../include)
set(CCT_DIR "../../include/CommonCTypes")

add_library(CCT STATIC ${CCT_DIR}/mat.c ${CCT_DIR}/option.c ${CCT_DIR}/string.c ${CCT_DIR}/vector.c)

add_executable(${PROJECT_NAME} CGamEmain.c CGamE_Object.c CGamE_Context.c CGamE_Log.c CGamE_Hook.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_link_libraries(${PROJECT_NAME} CCT)

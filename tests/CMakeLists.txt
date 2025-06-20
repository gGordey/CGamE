cmake_minimum_required(VERSION 3.10)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Tests")

project(CGamEtests)

add_executable(HookTest Test_Hook.c)
target_link_libraries(HookTest CGamEruntime)
set_target_properties(HookTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
add_executable(CameraTest Test_Camera.c)
target_link_libraries(CameraTest CGamEruntime)
set_target_properties(CameraTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
add_executable(ComponentSystemTest Test_Component.c)
target_link_libraries(ComponentSystemTest CGamEruntime)
set_target_properties(ComponentSystemTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
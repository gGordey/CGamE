cmake_minimum_required(VERSION 3.10)


set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Sandbox")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(PROJECT_NAME "CGamEsandbox")

project(${PROJECT_NAME})

include_directories(include)

add_executable(${PROJECT_NAME} main.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    CCT
    glfw
    CGamEruntime
)

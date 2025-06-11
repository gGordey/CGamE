cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")

set(CMAKE_C_FLAGS "-O3 -L .")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(PROJECT_NAME "CGamE")

project(${PROJECT_NAME})

include_directories(include)

add_subdirectory(src/CGameEcore)

file(COPY "${LIB_DIR}/glfw3.dll" DESTINATION "${OUTPUT_DIR}")
file(COPY "${LIB_DIR}/glad.dll" DESTINATION "${OUTPUT_DIR}")


add_executable(${PROJECT_NAME} ${SRC_DIR}/main.c)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${LIB_DIR}/glad.dll
    ${LIB_DIR}/glfw3.dll
)
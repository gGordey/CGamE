cmake_minimum_required(VERSION 4.0)

project(CGamE_GeneralTest)

add_executable(general main.c)

target_link_libraries(general PRIVATE CGamEcore)

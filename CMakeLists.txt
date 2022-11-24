cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 11)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(Template)
add_compile_definitions(LOCAL)

add_executable(P6348 Luogu/P6348.cpp)
add_executable(P3178 Luogu/P3178.cpp)
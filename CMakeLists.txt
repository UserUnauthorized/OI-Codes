cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(P3376 Luogu/P3376.cpp)
add_executable(P3805 Luogu/P3805.cpp)
add_executable(P2740 P2740.cpp)
add_executable(P2261 P2261.cpp)
add_executable(P5325 P5325.cpp)
add_executable(P4178 Luogu/P4178.cpp)
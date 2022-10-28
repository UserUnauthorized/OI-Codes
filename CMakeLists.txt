cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 11)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(P1082 Luogu/P1082.cpp)
add_executable(P1516 Luogu/P1516.cpp)
add_executable(A HZ-contests/277/A.cpp)
add_executable(B HZ-contests/277/B.cpp)
add_executable(C HZ-contests/277/C.cpp)
add_executable(D HZ-contests/277/D.cpp)
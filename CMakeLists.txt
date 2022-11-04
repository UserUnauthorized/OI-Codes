cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 11)

#MATH(EXPR stack_size "1024*1024*1024")
#set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

#add_executable(segTree Template/segTree.cpp Template/segTree.h)
add_executable(P6348 Luogu/P6348.cpp)
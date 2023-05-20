cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(80.5 HZ/80.5.cpp)
add_executable(P9118 Luogu/P9118.cpp)
add_executable(P3383 Luogu/P3383.cpp)
add_executable(test ../Users/hzoi/Documents/test.cpp)
add_executable(P7453 Luogu/P7453.cpp)
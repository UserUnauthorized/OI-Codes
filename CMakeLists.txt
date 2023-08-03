cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(P3324 P3324.cpp)
add_executable(P4311 Luogu/P4311.cpp)
add_executable(AT_agc017_d AtCoder/AT_agc017_d.cpp)
add_executable(P2197 Luogu/P2197.cpp)
add_executable(1850D CodeForces/1850D.cpp)
add_executable(1850F CodeForces/1850F.cpp)
add_executable(AT_arc096_c AtCoder/AT_arc096_c.cpp)
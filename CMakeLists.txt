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
add_executable(P4859 Luogu/P4859.cpp)

add_executable(51.4 HZ/51.4.cpp)
add_executable(P4827 Luogu/P4827.cpp)

add_executable(73.5 HZ/73.5.cpp)
add_executable(SP7363 Luogu/SP7363.cpp)
add_executable(73.7 HZ/73.7.cpp)
add_executable(896C CodeForces/896C.cpp)
add_executable(896B CodeForces/896B.cpp)
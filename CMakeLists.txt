cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(P5038 Luogu/P5038.cpp)
add_executable(1174E CodeForces/1174E.cpp)
add_executable(P4859 Luogu/P4859.cpp)
add_executable(1626F CodeForces/1626F.cpp)
add_executable(915G CodeForces/915G.cpp)
add_executable(838D CodeForces/838D.cpp)
add_executable(915G-2 CodeForces/915G-2.cpp)
add_executable(653G CodeForces/653G.cpp)
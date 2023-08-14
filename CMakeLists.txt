cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(AT_arc131_c AtCoder/AT_arc131_c.cpp)
add_executable(1779C CodeForces/1779C.cpp)
add_executable(1845D CodeForces/1845D.cpp)
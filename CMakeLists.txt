cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(1737E CodeForces/1737E.cpp)
add_executable(AT_abc238_d AtCoder/AT_abc238_d.cpp)
add_executable(AT_abc313_f AtCoder/AT_abc313_f.cpp)
add_executable(caddi2018_a AtCoder/caddi2018_a.cpp)
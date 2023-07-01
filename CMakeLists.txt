cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

include_directories(LocalInclude)
add_compile_definitions(CLION)
add_compile_definitions(LOCAL)

add_executable(48.2 HZ/48.2.cpp)
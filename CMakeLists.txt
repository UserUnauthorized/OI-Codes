cmake_minimum_required(VERSION 3.13)
project(OI-Codes)
set(CMAKE_CXX_STANDARD 11)

MATH(EXPR stack_size "64*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(D HZ-contests/264/D.cpp)
add_executable(D_S HZ-contests/264/D_S.cpp)
add_executable(E HZ-contests/264/E.cpp)
add_executable(F HZ-contests/264/F.cpp)
add_executable(G HZ-contests/264/G.cpp)
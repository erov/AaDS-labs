cmake_minimum_required(VERSION 3.19)
project(lca_problem_revisited)

set(CMAKE_CXX_STANDARD 17)
MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(lca_problem_revisited main.cpp)
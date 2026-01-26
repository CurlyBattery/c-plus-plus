cmake_minimum_required(VERSION 3.10)
project(MathLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MathLib STATIC library.cpp)

add_executable(test_mathlib test_main.cpp)

target_link_libraries(test_mathlib MathLib)
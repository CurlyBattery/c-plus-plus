cmake_minimum_required(VERSION 3.10)
project(MathLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MathLib STATIC library.cpp)
target_include_directories(MathLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
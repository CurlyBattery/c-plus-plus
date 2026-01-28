cmake_minimum_required(VERSION 4.1)
project(pz15)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(MathLib)

add_executable(pz15 main.cpp)

target_link_libraries(pz15 MathLib)
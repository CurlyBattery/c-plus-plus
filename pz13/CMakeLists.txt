cmake_minimum_required(VERSION 4.1)
project(pz13)

set(CMAKE_CXX_STANDARD 20)

add_executable(pz13 WIN32 main.cpp)

target_link_libraries(pz13 user32 gdi32)
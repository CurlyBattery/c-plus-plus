cmake_minimum_required(VERSION 3.10)
project(FactorialLib)

set(CMAKE_CXX_STANDARD 20)

add_library(FactorialLib SHARED library.cpp)
target_compile_definitions(FactorialLib PRIVATE FACTORIALLIB_EXPORTS)

add_executable(TestFactorial test_main.cpp)

target_link_libraries(TestFactorial FactorialLib)

if(WIN32)
    add_custom_command(TARGET TestFactorial POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:FactorialLib>
            $<TARGET_FILE_DIR:TestFactorial>
    )
endif()
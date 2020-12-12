cmake_minimum_required(VERSION 3.10)

project(aoc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(1 1.cpp)
add_executable(2 2.cpp)
add_executable(3 3.cpp)

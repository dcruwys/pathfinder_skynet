cmake_minimum_required(VERSION 3.4)
project(HW1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Gameboard.cpp Gameboard.h BFS.h BFS.cpp)
add_executable(HW1 ${SOURCE_FILES})
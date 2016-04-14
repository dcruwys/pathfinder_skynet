cmake_minimum_required(VERSION 3.4)
project(pathfinder_skynet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Heuristic.h IDA.h SlidingTile.cpp SlidingTile.h BFS.h DFS.h Gameboard.cpp Gameboard.h NaryTree.h NaryTree.cpp)
add_executable(pathfinder_skynet ${SOURCE_FILES})
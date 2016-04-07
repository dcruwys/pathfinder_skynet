cmake_minimum_required(VERSION 3.4)
project(pathfinder_skynet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Gameboard.cpp Gameboard.h BFS.h Heuristic.h DFS.h NaryTree.h NaryTree.cpp IDA.h SlidingTile.cpp SlidingTile.h)
add_executable(pathfinder_skynet ${SOURCE_FILES})
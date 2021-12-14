cmake_minimum_required(VERSION 3.20)
project (hardtree)

set(CMAKE_CXX_STANDARD 14)

add_executable(hardtree main.cpp Tree.h list.h TreeException.h Tree.cpp list.cpp)

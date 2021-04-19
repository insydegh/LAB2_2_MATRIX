cmake_minimum_required(VERSION 3.17)
project(MAT)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Catch2)




add_executable(MAT main.cpp DynamicArray.h LinkedList.h Sequence.h ArraySequence.h ListSequence.h Complex.h Matrix.h Tests.cpp catch.hpp menu.h)


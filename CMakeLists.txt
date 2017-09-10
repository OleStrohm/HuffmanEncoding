cmake_minimum_required(VERSION 3.8)
project(huffmanTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp node.cpp node.h tree.cpp tree.h bitarray.cpp bitarray.h)
add_executable(huffmanTree ${SOURCE_FILES})
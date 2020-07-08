cmake_minimum_required(VERSION 3.6)
project(BasicDE)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES line.cpp line.h individual.cpp individual.h main3.cpp)
add_executable(BasicDE ${SOURCE_FILES})
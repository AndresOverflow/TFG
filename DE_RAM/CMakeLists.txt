cmake_minimum_required(VERSION 3.16)
project(DE_RAM)

set(CMAKE_CXX_STANDARD 14)

add_executable(DE_RAM main.cpp Population.h Population.cpp Individual.h Individual.cpp  FileReader.h FileReader.cpp DE.cpp DE.h)
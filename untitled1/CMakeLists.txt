cmake_minimum_required(VERSION 3.16)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp Population.cpp Population.h Individual.cpp Individual.h FileReader.h FileReader.cpp MutationProbabilityTable.h MutationProbabilityTable.cpp TripletPST.h TripletPST.cpp)
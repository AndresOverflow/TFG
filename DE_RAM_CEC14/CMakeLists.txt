cmake_minimum_required(VERSION 3.16)
project(DE_RAM_CEC14)

set(CMAKE_CXX_STANDARD 11)

add_executable(DED_RAM_CEC14 main.cpp Population.cpp Population.h Individual.cpp Individual.h FileReader.h FileReader.cpp MutationProbabilityTable.h MutationProbabilityTable.cpp TripletPST.h TripletPST.cpp cec14_test_func.cpp armadillo.h)
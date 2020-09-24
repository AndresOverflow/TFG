cmake_minimum_required(VERSION 3.16)
project(DE_RAM_JAPDE_CEC14_HSPR)

set(CMAKE_CXX_STANDARD 14)

add_executable(DE_RAM_JAPDE_CEC14_HSPR main.cpp armadillo.h cec14_test_func.cpp Individual.h Individual.cpp Population.h Population.cpp MutationProbabilityTable.h MutationProbabilityTable.cpp TableFandCR.h TableFandCR.cpp TripletPST.h TripletPST.cpp)
cmake_minimum_required(VERSION 3.16)
project(DE_RAM_JAPDE_CEC14_HSPR)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_BUILD_TYPE distribution)
SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
SET(CMAKE_C_FLAGS_DISTRIBUTION "-O3")

add_executable(DE_RAM_JAPDE_CEC14_HSPR main.cpp armadillo.h cec14_test_func.cpp Individual.h Individual.cpp Population.h Population.cpp MutationProbabilityTable.h MutationProbabilityTable.cpp TableFandCR.h TableFandCR.cpp TripletPST.h TripletPST.cpp)
# 3min 54 segs sin opt-3
#43 segs
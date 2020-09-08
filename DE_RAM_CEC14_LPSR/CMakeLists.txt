cmake_minimum_required(VERSION 3.16)
project(DE_RAM_CEC14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

add_executable(DED_RAM_CEC14 main.cpp Population.cpp Population.h Individual.cpp Individual.h MutationProbabilityTable.h MutationProbabilityTable.cpp TripletPST.h TripletPST.cpp cec14_test_func.cpp armadillo.h)
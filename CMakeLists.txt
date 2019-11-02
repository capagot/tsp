cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(TSP)

###############################################################################
# Select between Release and Debug
###############################################################################

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
    message("Building DEBUG version")
else(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DNDEBUG)
    message("Building RELEASE version")
endif()

###############################################################################
# Enforce c++17 standard
###############################################################################

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_STANDARD 17)          # requires c++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # does not fallback if the compiler does not cupport c++17
set(CMAKE_CXX_EXTENSIONS OFF)       # sets -std=c++17 instead of -std=g++17

###############################################################################
# Prepares the application
###############################################################################

add_executable(tsp
               ${PROJECT_SOURCE_DIR}/core/main.cpp
               ${PROJECT_SOURCE_DIR}/core/application.cpp
               ${PROJECT_SOURCE_DIR}/tsplib_reader/tsplib_reader.cpp
               ${PROJECT_SOURCE_DIR}/solvers/tsp_solver.cpp
               ${PROJECT_SOURCE_DIR}/solvers/tsp_brute_force.cpp
               ${PROJECT_SOURCE_DIR}/solvers/tsp_nearest_neighbor.cpp)

target_include_directories(tsp
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/tsplib_reader
                           ${PROJECT_SOURCE_DIR}/solvers
                           ${PROJECT_SOURCE_DIR}/third_party/ann_1.1.2/include/ANN)

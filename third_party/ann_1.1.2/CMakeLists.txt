cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(ANNLib LANGUAGES CXX )

###############################################################################
# Enforce c++17 standard
###############################################################################

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O3 -g0")
set(CMAKE_CXX_STANDARD 17)          # requires c++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # does not fallback if the compiler does not cupport c++17
set(CMAKE_CXX_EXTENSIONS OFF)       # sets -std=c++17 instead of -std=g++17

###############################################################################
# Prepares the application
###############################################################################

add_library(ANN STATIC
            "${PROJECT_SOURCE_DIR}/src/kd_split.cpp"
            "${PROJECT_SOURCE_DIR}/src/kd_util.cpp"
            "${PROJECT_SOURCE_DIR}/src/perf.cpp"
            "${PROJECT_SOURCE_DIR}/src/brute.cpp"
            "${PROJECT_SOURCE_DIR}/src/bd_pr_search.cpp"
            "${PROJECT_SOURCE_DIR}/src/bd_search.cpp"
            "${PROJECT_SOURCE_DIR}/src/kd_pr_search.cpp"
            "${PROJECT_SOURCE_DIR}/src/bd_tree.cpp"
            "${PROJECT_SOURCE_DIR}/src/kd_fix_rad_search.cpp"
            "${PROJECT_SOURCE_DIR}/src/ANN.cpp"
            "${PROJECT_SOURCE_DIR}/src/kd_tree.cpp"
            "${PROJECT_SOURCE_DIR}/src/bd_fix_rad_search.cpp"
            "${PROJECT_SOURCE_DIR}/src/kd_search.cpp"
            "${PROJECT_SOURCE_DIR}/src/kd_dump.cpp")

target_include_directories(ANN
                           PRIVATE
                           "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/include")

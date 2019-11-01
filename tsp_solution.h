#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H

#include <limits>
#include <vector>

struct TSPSolution {
    TSPSolution() : cost(std::numeric_limits<float>::infinity()) {}

    float cost;
    std::vector<int> nodes;
};

#endif  // TSP_SOLUTION_H

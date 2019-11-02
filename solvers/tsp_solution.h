#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H

#include <limits>
#include <vector>

struct TSPSolution {
    float cost;
    std::vector<int> nodes;
};

#endif  // TSP_SOLUTION_H

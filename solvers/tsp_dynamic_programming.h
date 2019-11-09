#ifndef TSP_DYNAMIC_PROGRAMMING_H
#define TSP_DYNAMIC_PROGRAMMING_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <list>

#include "tsp_solution.h"
#include "tsp_solver.h"
#include "tsplib_reader.h"

class TSPDynamicProgramming : public TSPSolver {
   public:
    TSPDynamicProgramming(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution);
    ~TSPDynamicProgramming();
    void solve() override;

private:
    using Set = unsigned int;

    int solveRecursive(const Set s, int t);

    static const int max_n_;
    std::vector<std::vector<int>> opt_;
};

#endif  // TSP_DYNAMIC_PROGRAMMING_H

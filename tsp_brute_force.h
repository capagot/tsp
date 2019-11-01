#ifndef TSP_BRUTE_FORCE_H
#define TSP_BRUTE_FORCE_H

#include <algorithm>
#include <iostream>

#include "tsp_solution.h"
#include "tsp_solver.h"
#include "tsplib_reader.h"

class TSPBruteForce : public TSPSolver {
   public:
    TSPBruteForce(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution);
    ~TSPBruteForce();
    void solve() override;

   private:
    long factorial(long n);
    void pathPermutation(int i);
    std::vector<int> nodes_;
};

#endif  // TSP_BRUTE_FORCE_H

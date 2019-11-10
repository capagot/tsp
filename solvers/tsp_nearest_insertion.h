#ifndef TSP_NEAREST_INSERTION_H
#define TSP_NEAREST_INSERTION_H

#include <algorithm>
#include <iostream>
#include <list>

#include "tsp_solution.h"
#include "tsp_solver.h"
#include "tsplib_reader.h"

class TSPNearestInsertion : public TSPSolver {
   public:
    TSPNearestInsertion(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution);
    ~TSPNearestInsertion();
    void solve() override;
};

#endif  // TSP_NEAREST_INSERTION_H

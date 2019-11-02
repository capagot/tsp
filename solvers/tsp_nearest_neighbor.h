#ifndef TSP_NEAREST_NEIGHBOR_H
#define TSP_NEAREST_NEIGHBOR_H

#include <algorithm>
#include <iostream>
#include <list>

#include "tsp_solution.h"
#include "tsp_solver.h"
#include "tsplib_reader.h"

class TSPNearestNeighbor : public TSPSolver {
   public:
    TSPNearestNeighbor(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution);
    ~TSPNearestNeighbor();
    void solve() override;
};

#endif  // TSP_NEAREST_NEIGHBOR_H

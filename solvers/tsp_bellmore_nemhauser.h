#ifndef TSP_BELLMORE_NEMHAUSER_H
#define TSP_BELLMORE_NEMHAUSER_H

#include <algorithm>
#include <iostream>
#include <list>

#include "tsp_solution.h"
#include "tsp_solver.h"
#include "tsplib_reader.h"

class TSPBellmoreNemhauser : public TSPSolver {
   public:
    TSPBellmoreNemhauser(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution);
    ~TSPBellmoreNemhauser();
    void solve() override;
};

#endif  // TSP_BELLMORE_NEMHAUSER_H

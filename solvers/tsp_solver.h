#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "tsp_solution.h"
#include "tsplib_reader.h"

class TSPSolver {
   public:
    enum class TSPSolverType { BRUTE_FORCE, NEAREST_NEIGHBOR, BELLMORE_NEMHAUSER };

    TSPSolver(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution, TSPSolverType tsp_solver_type);
    virtual void solve() = 0;
    virtual ~TSPSolver();

   protected:
    tlb::TSPLibData& tsplib_data_;
    TSPSolution& tsp_solution_;
    TSPSolverType tsp_solver_type_;
};

#endif  // TSP_SOLVER_H

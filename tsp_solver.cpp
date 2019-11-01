#include "tsp_solver.h"

TSPSolver::TSPSolver(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution, TSPSolverType tsp_solver_type)
    : tsplib_data_(tsplib_data), tsp_solution_(tsp_solution), tsp_solver_type_(tsp_solver_type) {}

TSPSolver::~TSPSolver() {}

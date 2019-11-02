#include "tsp_nearest_neighbor.h"

TSPNearestNeighbor::TSPNearestNeighbor(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution)
    : TSPSolver(tsplib_data, tsp_solution, TSPSolver::TSPSolverType::NEAREST_NEIGHBOR) {

    for (int i = 1; i < tsplib_data_.dimension; ++i)
        nodes_.push_back(i);
}

TSPNearestNeighbor::~TSPNearestNeighbor() {}

void TSPNearestNeighbor::solve() {
    std::cout << "Nearest Neighbor TSP solver.\n";

    tsp_solution_.nodes[0] = 0;
    tsp_solution_.cost = 0.0;
    int row = 0;

    for (int i = 1; i < tsplib_data_.dimension; ++i) {
        std::list<int>::const_iterator best_node;
        double best_cost = std::numeric_limits<double>::infinity();

        for (auto it = nodes_.cbegin(); it != nodes_.cend(); ++it) {
            if (tsplib_data_.full_matrix[row][*it] < best_cost) {
                best_node = it;
                best_cost = tsplib_data_.full_matrix[row][*it];
            }
        }

        row = *best_node;
        tsp_solution_.nodes[i] = row;
        tsp_solution_.cost += best_cost;
        nodes_.erase(best_node);
    }

    tsp_solution_.cost += tsplib_data_.full_matrix[row][0];
}

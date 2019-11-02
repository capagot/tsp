#include "tsp_nearest_neighbor.h"

TSPNearestNeighbor::TSPNearestNeighbor(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution)
    : TSPSolver(tsplib_data, tsp_solution, TSPSolver::TSPSolverType::NEAREST_NEIGHBOR) {}

TSPNearestNeighbor::~TSPNearestNeighbor() {}

void TSPNearestNeighbor::solve() {
    std::cout << "Nearest Neighbor TSP solver.\n";

    std::list<int> candidate_nodes;
    for (int i = 1; i < tsplib_data_.dimension; ++i) 
        candidate_nodes.push_back(i);

    std::vector<int> solution_nodes(tsplib_data_.dimension);
    solution_nodes[0] = 0;  // starts at node 0

    double solution_cost = 0.0;

    for (int i = 1; i < tsplib_data_.dimension; ++i) {
        std::list<int>::const_iterator candidate_node;
        double best_cost = std::numeric_limits<double>::infinity();

        for (auto it = candidate_nodes.cbegin(); it != candidate_nodes.cend(); ++it) {
            if (tsplib_data_.full_matrix[solution_nodes[i - 1]][*it] < best_cost) {
                candidate_node = it;
                best_cost = tsplib_data_.full_matrix[solution_nodes[i - 1]][*it];
            }
        }

        solution_nodes[i] = *candidate_node;
        solution_cost += best_cost;
        candidate_nodes.erase(candidate_node);
    }

    solution_cost += tsplib_data_.full_matrix[solution_nodes[solution_nodes.size() - 1]][0];

    for (int i = 0; i < solution_nodes.size(); ++i) 
        tsp_solution_.nodes[i] = solution_nodes[i];
    tsp_solution_.nodes[tsp_solution_.nodes.size()] = solution_nodes[0];

    tsp_solution_.cost = solution_cost;
}

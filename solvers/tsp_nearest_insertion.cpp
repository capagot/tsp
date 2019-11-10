#include "tsp_nearest_insertion.h"

TSPNearestInsertion::TSPNearestInsertion(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution)
    : TSPSolver(tsplib_data, tsp_solution, TSPSolver::TSPSolverType::NEAREST_INSERTION) {}

TSPNearestInsertion::~TSPNearestInsertion() {}

void TSPNearestInsertion::solve() {
    std::cout << "Nearest Insertion TSP solver.\n";

    int initial_node = 0;

    std::list<int> candidate_nodes;
    for (int i = 0; i < tsplib_data_.dimension; ++i) 
        if (i != initial_node) 
            candidate_nodes.push_back(i);

    std::vector<int> solution_nodes;
    solution_nodes.resize(tsplib_data_.dimension, -1);

    double best_cost = std::numeric_limits<double>::infinity();
    std::list<int>::const_iterator candidate_node;

    // Step 1 - Selection of the second node
    for (auto it = candidate_nodes.cbegin(); it != candidate_nodes.cend(); ++it)
        if (tsplib_data_.full_matrix[initial_node][*it] < best_cost) {
            best_cost = tsplib_data_.full_matrix[initial_node][*it];
            candidate_node = it;
        }

    solution_nodes[initial_node] = *candidate_node;
    candidate_nodes.erase(candidate_node);

    // Step 2 - Selection of the third node
    best_cost = std::numeric_limits<double>::infinity();

    for (auto it = candidate_nodes.cbegin(); it != candidate_nodes.cend(); ++it) {
        double cost = tsplib_data_.full_matrix[initial_node][*it] + tsplib_data_.full_matrix[*it][solution_nodes[initial_node]];

        if (cost < best_cost) {
            best_cost = cost;
            candidate_node = it;
        }
    }

    solution_nodes[solution_nodes[initial_node]] = *candidate_node;
    solution_nodes[*candidate_node] = initial_node;
    candidate_nodes.erase(candidate_node);

    // Step 3 - Selection of the remaining nodes
    best_cost = std::numeric_limits<double>::infinity();
    while (candidate_nodes.size() > 0) {
        int i = initial_node;
        best_cost = std::numeric_limits<double>::infinity();
        int prev_node = -1;
        int next_node = -1;

        for (int k = 0; k < tsplib_data_.dimension - candidate_nodes.size(); ++k) {
            for (auto it = candidate_nodes.cbegin(); it != candidate_nodes.cend(); ++it) {
                double cost = tsplib_data_.full_matrix[i][*it] + tsplib_data_.full_matrix[*it][solution_nodes[i]] - tsplib_data_.full_matrix[i][solution_nodes[i]];
                // std:: cout << "[" << k << "] : " << i << " - " << *it << " - " << solution_nodes[i] << " : " << cost << "\n";

                if (cost < best_cost) {
                    best_cost = cost;                    
                    candidate_node = it;
                    prev_node = i;
                    next_node = solution_nodes[i];
                }
            }
            i = solution_nodes[i];
        }
        
        solution_nodes[prev_node] = *candidate_node;
        solution_nodes[*candidate_node] = next_node;
        candidate_nodes.erase(candidate_node);
    }

    int k = initial_node;
    tsp_solution_.cost = 0.0;
    for (int i = 0; i < tsplib_data_.dimension; ++i) {
        tsp_solution_.nodes[i] = k;
        tsp_solution_.cost += tsplib_data_.full_matrix[k][solution_nodes[k]];
        k = solution_nodes[k];
    }
}

#include "tsp_bellmore_nemhauser.h"

TSPBellmoreNemhauser::TSPBellmoreNemhauser(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution)
    : TSPSolver(tsplib_data, tsp_solution, TSPSolver::TSPSolverType::BELLMORE_NEMHAUSER) {}

TSPBellmoreNemhauser::~TSPBellmoreNemhauser() {}

void TSPBellmoreNemhauser::solve() {
    std::cout << "Bellmore-Nemhauser TSP solver.\n";

    std::list<int> candidate_nodes;
    for (int i = 1; i < tsplib_data_.dimension; ++i) candidate_nodes.push_back(i);

    std::deque<int> solution_nodes;
    solution_nodes.push_back(0);  // starts at node 0

    double solution_cost = 0.0;

    for (int i = 1; i < tsplib_data_.dimension; ++i) {
        std::list<int>::const_iterator candidate_node_front;
        double best_cost_front = std::numeric_limits<double>::infinity();

        std::list<int>::const_iterator candidate_node_back;
        double best_cost_back = std::numeric_limits<double>::infinity();

        for (auto it = candidate_nodes.cbegin(); it != candidate_nodes.cend(); ++it) {
            if (tsplib_data_.full_matrix[solution_nodes.front()][*it] < best_cost_front) {
                candidate_node_front = it;
                best_cost_front = tsplib_data_.full_matrix[solution_nodes.front()][*it];
            }

            if (tsplib_data_.full_matrix[solution_nodes.back()][*it] < best_cost_back) {
                candidate_node_back = it;
                best_cost_back = tsplib_data_.full_matrix[solution_nodes.back()][*it];
            }
        }

        if (best_cost_back < best_cost_front) {
            solution_nodes.push_back(*candidate_node_back);
            solution_cost += best_cost_back;
            candidate_nodes.erase(candidate_node_back);
        } else {
            solution_nodes.push_front(*candidate_node_front);
            solution_cost += best_cost_front;
            candidate_nodes.erase(candidate_node_front);
        }
    }

    solution_cost += tsplib_data_.full_matrix[solution_nodes.front()][solution_nodes.back()];

    int i = 0;
    for (auto it = solution_nodes.cbegin(); it != solution_nodes.cend(); ++it) {
        tsp_solution_.nodes[i] = *it;
        ++i;
    }
    tsp_solution_.nodes[tsp_solution_.nodes.size() - 1] = solution_nodes.front();

    tsp_solution_.cost = solution_cost;
}

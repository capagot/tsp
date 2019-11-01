#include "tsp_brute_force.h"

TSPBruteForce::TSPBruteForce(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution)
    : TSPSolver(tsplib_data, tsp_solution, TSPSolver::TSPSolverType::BRUTE_FORCE) {
    nodes_.resize(tsplib_data_.dimension);

    for (int i = 0; i < tsplib_data_.dimension; ++i) nodes_[i] = i;
}

TSPBruteForce::~TSPBruteForce() {}

void TSPBruteForce::solve() {
    std::cout << "Brute force TSP solver.\n";
    std::cout << "# permutations: " << factorial(nodes_.size()) << "\n";
    pathPermutation(0);
}

long TSPBruteForce::factorial(long n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

void TSPBruteForce::pathPermutation(int i) {
    int n = tsplib_data_.dimension;

    if (i == n) {
        float cost = 0;

        for (int k = 0; k < (n - 1); ++k) 
            cost += tsplib_data_.full_matrix[nodes_[k]][nodes_[k + 1]];

        cost += tsplib_data_.full_matrix[nodes_[n - 1]][nodes_[0]];

        if (cost < tsp_solution_.cost) {
            tsp_solution_.cost = cost;

            for (int k = 0; k < n; ++k) tsp_solution_.nodes[k] = nodes_[k];
        }
    } else {
        for (int j = i; j < n; ++j) {
            std::swap(nodes_[i], nodes_[j]);
            pathPermutation(i + 1);
            std::swap(nodes_[i], nodes_[j]);
        }
    }
}

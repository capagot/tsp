#include "tsp_dynamic_programming.h"

const int TSPDynamicProgramming::max_n_ = 20;  // mem consumption = 19 * 2^19 * 4 bytes... ~38MB

TSPDynamicProgramming::TSPDynamicProgramming(tlb::TSPLibData& tsplib_data, TSPSolution& tsp_solution)
    : TSPSolver(tsplib_data, tsp_solution, TSPSolver::TSPSolverType::DYNAMIC_PROGRAMMING) {}

TSPDynamicProgramming::~TSPDynamicProgramming() {}

/* 
 * The dynamic programming based algorithm implemented below was extracted from
 * the draft of the Chapter 7 of the book "A Practical Guide to Discrete Optimization", by
 * D. Applegate, W. Cook, S. Dash and D. Johnson. 
 * The Chapter 7 is available at:
 *     http://www.math.uwaterloo.ca/~bico/papers/comp_chapterDP.pdf
 */
void TSPDynamicProgramming::solve() {
    std::cout << "Dynamic programming TSP solver.\n";

    opt_.resize(max_n_ - 1, std::vector<int>(1 << (max_n_ - 1)));

    Set set;
    Set set_count = 1 << (tsplib_data_.dimension - 1);

    for (int i = 0; i < tsplib_data_.dimension - 1; ++i) {
        for (set = 0; set < set_count; ++set) opt_[i][set] = -1;

        opt_[i][1 << i] = tsplib_data_.full_matrix[i][tsplib_data_.dimension - 1];
    }

    int len;
    int best_len = std::numeric_limits<int>::max();

    Set n = (1 << (tsplib_data_.dimension - 1)) - 1;
    for (int t = 0; t < tsplib_data_.dimension - 1; ++t) {
        len = solveRecursive(n, t) + tsplib_data_.full_matrix[t][tsplib_data_.dimension - 1];
        if (len < best_len) best_len = len;
    }

    tsp_solution_.cost = best_len;

    set = (1 << (tsplib_data_.dimension - 1)) - 1;

    int tour[tsplib_data_.dimension + 1];
    tour[0] = tsplib_data_.dimension - 1;
    for (int i = 1; i < tsplib_data_.dimension; ++i) {
        for (int j = 0; j < tsplib_data_.dimension - 1; ++j) {
            if ((set & (1 << j)) && best_len == opt_[j][set] + tsplib_data_.full_matrix[j][tour[i - 1]]) {
                best_len -= tsplib_data_.full_matrix[j][tour[i - 1]];
                tour[i] = j;
                set &= ~(1 << j);
                break;
            }
        }
    }

    for (int i = 0; i < tsplib_data_.dimension; ++i) {
        tsp_solution_.nodes[i] = tour[i];
    }
    tsp_solution_.nodes[tsplib_data_.dimension] = tsp_solution_.nodes[0];
}

int TSPDynamicProgramming::solveRecursive(const Set set, int t) {
    int v;
    int min_v = std::numeric_limits<int>::max();

    Set r;

    if (opt_[t][set] == -1) {
        r = set & ~(1 << t);  // r = set\t

        for (int i = 0; i < tsplib_data_.dimension - 1; ++i) {
            if (!(r & (1 << i))) continue;

            v = solveRecursive(r, i) + tsplib_data_.full_matrix[i][t];

            if (v < min_v) min_v = v;
        }

        opt_[t][set] = min_v;
    }

    return opt_[t][set];
}

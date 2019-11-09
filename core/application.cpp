#include "application.h"

Application::Application(int argc, char** argv) {
    std::string filename;

    if (CmdLineOptions::getOptionValue(argc, argv, "-h")) {
        printHelpMessage();
        exit(EXIT_SUCCESS);
    } else if (CmdLineOptions::getOptionValue(argc, argv, "-i", filename)) {
        tlb::ReadTSPLibFile(filename, tsplib_data_);
        tsp_solution_.nodes.resize(tsplib_data_.dimension + 1);
    } else
        throw;

    std::string tsp_solver_type;
    if (!CmdLineOptions::getOptionValue(argc, argv, "-s", tsp_solver_type))
        tsp_solver_type = "brute-force";

    if (tsp_solver_type.compare("brute-force") == 0)
        tsp_solver_ = std::make_unique<TSPBruteForce>(tsplib_data_, tsp_solution_);
    else if (tsp_solver_type.compare("dynamic-programming") == 0)
        tsp_solver_ = std::make_unique<TSPDynamicProgramming>(tsplib_data_, tsp_solution_);
    else if (tsp_solver_type.compare("nearest-neighbor") == 0)
        tsp_solver_ = std::make_unique<TSPNearestNeighbor>(tsplib_data_, tsp_solution_);
    else if (tsp_solver_type.compare("bellmore-nemhauser") == 0)
        tsp_solver_ = std::make_unique<TSPBellmoreNemhauser>(tsplib_data_, tsp_solution_);
    else
        throw;
}

void Application::run() {
    tsp_solver_->solve();

    std::cout << "cost: " << tsp_solution_.cost << "\n";
    std::cout << "path: ";

    for (int i = 0; i < tsp_solution_.nodes.size() - 1; ++i)
        std::cout << tsp_solution_.nodes[i] << "-";

    std::cout << tsp_solution_.nodes[tsp_solution_.nodes.size() - 1] << "\n";
}

void Application::printHelpMessage() const {
    std::cout << "-h this help message.\n";
    std::cout << "-i input filename.\n";
    std::cout << "-s solver type. Can be:\n";
    std::cout << "  brute-force\n";
    std::cout << "  dynamic-programming\n";
    std::cout << "  nearest-neighbor\n";
    std::cout << "  bellmore-nemhauser\n";
}

#ifndef APPLICATION_H
#define APPLICATION_H

#include <fstream>
#include <memory>

#include "cmd_line_options.h"
#include "tsplib_reader.h"
#include "tsp_solution.h"
#include "tsp_solver.h"
#include "tsp_brute_force.h"
#include "tsp_dynamic_programming.h"
#include "tsp_nearest_neighbor.h"
#include "tsp_bellmore_nemhauser.h"

class Application {
   public:
    Application(int argc, char** argv);
    void run();

   private:
    void printHelpMessage() const;

    TSPSolution tsp_solution_;
    tlb::TSPLibData tsplib_data_;
    std::unique_ptr<TSPSolver> tsp_solver_;
};

#endif  // APPLICATION_H

#ifndef TSPLIB_READER_H
#define TSPLIB_READER_H

#include <fstream>
#include <vector>
#include <regex>

#define SPEC_FIELD_REGEX(VAR, FIELD) std::regex VAR("^\\s*"#FIELD"\\s*:\\s*([^\\s]+(\\s+[^\\s]+)*)\\s*$")

#define DATA_FIELD_REGEX(VAR, FIELD) std::regex VAR("^\\s*("#FIELD")\\s*$")

namespace tlb {

enum class ProblemType {
    NONE, 
    TSP
    // ATSP,
    // SOP,
    // HCP,
    // CVRP,
    // TOUR
};

enum class EdgeWeightType {
    NONE, 
    EXPLICIT
    // EUC_2D,
    // EUC_3D,
    // MAX_2D,
    // MAX_3D,
    // MAN_2D,
    // MAN_3D,
    // CEIL_2D,
    // GEO,
    // ATT,
    // XRAY1,
    // XRAY2,
    // SPECIAL    
};

enum class EdgeWeightFormat {
    NONE, 
    ///FUNCTION,
    FULL_MATRIX
    // UPPER_ROW,
    // LOWER_ROW,
    // UPPER_DIAG_ROW,
    // LOWER_DIAG_ROW,
    // UPPER_COL,
    // LOWER_COL,
    // UPPER_DIAG_COL,
    // LOWER_DIAG_COL
};
enum class DisplayDataType {
    NONE, 
    // COORD_DISPLAY,
    // TWOD_DISPLAY,
    NO_DISPLAY
};

struct TSPLibData {
    std::string name;
    ProblemType type;
    long int dimension;
    EdgeWeightType edge_weight_type;
    EdgeWeightFormat edge_weight_format;
    DisplayDataType display_data_type;
    //std::vector<std::vector<double>> node_coord;
    std::vector<std::vector<double>> full_matrix;
};

void ReadTSPLibFile(const std::string& filename, TSPLibData& tsplib_data);

}  // namespace tlib

#endif  // TSPLIB_READER_H

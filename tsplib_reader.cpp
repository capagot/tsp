#include "tsplib_reader.h"

#include <iostream>

namespace tlb {

void ReadTSPLibFile(const std::string& filename, TSPLibData& tsplib_data) {
    std::ifstream infile(filename);

    SPEC_FIELD_REGEX(spec_name_regex, NAME);
    SPEC_FIELD_REGEX(spec_type_regex, TYPE);
    SPEC_FIELD_REGEX(spec_dimension_regex, DIMENSION);
    SPEC_FIELD_REGEX(spec_ewt_regex, EDGE_WEIGHT_TYPE);
    SPEC_FIELD_REGEX(spec_ewf_regex, EDGE_WEIGHT_FORMAT);
    SPEC_FIELD_REGEX(spec_ddt_regex, DISPLAY_DATA_TYPE);

    DATA_FIELD_REGEX(data_edge_weight_sec_regex, EDGE_WEIGHT_SECTION);

    std::smatch match;

    std::string line;
    while (std::getline(infile, line)) {
        if (std::regex_search(line, match, spec_name_regex)) {
            tsplib_data.name = match[1];
            std::cout << "name: " << match[1] << "\n";
        }

        if (std::regex_search(line, match, spec_type_regex)) {            
            if (match[1].compare("TSP") == 0) 
                tsplib_data.type = tlb::ProblemType::TSP;
            std::cout << "type: " << match[1] << "\n";
        }

        if (std::regex_search(line, match, spec_dimension_regex)) {
            tsplib_data.dimension = std::stoi(match[1]);
            std::cout << "dimension: " << std::stoi(match[1]) << "\n";
        }

        if (std::regex_search(line, match, spec_ewt_regex)) {
            if (match[1].compare("EXPLICIT") == 0) 
                tsplib_data.edge_weight_type = tlb::EdgeWeightType::EXPLICIT;

            std::cout << "edge_weight_type: " << match[1] << "\n";
        }

        if (std::regex_search(line, match, spec_ewf_regex)) {
            if (match[1].compare("FULL_MATRIX") == 0) 
                tsplib_data.edge_weight_format = tlb::EdgeWeightFormat::FULL_MATRIX;
            std::cout << "edge_weight_format: " << match[1] << "\n";
        }

        if (std::regex_search(line, match, spec_ddt_regex)) {
            if (match[1].compare("NO_DISPLAY") == 0) 
                tsplib_data.display_data_type = tlb::DisplayDataType::NO_DISPLAY;
            std::cout << "display_data_type: " << match[1] << "\n";
        }

        if (std::regex_search(line, match, data_edge_weight_sec_regex)) {
            if (tsplib_data.edge_weight_format == tlb::EdgeWeightFormat::FULL_MATRIX) {
                tsplib_data.full_matrix.resize(tsplib_data.dimension, std::vector<double>(tsplib_data.dimension, 0.0f));

                for (int i = 0; i < tsplib_data.dimension; ++i) {
                    std::getline(infile, line);
                    std::istringstream iss(line);

                    for (int j = 0; j < tsplib_data.dimension; ++j) {
                        iss >> tsplib_data.full_matrix[i][j];

                        std::cout << tsplib_data.full_matrix[i][j] << " ";
                    }
                        
                    std::cout << "\n";
                }            
            }
        }
    }
}

}  // namespace tlb

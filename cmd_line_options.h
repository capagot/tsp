#ifndef CMD_LINE_OPTIONS_H
#define CMD_LINE_OPTIONS_H

#include <getopt.h>
#include <string>

struct CmdLineOptions {
    static bool getOptionValue(int argc, char** argv, const std::string& short_option, int& value) {
        bool option_exists = false;

        for (int i = 1; i < argc; ++i)
            if (short_option.compare(*(argv + i)) == 0) {
                value = std::atoi(*(argv + i + 1));
                option_exists = true;
            }

        return option_exists;
    }

    static bool getOptionValue(int argc, char** argv, const std::string& short_option, std::string& value) {
        bool option_exists = false;

        for (int i = 1; i < argc; ++i)
            if (short_option.compare(*(argv + i)) == 0) {
                value = std::string(*(argv + i + 1));
                option_exists = true;
            }
            
        return option_exists;
    }
};

#endif  // CMD_LINE_OPTIONS_H

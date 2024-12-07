#include "getFlags.hpp"

std::unordered_set<std::string> getFlags(int argc, char *argv[]) {
    std::unordered_set<std::string> flags;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') flags.insert(std::string(argv[i]).substr(1));
    }

    return flags;
}
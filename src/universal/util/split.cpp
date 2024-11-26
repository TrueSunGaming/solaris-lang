#include "split.hpp"

std::vector<std::string> split(const std::string str, std::string delim) {
    std::vector<std::string> res;

    size_t pos = 0;

    while(pos < str.size()) {
        size_t next = str.find(delim, pos);
        res.push_back(str.substr(pos, next - pos));

        if (next == std::string::npos) break;

        pos = next + delim.size();
    }

    return res;
}
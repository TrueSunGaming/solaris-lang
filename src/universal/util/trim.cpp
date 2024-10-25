#include "trim.hpp"
#include <algorithm>

void ltrim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
}

void rtrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), str.end());
}

void trim(std::string &str) {
    ltrim(str);
    rtrim(str);
}
#include "scientificToNumber.hpp"

template <class T> T scientificToNumber(const std::string& str) {
    std::istringstream stream = std::istringstream(str);
    T res;
    stream >> res;

    return res;
}

template double scientificToNumber(const std::string& str);
template int64_t scientificToNumber(const std::string& str);
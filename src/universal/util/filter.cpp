#include "filter.hpp"
#include <algorithm>

template <class T>
std::vector<T> filter(const std::vector<T> &vec, const std::function<bool(T)> &fn) {
    std::vector<T> res;

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(res), fn);

    return res;
}

template std::vector<std::string> filter(const std::vector<std::string> &, const std::function<bool(std::string)> &);
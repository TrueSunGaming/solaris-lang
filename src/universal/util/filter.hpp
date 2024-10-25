#pragma once

#include <vector>
#include <functional>
#include <string>

template <class T>
std::vector<T> filter(const std::vector<T> &vec, const std::function<bool(T)> &fn);

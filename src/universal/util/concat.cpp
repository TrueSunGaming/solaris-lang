#include "concat.hpp"
#include "../assembly/Instruction.hpp"

template <class T> constexpr void concat(std::vector<T>& to, const std::vector<T>& from) {
    to.insert(to.end(), from.begin(), from.end());
}

template void concat(std::vector<Instruction>&, const std::vector<Instruction>&);
template void concat(std::vector<std::string>&, const std::vector<std::string>&);
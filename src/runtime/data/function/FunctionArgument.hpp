#pragma once

#include <string>
#include "../ValueType.hpp"

class FunctionArgument {
    public:
        std::string name;
        ValueType type;

        FunctionArgument(std::string name, ValueType type);
};
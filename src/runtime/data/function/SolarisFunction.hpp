#pragma once

#include "Function.hpp"

class SolarisFunction : public Function {
    public:
        std::string name;
        size_t id;
        size_t startLine;

        void call(AbstractFunctionCaller *runtime, const std::vector<Object *>& args) const override;
};
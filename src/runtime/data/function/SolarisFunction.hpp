#pragma once

#include "Function.hpp"

class SolarisFunction : public Function {
    public:
        std::string name;
        size_t id;
        size_t startLine;

        void call(RuntimeState& runtime, std::vector<Object *> args) const override;
};
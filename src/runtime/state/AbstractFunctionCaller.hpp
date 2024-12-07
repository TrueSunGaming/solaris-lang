#pragma once

#include "../data/Object.hpp"

class AbstractFunctionCaller {
    public:
        virtual void jump(size_t line) = 0;
        virtual void pushReturn(std::optional<size_t> functionID = std::nullopt) = 0;
        virtual void createScope() = 0;
        virtual void setObject(const std::string& name, Object *value) = 0;
};
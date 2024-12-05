#pragma once

#include "../data/Object.hpp"

class AbstractFunctionCaller {
    public:
        virtual void jump(size_t line) = 0;
        virtual void pushReturn(size_t functionID) = 0;
        virtual void createScope() = 0;
        virtual void setObject(const std::string& name, Object *value) = 0;
};
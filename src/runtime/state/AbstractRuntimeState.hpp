#pragma once

#include "../data/Object.hpp"

class AbstractRuntimeState {
    public:
        virtual void step() = 0;
        virtual void jump(size_t line) = 0;
        virtual void ret() = 0;
        virtual void pushReturn(size_t functionID) = 0;
        virtual Object *getReturnObject() = 0;
};
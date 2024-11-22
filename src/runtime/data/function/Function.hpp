#pragma once

#include <string>
#include <memory>
#include "../Object.hpp"
#include "../../state/AbstractFunctionCaller.hpp"
#include "FunctionArgument.hpp"

class Function : public Object {
    public:
        Object *returnObj = nullptr;
        std::vector<FunctionArgument> args;

        Function(Object *returnObj = nullptr);

        virtual void call(AbstractFunctionCaller *runtime, std::vector<Object *> args) const = 0;
};
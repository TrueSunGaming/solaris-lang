#pragma once

#include "Function.hpp"
#include <functional>

class CompiledFunction : public Function {
    public:
        typedef std::function<Object *(AbstractFunctionCaller *, const std::vector<Object *>&)> Definition;

        Definition def;

        CompiledFunction(Object *, std::vector<FunctionArgument>) = delete;
        CompiledFunction(Definition def, Object *returnObj = nullptr, std::vector<FunctionArgument> args = {});

        void call(AbstractFunctionCaller *runtime, const std::vector<Object *>& args) const override;
};
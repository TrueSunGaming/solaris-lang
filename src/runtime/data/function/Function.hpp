#pragma once

#include <string>
#include <memory>
#include "../Object.hpp"
#include "../../state/AbstractRuntimeState.hpp"

class Function {
    public:
        Object *returnObj = nullptr;

        Function(Object *returnObj);

        virtual void call(AbstractRuntimeState& runtime, std::vector<Object *> args) const = 0;
};
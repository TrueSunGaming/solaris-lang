#pragma once

#include <string>
#include <memory>
#include "../Object.hpp"
#include "../../state/RuntimeState.hpp"

class Function {
    public:
        Object *returnObj = nullptr;

        Function(Object *returnObj);

        virtual void call(RuntimeState& runtime, std::vector<Object *> args) const = 0;
};
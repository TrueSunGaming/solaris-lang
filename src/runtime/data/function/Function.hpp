#pragma once

#include <string>
#include <memory>
#include "../Object.hpp"
#include "../../state/RuntimeState.hpp"

class Function {
    public:
        virtual std::unique_ptr<Object> call(RuntimeState& runtime, std::vector<Object *> args) const = 0;
};
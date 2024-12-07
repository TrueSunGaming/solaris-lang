#pragma once

#include <optional>

struct FunctionReturnState {
    std::optional<size_t> functionID;
    size_t line;
};
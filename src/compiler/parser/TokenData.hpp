#pragma once

#include <string>
#include <unordered_set>

namespace TokenData {
    const std::unordered_set<std::string> keywords = {
        "fn",
        "const",
        "constref",
        "string",
        "int",
        "float",
        "bool",
        "void",
        "if"
    };

    const std::unordered_set<std::string> baseTypes = {
        "string",
        "int",
        "float",
        "bool",
        "void"
    };

    const std::unordered_set<std::string> typeModifiers = {
        "const",
        "constref"
    };
}
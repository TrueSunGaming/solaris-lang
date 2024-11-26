#pragma once

#include "ast/ASTType.hpp"
#include <string>
#include <unordered_set>

namespace ParseData {
    const std::unordered_set<std::string> keywords = {
        "fn",
        "const",
        "constref",
        "string",
        "int",
        "float",
        "bool",
        "void",
        "if",
        "else",
        "elif",
        "while",
        "for",
        "do",
        "true",
        "false",
        "null",
        "class",
        "return"
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

    const std::unordered_set<std::string> accessOperators = {
        ".",
        "?.",
        "::"
    };

    const std::unordered_set<ASTType> eolBack = {
        ASTType::ROOT,
        ASTType::BLOCK
    };

    const std::unordered_set<ASTType> callable = {
        ASTType::GET,
        ASTType::OPERATION
    };

    const std::unordered_set<ASTType> blockParent = {
        ASTType::DEFINE_FUNCTION,
        ASTType::DEFINE_CLASS,
        ASTType::WHILE,
        ASTType::DO_WHILE,
        ASTType::FOR,
        ASTType::CONDITIONAL
    };
}
#pragma once

#include "ast/ASTType.hpp"
#include "../lexer/Token.hpp"
#include <string>
#include <unordered_set>
#include <set>

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

    const std::set<ASTType> eolBack = {
        ASTType::ROOT,
        ASTType::BLOCK
    };

    const std::set<ASTType> callable = {
        ASTType::GET,
        ASTType::OPERATION
    };

    const std::set<ASTType> blockParent = {
        ASTType::DEFINE_FUNCTION,
        ASTType::DEFINE_CLASS,
        ASTType::WHILE,
        ASTType::DO_WHILE,
        ASTType::FOR,
        ASTType::CONDITIONAL
    };

    const std::set<TokenType> invalidAfterDeclaration = {
        TokenType::OPERATOR,
        TokenType::PARENTHESIS_OPEN
    };

    const std::set<ASTType> values = {
        ASTType::GET,
        ASTType::INTEGER,
        ASTType::FLOAT,
        ASTType::STRING,
        ASTType::BOOLEAN,
        ASTType::OPERATION,
        ASTType::NULL_VAL,
        ASTType::CALL,
        ASTType::DECLARE,
        ASTType::LIST
    };
}
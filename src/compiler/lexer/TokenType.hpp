#pragma once

#include <regex>
#include <map>
#include <unordered_set>

enum TokenType {
    EOL,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    STRING,
    PARENTHESIS_OPEN,
    PARENTHESIS_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE,
    CURLY_OPEN,
    CURLY_CLOSE,
    COMMA,
    OPERATOR
};

const std::regex MULTILINE_COMMENT_REGEX = std::regex(R"(\/\*.*?\*\/)");
const std::unordered_set<std::string> joinedOperators = {
    "==", // equal
    "+=", // add assign
    "-=", // sub assign
    "*=", // mul assign
    "/=", // div assign
    "%=", // mod assign
    "**=", // exp assign
    "||=", // bool or assign
    "&&=", // bool and assign
    "^^=", // bool xor assign
    "\?\?=", // nullish coalescing assign
    "|=", // bitwise or assign
    "&=", // bitwise and assign
    "^=", // bitwise xor assign
    "~=", // bitwise not assign
    "!=", // not equal
    ">=", // greater equal
    "<=", // less equal
    "::", // namespace
    "++", // increment
    "--", // decrement
    "||", // boolean or
    "&&", // boolean and
    "^^", // boolean xor
    "**", // exp
    "??", // nullish coalescing,
    "?.", // optional chaining
};

const std::map<TokenType, std::string> tokenRegexMap = {
    { TokenType::EOL, R"(;)" },
    { TokenType::IDENTIFIER, R"([a-zA-Z_$][\w$]*)" },
    { TokenType::INTEGER, R"(\d+(e\+?\d+)?)" },
    { TokenType::FLOAT, R"((\d+\.(\d*)?(e(-|\+)?\d+(\.\d*)?)?)|(\d+(\.\d*)?e-\d+(\.\d*)?))" },
    { TokenType::STRING, R"((['"])(?:(?:\\.|[^\\])*?)\1)" },
    { TokenType::PARENTHESIS_OPEN, R"(\()" },
    { TokenType::PARENTHESIS_CLOSE, R"(\))" },
    { TokenType::SQUARE_OPEN, R"(\[)" },
    { TokenType::SQUARE_CLOSE, R"(\])" },
    { TokenType::CURLY_OPEN, R"(\{)" },
    { TokenType::CURLY_CLOSE, R"(\})" },
    { TokenType::COMMA, R"(,)" },
    { TokenType::OPERATOR, R"([+\-*/=!<>:?%&|^~])" }
};
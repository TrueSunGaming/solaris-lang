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
    OPERATOR,
    ARRAY_TYPE,
    OPTIONAL_TYPE
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
    { EOL, R"(;)" },
    { IDENTIFIER, R"([a-zA-Z_$][\w$]*)" },
    { INTEGER, R"(\d+(e\+?\d+)?)" },
    { FLOAT, R"((\d+\.(\d*)?(e(-|\+)?\d+(\.\d*)?)?)|(\d+(\.\d*)?e-\d+(\.\d*)?))" },
    { STRING, R"((['"])(?:(?:\\.|[^\\])*?)\1)" },
    { PARENTHESIS_OPEN, R"(\()" },
    { PARENTHESIS_CLOSE, R"(\))" },
    { SQUARE_OPEN, R"(\[)" },
    { SQUARE_CLOSE, R"(\])" },
    { CURLY_OPEN, R"(\{)" },
    { CURLY_CLOSE, R"(\})" },
    { COMMA, R"(,)" },
    { OPERATOR, R"([+\-*/=!<>:?%&|^~])" }
};
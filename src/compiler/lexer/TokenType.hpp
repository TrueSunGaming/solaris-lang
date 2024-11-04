#pragma once

#include <regex>

const std::regex IDENTIFIER_REGEX = std::regex(R"([a-zA-Z_$][\w$]*)");
const std::regex INTEGER_REGEX = std::regex(R"(\d+(e\+?\d+)?)");
const std::regex FLOAT_REGEX = std::regex(R"((\d+\.(\d*)?(e(-|\+)?\d+(\.\d*)?)?)|(\d+(\.\d*)?e-\d+(\.\d*)?))");
const std::regex STRING_REGEX = std::regex(R"((['"])(?:(?:\\.|[^\\])*?)\1)");
const std::regex MULTILINE_COMMENT_REGEX = std::regex(R"(\/\*.*?\*\/)");

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
    COLON,
    OPERATOR,
    QUESTION
};
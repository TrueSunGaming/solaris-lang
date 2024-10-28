#pragma once

#include <string>
#include "TokenType.hpp"

class Token {
    public:
        std::string value;
        enum TokenType type;
        std::string filepath;
        int line;
        int column;

        Token(std::string value, enum TokenType type, std::string filepath, int line, int column);
        ~Token() = default;
};
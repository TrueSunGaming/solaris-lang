#pragma once

#include <string>
#include "../../universal/tokens/TokenType.hpp"

class Token {
    public:
        std::string value;
        TokenType type = TokenType::EOL;
        std::string filepath;
        int line;
        int column;

        Token() = default;
        Token(const std::string& value, TokenType type, std::string filepath, int line, int column);
        ~Token() = default;
};
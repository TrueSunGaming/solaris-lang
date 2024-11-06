#pragma once

#include <string>
#include <vector>
#include "../../universal/regex/SubstringPosition.hpp"
#include "Token.hpp"

class Lexer {
    protected:
        std::string str;
        size_t searchPosition = 0;
        
        std::string getActiveSubstring() const;
        void mergeTokens();

    public:
        std::vector<Token> tokens;
        
        Lexer(std::string str);
        ~Lexer() = default;

        bool readNext();
        void readAll(size_t limit = SIZE_MAX);

        static std::vector<Token> tokenize(const std::string& code, size_t limit = SIZE_MAX);
};
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
        void mergeOperator(size_t index);

    public:
        std::vector<Token> tokens;
        std::vector<std::string> errors;
        
        Lexer(std::string str);
        ~Lexer() = default;

        bool readNext();
        void readAll(size_t limit = SIZE_MAX);
        void mergeTokens();

        static std::vector<Token> tokenize(const std::string& code, size_t limit = SIZE_MAX);
};
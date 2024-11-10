#pragma once

#include <vector>
#include "../lexer/Token.hpp"
#include "ast/AST.hpp"

class Parser {
    protected:
        const std::vector<Token>& tokens;
        size_t searchPosition = 0;
        std::stack<AST&> nested;

        bool parseIdentifier();
        bool parseKeyword();
        bool parseFunction();
        bool parseType();

        bool tokenIsType(size_t index, std::optional<std::map<size_t, bool>> cache = std::nullopt) const;
    
    public:
        AST ast = AST(ASTType::ROOT);
        std::vector<std::string> errors;

        Parser(const std::vector<Token>& tokens);
        ~Parser() = default;

        bool parseNext();
        void parseAll(size_t limit = SIZE_MAX);

        static AST parse(std::vector<Token> tokens);
};
#pragma once

#include <vector>
#include <optional>
#include "../lexer/Token.hpp"
#include "ast/AST.hpp"

class Parser {
    protected:
        const std::vector<Token>& tokens;
        size_t searchPosition = 0;
        std::stack<AST *> nested;

        enum BracketType {
            PARENTHESIS,
            SQUARE,
            CURLY
        };

        bool validBrackets() const;
        bool parseIdentifier();
        bool parseKeyword();
        bool parseFunction();
        bool parseType();
        bool parseOpenParenthesis();
        bool parseCloseParenthesis();
        bool parseDeclaration();
        bool parseComma();

        bool tokenIsType(size_t index, std::optional<std::map<size_t, bool>> cache = std::nullopt) const;

        void push(ASTType type = ASTType::BLOCK, std::string value = "");
    
    public:
        std::unique_ptr<AST> ast = std::make_unique<AST>(ASTType::ROOT);
        std::vector<std::string> errors;

        Parser(const std::vector<Token>& tokens);
        ~Parser() = default;

        bool parseNext();
        void parseAll(size_t limit = SIZE_MAX);

        static std::unique_ptr<AST> parse(std::vector<Token> tokens);
};
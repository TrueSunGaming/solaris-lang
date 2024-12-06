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
        bool tokenIsType(size_t index, std::optional<std::map<size_t, bool>> cache = std::nullopt) const;
        size_t getTypeLength() const;
        bool canDeclare() const;

        bool parseIdentifier();
        bool parseKeyword();
        bool parseFunction();
        bool parseType();
        bool parseOpenParenthesis();
        bool parseCloseParenthesis();
        bool parseDeclaration();
        bool parseComma();
        bool parseOpenCurly();
        bool parseCloseCurly();
        bool parseBlock();
        bool parseOperator();
        bool parseEOL();
        bool parseCall();
        bool parseString();
        bool parseBoolean();
        bool parseFloat();
        bool parseInteger();
        bool parseNull();
        bool parseReturn();
        bool parseIf();
        bool parseElse();

        void wrapParent(ASTType type = ASTType::BLOCK, std::string value = "");
        void push(ASTType type = ASTType::BLOCK, std::string value = "");
        bool pushError(std::string error, bool continueParse = false);
    
    public:
        std::unique_ptr<AST> ast = std::make_unique<AST>(ASTType::ROOT);
        std::vector<std::string> errors;

        Parser(const std::vector<Token>& tokens);
        ~Parser() = default;

        bool parseNext();
        void parseAll(size_t limit = SIZE_MAX);

        static std::unique_ptr<AST> parse(std::vector<Token> tokens);
};
#include "Parser.hpp"
#include "keywords.hpp"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {
    nested.push(ast);
}

bool Parser::tokenIsType(size_t index, std::optional<std::map<size_t, bool>> cache) const {
    if (index < 0 || index >= tokens.size()) return false;

    if (cache) try {
        return cache->at(index);
    } catch(std::exception e) {}

    const Token& token = tokens[index];

    bool res = ([token, index, cache, this] {
        switch (token.type) {
            case TokenType::IDENTIFIER:
                if (index < 1) return true;
                return !tokenIsType(index - 1, cache);
            
            case TokenType::SQUARE_OPEN:
                if (index < 1 || index >= tokens.size() - 1) return false;
                return tokens[index + 1].type == TokenType::SQUARE_CLOSE && tokenIsType(index - 1, cache);
            
            case TokenType::SQUARE_CLOSE:
                if (index < 2) return false;
                return tokens[index - 1].type == TokenType::SQUARE_OPEN && tokenIsType(index - 1, cache);
            
            default:
                return false;
        }
    })();

    if (cache) (*cache)[index] = res;
    return res;
}

bool Parser::parseNext() {
    if (searchPosition >= tokens.size()) return false;

    const Token& token = tokens[searchPosition];

    switch (token.type) {
        case TokenType::IDENTIFIER:
            return parseIdentifier();
        
        default:
            return false;
    }
}

bool Parser::parseIdentifier() {
    const Token& token = tokens[searchPosition];

    if (keywords.contains(token.value)) return parseKeyword();

    return false;
}

bool Parser::parseKeyword() {
    const Token& token = tokens[searchPosition];

    if (!keywords.contains(token.value)) {
        std::string err = "Syntax Error: Expected keyword";
        std::cout << err << "\n";
        errors.push_back(err);
        return false;
    }

    if (token.value == "fn") return parseFunction();

    return false;
}

bool Parser::parseFunction() {
    AST def = AST(ASTType::DEFINE_FUNCTION);
    nested.top().children.push_back(def);
    nested.push(def);

    AST returnType = AST(ASTType::TYPE);
    def.children.push_back(returnType);
    nested.push(returnType);

    searchPosition++;
    return parseType();
}

bool Parser::parseType() {
    AST& type = nested.top();

    const std::unordered_set<TokenType> typeTokenTypes = {
        TokenType::IDENTIFIER,
        TokenType::SQUARE_OPEN,
        TokenType::SQUARE_CLOSE
    };

    std::vector<size_t> typeTokens;

    std::map<size_t, bool> tokenIsTypeCache;
    for (size_t i = searchPosition; i < tokens.size(); i++) {
        if (!tokenIsType(i, tokenIsTypeCache)) break;
        typeTokens.push_back(i);
    }

    if (typeTokens.size() < 1) {
        std::string err = "Syntax Error: Expected type";
        std::cout << err << "\n";
        errors.push_back(err);
        return false;
    }

    searchPosition += typeTokens.size();

    std::vector<std::string> typeTokenValues;
    typeTokenValues.reserve(typeTokens.size());

    for (size_t i = 0; i < typeTokens.size(); i++) {
        const Token& token = tokens[typeTokens[i]];

        if (token.type == TokenType::SQUARE_OPEN) {
            typeTokenValues.push_back("[]");
            i++;
            continue;
        }

        typeTokenValues.push_back(token.value);
    }

    for (const auto& i : typeTokenValues) {
        if (i == "int" || i == "string" || i == "bool" || i == "float") type.type = ASTType::BASE_TYPE;

        if (i == "const" || i == "constref") {
            type.children.emplace_back(ASTType::TYPE_MODIFIER, i);
            continue;
        }

        if (i == "[]") {
            type.children.emplace_back(ASTType::TYPE_MODIFIER, "array");
            continue;
        }

        type.value = i;
    }

    return true;
}

void Parser::parseAll(size_t limit) {
    for (size_t i = 0; i < limit && parseNext(); i++) {}
}

AST Parser::parse(std::vector<Token> tokens) {
    Parser parser = Parser(tokens);
    parser.parseAll();
    return parser.tokenms
}
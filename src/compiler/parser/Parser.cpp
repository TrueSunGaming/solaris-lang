#include "Parser.hpp"
#include "TokenData.hpp"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {
    nested.push(ast.get());
}

bool Parser::validBrackets() const {
    std::stack<Parser::BracketType> brackets;

    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];

        switch (token.type) {
            case TokenType::PARENTHESIS_OPEN:
                brackets.push(Parser::BracketType::PARENTHESIS);
                break;
            
            case TokenType::SQUARE_OPEN:
                brackets.push(Parser::BracketType::SQUARE);
                break;
            
            case TokenType::CURLY_OPEN:
                brackets.push(Parser::BracketType::CURLY);
                break;
            
            case TokenType::PARENTHESIS_CLOSE:
                if (brackets.empty() || brackets.top() != Parser::BracketType::PARENTHESIS) return false;
                brackets.pop();
                break;
            
            case TokenType::SQUARE_CLOSE:
                if (brackets.empty() || brackets.top() != Parser::BracketType::SQUARE) return false;
                brackets.pop();
                break;
            
            case TokenType::CURLY_CLOSE:
                if (brackets.empty() || brackets.top() != Parser::BracketType::CURLY) return false;
                brackets.pop();
                break;
        }
    }

    return true;
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
                if (tokens[index - 1].value == "fn") return true;
                if (TokenData::typeModifiers.contains(tokens[index - 1].value)) return true;
                return !tokenIsType(index - 1, cache);
            
            case TokenType::SQUARE_OPEN:
                if (index < 1 || index >= tokens.size() - 1) return false;
                return tokens[index + 1].type == TokenType::SQUARE_CLOSE && tokenIsType(index - 1, cache);
            
            case TokenType::SQUARE_CLOSE:
                if (index < 2) return false;
                return tokens[index - 1].type == TokenType::SQUARE_OPEN && tokenIsType(index - 1, cache);
            
            case TokenType::OPERATOR:
                if (index < 1) return false;
                return tokenIsType(index - 1, cache) && token.value == "?" && tokens[index - 1].value != "?";
            
            default:
                return false;
        }
    })();

    return cache ? (*cache)[index] = res : res;
}

void Parser::push(ASTType type, std::string value) {
    nested.push(nested.top()->createChild(type, value));
}

bool Parser::parseNext() {
    std::cout << "Parsing token at " << searchPosition << " '" << tokens[searchPosition].value << "'\n";

    if (searchPosition >= tokens.size()) return false;

    const Token& token = tokens[searchPosition];

    switch (token.type) {
        case TokenType::IDENTIFIER:
            return parseIdentifier();
        
        case TokenType::PARENTHESIS_OPEN:
            return parseOpenParenthesis();
        
        case TokenType::PARENTHESIS_CLOSE:
            return parseCloseParenthesis();
        
        case TokenType::COMMA:
            return parseComma();
        
        default:
            return false;
    }
}

bool Parser::parseIdentifier() {
    std::cout << "Parsing identifier at " << searchPosition << "\n";

    const Token& token = tokens[searchPosition];
    AST& parent = *nested.top();
    const bool isKeyword = TokenData::keywords.contains(token.value);

    if (parent.type == ASTType::TYPE) return parseType();
    if (parent.type == ASTType::DECLARE) return parseDeclaration();

    if (parent.type == ASTType::DEFINE_FUNCTION) {
        if (isKeyword) {
            std::string err = "Syntax Error: Unexpected keyword";
            std::cout << err << "\n";
            errors.push_back(err);
            return false;
        }

        parent.value = token.value;
        searchPosition++;

        return true;
    }

    if (isKeyword) return parseKeyword();

    return false;
}

bool Parser::parseKeyword() {
    std::cout << "Parsing keyword at " << searchPosition << "\n";

    const Token& token = tokens[searchPosition];

    if (!TokenData::keywords.contains(token.value)) {
        std::string err = "Syntax Error: Expected keyword, found " + token.value + " (" + std::to_string((int)token.type) + ") instead."; 
        std::cout << err << "\n";
        errors.push_back(err);
        return false;
    }

    if (token.value == "fn") return parseFunction();

    return false;
}

bool Parser::parseFunction() {
    std::cout << "Parsing function definition at " << searchPosition << "\n";

    push(ASTType::DEFINE_FUNCTION);
    push(ASTType::TYPE);

    searchPosition++;
    
    return true;
}

bool Parser::parseType() {
    std::cout << "Parsing type at " << searchPosition << "\n";

    AST& type = *nested.top();

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
        std::string err = "Syntax Error: Expected type, found " + tokens[searchPosition].value + " (" + std::to_string((int)tokens[searchPosition].type) + ") instead."; 
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
        if (TokenData::baseTypes.contains(i)) type.type = ASTType::BASE_TYPE;

        if (i == "const" || i == "constref") {
            type.createChild(ASTType::TYPE_MODIFIER, i);
            continue;
        }

        if (i == "[]") {
            type.createChild(ASTType::TYPE_MODIFIER, "array");
            continue;
        }

        if (i == "?") {
            type.createChild(ASTType::TYPE_MODIFIER, "optional");
            continue;
        }

        type.value = i;
    }

    nested.pop();

    return true;
}

bool Parser::parseOpenParenthesis() {
    std::cout << "Parsing open parenthesis at " << searchPosition << "\n";

    AST& parent = *nested.top();

    if (parent.type == ASTType::DEFINE_FUNCTION) {
        push(ASTType::ARGUMENT_LIST);
        push(ASTType::DECLARE);
        searchPosition++;

        return true;
    }

    return false;
}

bool Parser::parseCloseParenthesis() {
    std::cout << "Parsing close parenthesis at " << searchPosition << "\n";

    AST& parent = *nested.top();

    if (parent.type == ASTType::ARGUMENT_LIST) {
        nested.pop();
        searchPosition++;

        return true;
    }

    if (parent.type == ASTType::DECLARE) {
        nested.pop();

        return nested.top()->type == ASTType::ARGUMENT_LIST;
    }

    return false;
}

bool Parser::parseDeclaration() {
    std::cout << "Parsing declaration at " << searchPosition << "\n";

    AST& parent = *nested.top();

    if (parent.children.size() == 0) {
        push(ASTType::TYPE);
        return true;
    }

    parent.value = tokens[searchPosition].value;
    nested.pop();

    searchPosition++;

    return true;
}

bool Parser::parseComma() {
    std::cout << "Parsing comma at " << searchPosition << "\n";

    AST& parent = *nested.top();

    if (parent.type == ASTType::ARGUMENT_LIST) {
        push(ASTType::DECLARE);
        searchPosition++;

        return true;
    }

    return false;
}

void Parser::parseAll(size_t limit) {
    if (!validBrackets()) {
        std::cout << "Syntax Error: Invalid brackets\n";
        return;
    }

    for (size_t i = 0; i < limit && parseNext(); i++) {}
}

std::unique_ptr<AST> Parser::parse(std::vector<Token> tokens) {
    Parser parser = Parser(tokens);
    parser.parseAll();
    return std::move(parser.ast);
}
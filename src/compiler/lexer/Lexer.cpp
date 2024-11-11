#include "Lexer.hpp"
#include "../../universal/regex/findRegex.hpp"
#include "../../universal/util/trim.hpp"
#include "minimize.hpp"
#include <iostream>

Lexer::Lexer(std::string str) : str(str) {}

std::string Lexer::getActiveSubstring() const {
    return str.substr(searchPosition);
}

bool Lexer::readNext() {
    if (searchPosition >= str.size()) return false;

    const std::string substr = getActiveSubstring();

    for (const auto& [k, v] : tokenRegexMap) {
        const std::regex regex = std::regex("^\\s*" + v);

        std::smatch match;
        if (!std::regex_search(substr, match, regex)) continue;

        size_t len = match.length();
        std::string matchStr = substr.substr(0, len);
        trim(matchStr);

        tokens.emplace_back(matchStr, k, "", 0, 0);
        searchPosition += len;

        return true;
    }

    return false;
}

void Lexer::readAll(size_t limit) {
    for (size_t i = 0; i < limit && readNext(); i++) {}
}

void Lexer::mergeTokens() {
    if (tokens.size() < 1) return;

    for (size_t i = 0; i < tokens.size() - 1; i++) {
        mergeOperator(i);
    }
}

void Lexer::mergeOperator(size_t index) {
    if (index >= tokens.size() - 1) return;

    std::string joined = "";
    for (size_t i = index; i < tokens.size(); i++) {
        if (tokens[i].type != TokenType::OPERATOR) break;
        joined += tokens[i].value;
    }

    if (joined.size() < 1) return;
    
    tokens.erase(std::next(tokens.begin(), index + 1), std::next(tokens.begin(), index + joined.size()));

    if (!joinedOperators.contains(joined)) {
        const std::string err = "Syntax Error: Unknown operator '" + joined + "'.";
        errors.push_back(err);
        std::cout << err << "\n";
        return;
    }

    tokens[index].value = joined;
}

std::vector<Token> Lexer::tokenize(const std::string& code, size_t limit) {
    Lexer lexer = Lexer(minimize(code));
    lexer.readAll(limit);
    lexer.mergeTokens();

    return lexer.tokens;
}

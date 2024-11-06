#include "Lexer.hpp"
#include "../../universal/regex/findRegex.hpp"
#include "../../universal/util/trim.hpp"
#include "minimize.hpp"

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
    for (size_t i = 0; i < tokens.size() - 1; i++) {
        if (tokens[i].type != TokenType::OPERATOR) continue;
        if (tokens[i + 1].type != TokenType::OPERATOR) continue;

        const std::string joined = tokens[i].value + tokens[i + 1].value;
        if (!joinedOperators.contains(joined)) continue;

        tokens[i].value = joined;
        tokens.erase(std::next(tokens.begin(), i + 1));
    }
}

std::vector<Token> Lexer::tokenize(const std::string& code, size_t limit) {
    Lexer lexer = Lexer(minimize(code));
    lexer.readAll(limit);
    lexer.mergeTokens();

    return lexer.tokens;
}

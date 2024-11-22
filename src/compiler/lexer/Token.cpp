#include "Token.hpp"

Token::Token(const std::string& value, TokenType type, std::string filepath, int line, int column) :
    value(value), 
    type(type),
    filepath(filepath),
    line(line),
    column(column) {}
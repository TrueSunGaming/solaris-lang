#include "Token.hpp"

Token::Token(std::string value, enum TokenType type, std::string filepath, int line, int column) :
    value(value), 
    type(type),
    filepath(filepath),
    line(line),
    column(column) {}
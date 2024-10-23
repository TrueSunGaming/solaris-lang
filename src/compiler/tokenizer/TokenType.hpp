#pragma once

enum TokenType {
    EOL,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    STRING,
    FSTRING_QUOTE,
    FSTRING_TEXT,
    FSTRING_FORMAT_OPEN,
    FSTRING_FORMAT_CLOSE,
    PARENTHESIS_OPEN,
    PARENTHESIS_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE,
    CURLY_OPEN,
    CURLY_CLOSE,
    COMMA,
    COLON,
    OPERATOR,
    QUESTION
};
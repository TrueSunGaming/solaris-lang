#pragma once

enum TokenType {
    EOL, // ;
    IDENTIFIER, // /[a-z_$][\w$]*/gi
    INTEGER, // /\d+(e\+?\d+)?/g
    FLOAT, // /(\d+\.(\d*)?(e(-|\+)?\d+(\.\d*)?)?)|(\d+(\.\d*)?e-\d+(\.\d*)?)/g
    STRING, // custom implementation
    PARENTHESIS_OPEN, // (
    PARENTHESIS_CLOSE, // )
    SQUARE_OPEN, // [
    SQUARE_CLOSE, // ]
    CURLY_OPEN, // {
    CURLY_CLOSE, // }
    COMMA, // ,
    COLON, // :
    OPERATOR, // 
    QUESTION // ?
};
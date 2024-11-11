#pragma once

enum class ASTType {
    ROOT,
    NULL_VAL,
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN,
    OPERATION,
    SET,
    GET,
    CALL,
    DECLARE,
    DEFINE_FUNCTION,
    ARGUMENT_LIST,
    CALL_ARGUMENTS,
    LIST,
    BLOCK,
    CONDITIONAL,
    WHILE,
    DO_WHILE,
    FOR,
    INSTANTIATE,
    DEFINE_CLASS,
    TYPE,
    TYPE_MODIFIER,
    BASE_TYPE
};
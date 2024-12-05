#pragma once

#include <map>
#include <string>

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
    BASE_TYPE,
    RETURN
};

const std::map<ASTType, std::string> astTypeName = {
    { ASTType::ROOT, "ROOT" },
    { ASTType::NULL_VAL, "NULL_VAL" },
    { ASTType::INTEGER, "INTEGER" },
    { ASTType::FLOAT, "FLOAT" },
    { ASTType::STRING, "STRING" },
    { ASTType::BOOLEAN, "BOOLEAN" },
    { ASTType::OPERATION, "OPERATION" },
    { ASTType::SET, "SET" },
    { ASTType::GET, "GET" },
    { ASTType::CALL, "CALL" },
    { ASTType::DECLARE, "DECLARE" },
    { ASTType::DEFINE_FUNCTION, "DEFINE_FUNCTION" },
    { ASTType::ARGUMENT_LIST, "ARGUMENT_LIST" },
    { ASTType::CALL_ARGUMENTS, "CALL_ARGUMENTS" },
    { ASTType::LIST, "LIST" },
    { ASTType::BLOCK, "BLOCK" },
    { ASTType::CONDITIONAL, "CONDITIONAL" },
    { ASTType::WHILE, "WHILE" },
    { ASTType::DO_WHILE, "DO_WHILE" },
    { ASTType::FOR, "FOR" },
    { ASTType::INSTANTIATE, "INSTANTIATE" },
    { ASTType::DEFINE_CLASS, "DEFINE_CLASS" },
    { ASTType::TYPE, "TYPE" },
    { ASTType::TYPE_MODIFIER, "TYPE_MODIFIER" },
    { ASTType::BASE_TYPE, "BASE_TYPE" },
    { ASTType::RETURN, "RETURN" }
};
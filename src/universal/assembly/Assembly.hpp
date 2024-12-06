#pragma once

#include <map>
#include <string>

enum class Assembly {
    DECLARE,
    PUSH_TEMP,
    POP_TEMP,
    DEFINE_FUNCTION,
    END_DEFINE_FUNCTION,
    ADD_FUNCTION_ARGUMENT,
    CALL,
    RETURN,
    NAMESPACE_ACCESS,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULO,
    EXPONENT,
    SET,
    JUMP,
    BRANCH_IF,
    ASSEMBLY_MAX
};

const std::map<Assembly, std::string> instructionNames = {
    { Assembly::DECLARE, "dec" },
    { Assembly::PUSH_TEMP, "push" },
    { Assembly::POP_TEMP, "pop" },
    { Assembly::DEFINE_FUNCTION, "dfn" },
    { Assembly::END_DEFINE_FUNCTION, "edfn" },
    { Assembly::ADD_FUNCTION_ARGUMENT, "fnarg" },
    { Assembly::CALL, "call" },
    { Assembly::RETURN, "ret" },
    { Assembly::NAMESPACE_ACCESS, "nsa" },
    { Assembly::ADD, "add" },
    { Assembly::SUBTRACT, "sub" },
    { Assembly::MULTIPLY, "mul" },
    { Assembly::DIVIDE, "div" },
    { Assembly::MODULO, "mod" },
    { Assembly::EXPONENT, "exp" },
    { Assembly::SET, "set" },
    { Assembly::JUMP, "jmp" },
    { Assembly::BRANCH_IF, "bif" },
};
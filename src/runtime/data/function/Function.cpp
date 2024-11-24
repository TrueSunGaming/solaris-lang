#include "Function.hpp"

Function::Function(Object *returnObj, std::vector<FunctionArgument> args) :
    Object(ValueType::FUNCTION),
    returnObj(returnObj),
    args(args) {}
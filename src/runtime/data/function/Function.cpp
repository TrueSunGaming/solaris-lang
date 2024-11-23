#include "Function.hpp"

Function::Function(Object *returnObj, std::vector<FunctionArgument> args) :
    returnObj(returnObj),
    args(args) {}
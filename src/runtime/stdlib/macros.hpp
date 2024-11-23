#pragma once

#include "../state/AbstractFunctionCaller.hpp"
#include <vector>

#define CFUNC(name, rt, args) Object *name(AbstractFunctionCaller *rt, const std::vector<Object *>& args)
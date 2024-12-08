#include "SolarisFunction.hpp"

void SolarisFunction::call(AbstractFunctionCaller *runtime, const std::vector<Object *>& args) const {
    if (args.size() < this->args.size()) throw std::runtime_error("Runtime Error: Not enough arguments passed to " + name);

    runtime->pushReturn(id);
    runtime->jump(startLine);
    runtime->createScope();

    for (size_t i = 0; i < this->args.size(); i++) {
        const FunctionArgument& arg = this->args[i];
        Object *passed = args[i];
        if (!passed->is(arg.type)) throw std::runtime_error("Runtime Error: Invalid type in argument " + std::to_string(i + 1) + " of " + name + " call. Expected " + std::to_string((int)arg.type) + " but found " + std::to_string((int)passed->getType()) + " instead");

        runtime->setObject(arg.name, passed->clone().release());
    }
}
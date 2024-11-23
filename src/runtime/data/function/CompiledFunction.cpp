#include "CompiledFunction.hpp"

CompiledFunction::CompiledFunction(Definition def, Object *returnObj, std::vector<FunctionArgument> args) :
    Function(returnObj, args),
    def(def) {}

void CompiledFunction::call(AbstractFunctionCaller *runtime, const std::vector<Object *>& args) const {
    def(runtime, args);
}
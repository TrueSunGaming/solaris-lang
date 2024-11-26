#include "SolarisFunction.hpp"

#include "../../state/RuntimeState.hpp"

void SolarisFunction::call(AbstractFunctionCaller *runtime, const std::vector<Object *>& args) const {
    runtime->pushReturn(id);
    runtime->jump(startLine);
}
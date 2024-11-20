#include "SolarisFunction.hpp"
#include <iostream>
#include "../../state/RuntimeState.hpp"

void SolarisFunction::call(AbstractRuntimeState *runtime, std::vector<Object *> args) const {
    runtime->pushReturn(id);
    runtime->jump(startLine);
}
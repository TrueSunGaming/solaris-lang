#include "SolarisFunction.hpp"

void SolarisFunction::call(AbstractRuntimeState& runtime, std::vector<Object *> args) const {
    runtime.pushReturn(id);
    runtime.jump(startLine);
}
#include "SolarisFunction.hpp"

void SolarisFunction::call(RuntimeState& runtime, std::vector<Object *> args) const {
    runtime.pushReturn(id);
    runtime.jump(startLine);
}
#include "../RuntimeState.hpp"

STEP_DEFINITION(ADD_FUNCTION_ARGUMENT) {
    SolarisFunction *fn = getFunction(std::stoull(args[0]));
    if (!fn) throw std::runtime_error("Function with id " + args[0] + " does not exist");

    fn->args.emplace_back(args[1], ValueType::NULL_VAL);
}
#include "../RuntimeState.hpp"

STEP_DEFINITION(SET) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Set requires 2 arguments");

    Object *obj = getObject(args[0]);
    if (!obj) throw std::runtime_error("Variable '" + args[0] + "' does not exist");

    std::vector<std::unique_ptr<Object>> created;
    *obj = getOrCreateObject(args[1], created);
}
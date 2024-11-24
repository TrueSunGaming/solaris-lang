#include "../RuntimeState.hpp"

STEP_DEFINITION(DIVIDE) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Divide requires 2 arguments");

    std::vector<std::unique_ptr<Object>> created;

    Object *lhs = getOrCreateObject(args[0], created);
    Object *rhs = getOrCreateObject(args[1], created);

    if (lhs->getType() != rhs->getType()) throw std::runtime_error("Mismatched types in division");

    switch (lhs->getType()) {
        case ValueType::INTEGER:
            return moveTemp(OBJ_OPERATION(lhs, rhs, /, INTEGER, int64_t));
        
        case ValueType::FLOAT:
            return moveTemp(OBJ_OPERATION(lhs, rhs, /, FLOAT, double));
        
        default:
            throw std::runtime_error("Cannot divide type " + std::to_string((int)lhs->getType()));
    }
}
#include "../RuntimeState.hpp"

STEP_DEFINITION(SUBTRACT) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Subtract requires 2 arguments");

    std::vector<std::unique_ptr<Object>> created;

    Object *lhs = getOrCreateObject(args[0], created);
    Object *rhs = getOrCreateObject(args[1], created);

    if (lhs->getType() != rhs->getType()) throw std::runtime_error("Mismatched types in subtraction");

    switch (lhs->getType()) {
        case ValueType::INTEGER:
            return moveTemp(OBJ_OPERATION(lhs, rhs, -, INTEGER, int64_t));
        
        case ValueType::FLOAT:
            return moveTemp(OBJ_OPERATION(lhs, rhs, -, FLOAT, double));
        
        default:
            throw std::runtime_error("Cannot subtract type " + std::to_string((int)lhs->getType()));
    }
}
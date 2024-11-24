#include "../RuntimeState.hpp"

STEP_DEFINITION(MODULO) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Modulo requires 2 arguments");

    std::vector<std::unique_ptr<Object>> created;

    Object *lhs = getOrCreateObject(args[0], created);
    Object *rhs = getOrCreateObject(args[1], created);

    if (lhs->getType() != rhs->getType()) throw std::runtime_error("Mismatched types in modulation");

    switch (lhs->getType()) {
        case ValueType::INTEGER:
            return moveTemp(OBJ_OPERATION(lhs, rhs, %, INTEGER, int64_t));
        
        case ValueType::FLOAT: {
            double rem = lhs->getValueAs<double>();
            double divisor = rhs->getValueAs<double>();

            while (rem >= divisor) rem -= divisor;

            return moveTemp(std::make_unique<Object>(ValueType::FLOAT, new double(rem)));
        }
        
        default:
            throw std::runtime_error("Cannot modulate type " + std::to_string((int)lhs->getType()));
    }
}
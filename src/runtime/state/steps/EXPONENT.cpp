#include "../RuntimeState.hpp"
#include <cmath>

STEP_DEFINITION(EXPONENT) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Exponent requires 2 arguments");

    std::vector<std::unique_ptr<Object>> created;

    Object *lhs = getOrCreateObject(args[0], created);
    Object *rhs = getOrCreateObject(args[1], created);

    if (lhs->getType() != rhs->getType()) throw std::runtime_error("Mismatched types in exponentiation");

    switch (lhs->getType()) {
        case ValueType::INTEGER:
            return moveTemp(std::make_unique<Object>(ValueType::INTEGER, new int64_t(pow(lhs->getValueAs<int64_t>(), rhs->getValueAs<int64_t>()))));
        
        case ValueType::FLOAT:
            return moveTemp(std::make_unique<Object>(ValueType::FLOAT, new double(pow(lhs->getValueAs<double>(), rhs->getValueAs<double>()))));
        
        default:
            throw std::runtime_error("Cannot exponentiate type " + std::to_string((int)lhs->getType()));
    }
}
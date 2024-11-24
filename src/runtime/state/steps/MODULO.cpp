#include "../RuntimeState.hpp"
#include <cmath>

STEP_DEFINITION(MODULO) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Modulo requires 2 arguments");

    std::vector<std::unique_ptr<Object>> created;

    Object *lhs = getOrCreateObject(args[0], created);
    Object *rhs = getOrCreateObject(args[1], created);

    if (!lhs->is({ rhs->getType(), ValueType::FLOAT })) throw std::runtime_error("Mismatched types in modulation");
    if (lhs->is(ValueType::FLOAT) && !rhs->is({ ValueType::FLOAT, ValueType::INTEGER })) throw std::runtime_error("Float modulation requires a right-hand side of an integer or float");

    switch (lhs->getType()) {
        case ValueType::INTEGER:
            return moveTemp(OBJ_OPERATION(lhs, rhs, %, INTEGER, int64_t));
        
        case ValueType::FLOAT: {
            double dividend = lhs->getValueAs<double>();
            double divisor = rhs->is(ValueType::FLOAT) ? rhs->getValueAs<double>() : (double)rhs->getValueAs<int64_t>();

            return moveTemp(std::make_unique<Object>(ValueType::FLOAT, new double(dividend - floor(dividend / divisor) * divisor)));
        }
        
        default:
            throw std::runtime_error("Cannot modulate type " + std::to_string((int)lhs->getType()));
    }
}
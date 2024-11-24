#include "../RuntimeState.hpp"

STEP_DEFINITION(MULTIPLY) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Multiply requires 2 arguments");

    std::vector<std::unique_ptr<Object>> created;

    Object *lhs = getOrCreateObject(args[0], created);
    Object *rhs = getOrCreateObject(args[1], created);

    if (lhs->getType() != rhs->getType() && lhs->getType() != ValueType::STRING) throw std::runtime_error("Mismatched types in multiplication");
    if (lhs->getType() == ValueType::STRING && rhs->getType() != ValueType::INTEGER) throw std::runtime_error("String multiplication requires a right-hand side of an integer");

    switch (lhs->getType()) {
        case ValueType::INTEGER:
            return moveTemp(OBJ_OPERATION(lhs, rhs, *, INTEGER, int64_t));
        
        case ValueType::FLOAT:
            return moveTemp(OBJ_OPERATION(lhs, rhs, *, FLOAT, double));
        
        case ValueType::STRING: {
            std::string res = "";

            std::string repeated = lhs->getValueAs<std::string>();
            int64_t count = rhs->getValueAs<int64_t>();

            for (int64_t i = 0; i < count; i++) res += repeated;

            return moveTemp(std::make_unique<Object>(ValueType::STRING, new std::string(res)));
        }
        
        default:
            throw std::runtime_error("Cannot multiply type " + std::to_string((int)lhs->getType()));
    }
}
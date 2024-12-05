#include "println.hpp"
#include <iostream>

CFUNC(SolarisStdlib::println, runtime, args) {
    for (size_t i = 0; i < args.size(); i++) {
        Object *obj = args[i];

        switch (obj->getType()) {
            case ValueType::STRING:
                std::cout << obj->getValueAs<std::string>();
                break;
            
            case ValueType::INTEGER:
                std::cout << obj->getValueAs<int64_t>();
                break;
            
            case ValueType::FLOAT:
                std::cout << std::to_string(obj->getValueAs<double>());
                break;
            
            case ValueType::BOOLEAN: {
                bool val = obj->getValueAs<bool>();
                std::cout << (val ? "true" : "false");
                break;
            }
            
            case ValueType::NULL_VAL:
                std::cout << "null";
                break;
            
            default:
                std::cout << "[Object " << obj << " (type " << (int)obj->getType() << ")]";
        }

        if (i != args.size() - 1) std::cout << " ";
    }

    std::cout << std::endl;
    return nullptr;
}
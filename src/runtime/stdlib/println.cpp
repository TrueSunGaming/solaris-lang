#include "println.hpp"
#include <iostream>

CFUNC(SolarisStdlib::println, runtime, args) {
    for (size_t i = 0; i < args.size(); i++) {
        std::cout << args[i]->toString();
        if (i != args.size() - 1) std::cout << " ";
    }

    std::cout << std::endl;
    return nullptr;
}
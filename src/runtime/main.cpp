#include "state/RuntimeState.hpp"
#include "data/function/CompiledFunction.hpp"
#include "stdlib/println.hpp"
#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) throw std::runtime_error("Please provide an assembly file as an argument");

    RuntimeState runtime = RuntimeState(std::string(argv[1]).ends_with(".solex") ? argv[1] : std::string(argv[1]) + ".solex");

    Object *stdlib = new Object(ValueType::NAMESPACE);

    runtime.getGlobalScope()->setMember("std", stdlib);
    stdlib->moveMember("println", std::make_unique<CompiledFunction>(SolarisStdlib::println));

    std::vector<Object *> v;
    v.push_back(new Object());
    v.push_back(new Object());
    v.push_back(new Object());
    v.erase(v.end() - 4, v.end() - 1);
    v.push_back(new Object());

    while (true) runtime.step();
}
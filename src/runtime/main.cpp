#include "state/RuntimeState.hpp"
#include "data/function/CompiledFunction.hpp"
#include "stdlib/println.hpp"
#include "../universal/util/getFlags.hpp"
#include <stdexcept>

int main(int argc, char *argv[]) {
    if (argc < 2) throw std::runtime_error("Please provide an assembly file as an argument");

    std::unordered_set<std::string> flags = getFlags(argc, argv);

    RuntimeState runtime = RuntimeState(std::string(argv[1]).ends_with(".solex") ? argv[1] : std::string(argv[1]) + ".solex", flags.contains("debug"));

    Object *stdlib = new Object(ValueType::NAMESPACE);

    runtime.getGlobalScope()->setMember("std", stdlib);
    stdlib->moveMember("println", std::make_unique<CompiledFunction>(SolarisStdlib::println));

    while (true) runtime.step();
}
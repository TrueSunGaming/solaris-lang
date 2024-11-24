#include "../RuntimeState.hpp"

STEP_DEFINITION(DEFINE_FUNCTION) {
    SolarisFunction *fn = new SolarisFunction();
    fn->startLine = line;
    fn->id = std::stoull(args[1]);
    fn->name = args[0];
    getCurrentScope()->setMember(fn->name, fn);
    
    while (std::get<0>(instructions[line]) != Assembly::END_DEFINE_FUNCTION) {
        if (line > instructions.size() - 1) throw std::runtime_error("Assembly Syntax Error: Unexpected EOF while defining function");
        line++;
    }
}
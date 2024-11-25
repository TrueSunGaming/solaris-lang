#include "../RuntimeState.hpp"

STEP_DEFINITION(DECLARE) {
    if (args.size() < 2) throw std::runtime_error("Assembly Syntax Error: Declare requires 2 arguments");

    Scope *scope = getCurrentScope();

    scope->createMember(args[0], determineType(std::vector(args.begin() + 1, args.end())));
    pushTemp(scope->getMember(args[0]));
}
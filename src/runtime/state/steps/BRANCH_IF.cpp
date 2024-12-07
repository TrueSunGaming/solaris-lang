#include "../RuntimeState.hpp"

STEP_DEFINITION(BRANCH_IF) {
    if (args.size() < 3) throw std::runtime_error("Assembly Syntax Error: BRANCH_IF requires 3 arguments");

    pushReturn();
    
    std::vector<std::unique_ptr<Object>> created;
    jumpForward(std::stoll(args[getOrCreateObject(args[0], created)->isTruthy() ? 1 : 2]));
}
#include "../RuntimeState.hpp"

STEP_DEFINITION(JUMP) {
    if (args.size() < 1) throw std::runtime_error("Assembly Syntax Error: JUMP requires an argument");

    jumpForward(std::stoll(args[0]));
}
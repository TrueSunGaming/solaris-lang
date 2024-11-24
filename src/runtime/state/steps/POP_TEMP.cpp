#include "../RuntimeState.hpp"

STEP_DEFINITION(POP_TEMP) {
    size_t delCount = args.size() >= 1 ? std::stoull(args[0]) : 1;
    size_t startIndex = args.size() >= 2 ? std::stoull(args[1]) : 0;

    for (size_t i = 0; i < delCount; i++) tempStack.erase(tempStack.end() - startIndex - 1);
}
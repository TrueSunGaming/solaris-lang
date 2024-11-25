#include "../RuntimeState.hpp"
#include <iostream>

STEP_DEFINITION(POP_TEMP) {
    size_t delCount = args.size() >= 1 ? std::stoull(args[0]) : 1;
    size_t startIndex = args.size() >= 2 ? std::stoull(args[1]) : 0;

    std::cout << "hi\n";
    tempStack.erase(tempStack.end() - startIndex - delCount, tempStack.end() - startIndex);
    std::cout << "hi 2\n";
    tempStack.shrink_to_fit();
    std::cout << "hi 3\n";
}
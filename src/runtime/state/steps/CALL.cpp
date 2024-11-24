#include "../RuntimeState.hpp"

STEP_DEFINITION(CALL) {
    if (args.size() < 1) throw std::runtime_error("Assembly Syntax Error: No function provided to call");
    
    Function *fn = (Function *)getObject(args[0]);
    if (!fn) throw std::runtime_error("Function '" + args[0] + "' does not exist");

    std::vector<Object *> parsedArgs;
    std::vector<std::unique_ptr<Object>> created;
    for (size_t i = 1; i < args.size(); i++) {
        parsedArgs.push_back(getOrCreateObject(args[i], created));
    }

    fn->call(this, parsedArgs);
}
#include "RuntimeState.hpp"
#include "../../universal/file/FileManager.hpp"
#include "../../universal/util/split.hpp"
#include "../data/function/SolarisFunction.hpp"
#include <iostream>

RuntimeState::Instructions RuntimeState::load(const std::string& filename) {
    FileManager file = FileManager(filename);
    std::string content = file.read();
    std::vector<std::string> lines = split(content, "\n");

    Instructions res;
    
    for (const auto& i : lines) {
        std::vector<std::string> parts;
        char openingQuote = '\0';
        std::string currentPart;

        for (char c : i) {
            if (currentPart.size() && openingQuote == '\0' && c == ' ') {
                parts.push_back(currentPart);
                currentPart.clear();
                continue;
            }

            if (c == '"' || c == '\'') {
                if (c == openingQuote) openingQuote = '\0';
                else if (!openingQuote) openingQuote = c;
            }

            if (c != ' ' || openingQuote != '\0') currentPart += c;
        }

        if (openingQuote != '\0') throw std::runtime_error("Assembly Syntax Error: Unexpected EOL while parsing string");

        parts.push_back(currentPart);

        int instruction = std::stoi(parts[0]);
        if (instruction >= (int)Assembly::ASSEMBLY_MAX) throw std::runtime_error("Assembly Syntax Error: Invalid instruction " + std::to_string((int)instruction));

        res.push_back({ (Assembly)instruction, std::vector<std::string>(parts.begin() + 1, parts.end()) });
    }

    return res;
}

RuntimeState::RuntimeState(const std::string& filename) :
    instructions(load(filename)),
    globalScope(std::make_unique<Scope>()) {}

Object *RuntimeState::getObject(std::string name) {
    return getCurrentScope()->findAndGetMember(name, globalScope.get());
}

SolarisFunction *RuntimeState::getFunction(size_t id) {
    return getCurrentScope()->findAndGetFunction(id, globalScope.get());
}

Scope *RuntimeState::getCurrentScope() {
    return activeScope ? activeScope : globalScope.get();
}

std::vector<Object *> RuntimeState::parseArgs(std::vector<std::string> args) {
    std::vector<Object *> res;
    for (const auto& i : args) {
        res.push_back(getObject(i));
        if (!res.back()) throw std::runtime_error("Variable '" + i + "' does not exist");
    }

    return res;
}

size_t RuntimeState::getLine() const {
    return line;
}

void RuntimeState::step() {
    std::cout << "Running line " << line << "\n";
    
    if (line >= instructions.size()) {
        std::cout << "Execution complete\n";
        return exit(0);
    }

    Assembly instruction = std::get<0>(instructions[line]);
    std::vector<std::string> args = std::get<1>(instructions[line]);

    switch (instruction) {
        case Assembly::CALL: {
            std::string functionName = args[0];
            
            Function *fn = (Function *)getObject(functionName);
            if (!fn) throw std::runtime_error("Function '" + functionName + "' does not exist");

            fn->call(this, parseArgs(std::vector(args.begin() + 1, args.end())));
            break;
        }

        case Assembly::DEFINE_FUNCTION: {
            SolarisFunction *fn = new SolarisFunction();
            fn->startLine = line;
            fn->id = std::stoull(args[1]);
            fn->name = args[0];
            getCurrentScope()->setMember(fn->name, fn);
            std::cout << "Function defined with id " + args[1] + "\n";
            
            while (std::get<0>(instructions[line]) != Assembly::END_DEFINE_FUNCTION) {
                if (line > instructions.size() - 1) throw std::runtime_error("Assembly Syntax Error: Unexpected EOF while defining function");
                line++;
            }

            break;
        }

        case Assembly::ADD_FUNCTION_ARGUMENT: {
            SolarisFunction *fn = getFunction(std::stoull(args[0]));
            if (!fn) throw std::runtime_error("Function with id " + args[0] + " does not exist");

            fn->args.emplace_back(args[1], ValueType::NULL_VAL);
            break;
        }

        case Assembly::END_DEFINE_FUNCTION:
            ret();
            break;

        default:
            throw std::runtime_error("Unknown instruction " + std::to_string((int)instruction));
    }

    line++;
}

void RuntimeState::jump(size_t line) {
    this->line = std::min(line, instructions.size() - 1);
}

void RuntimeState::ret() {
    if (!returnStack.size()) return;

    FunctionReturnState data = returnStack.top();
    returnStack.pop();

    jump(data.line);
}

void RuntimeState::pushReturn(size_t functionID) {
    returnStack.push({ functionID, line });
}

Object *RuntimeState::getReturnObject() {
    if (returnStack.empty()) return nullptr;

    Function *fn = getFunction(returnStack.top().functionID);
    return fn ? fn->returnObj : nullptr;
}
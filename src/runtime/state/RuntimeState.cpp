#include "RuntimeState.hpp"
#include "../../universal/file/FileManager.hpp"
#include "../../universal/util/split.hpp"
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

RuntimeState::RuntimeState(const std::string& filename) : instructions(load(filename)) {}

std::vector<Object *> RuntimeState::parseArgs(std::vector<std::string> args) const {
    std::vector<Object *> res;
    for (const auto& i : args) {
        res.push_back(activeScope->findAndGetMember(i, globalScope.get()));
        if (!res.back()) throw std::runtime_error("Variable '" + i + "' does not exist");
    }

    return res;
}

void RuntimeState::step() {
    if (line >= instructions.size()) return exit(0);

    Assembly instruction = std::get<0>(instructions[line]);
    std::vector<std::string> args = std::get<1>(instructions[line]);

    switch (instruction) {
        case Assembly::CALL: {
            std::string functionName = args[0];
            
            Function *function = activeScope->findAndGetFunction(functionName, globalScope.get());
            if (!function) throw std::runtime_error("Function '" + functionName + "' does not exist");

            function->call(*this, parseArgs(args));
            break;
        }

        default:
            throw std::runtime_error("Unknown instruction " + std::to_string((int)instruction));
    }

    line++;
}

void RuntimeState::jump(size_t line) {
    line = std::min(line, instructions.size() - 1);
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
    size_t id = returnStack.top().functionID;

    Scope *scope = activeScope ? activeScope->findFunction(id, globalScope.get()) : globalScope.get();
    if (!scope) return nullptr;

    Function *func = scope->getFunction(id);
    return func ? func->returnObj : nullptr;
}
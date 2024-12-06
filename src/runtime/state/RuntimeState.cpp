#include "RuntimeState.hpp"
#include "../../universal/file/FileManager.hpp"
#include "../../universal/util/split.hpp"
#include "../data/function/SolarisFunction.hpp"
#include "../../universal/tokens/TokenType.hpp"
#include "../../universal/util/scientificToNumber.hpp"
#include "../../universal/util/mergeEscape.hpp"
#include <regex>
#include <sstream>
#include <algorithm>

#define CASE_STEP(x) \
    case Assembly::x: \
        step##x(args); \
        break;

std::vector<Instruction> RuntimeState::load(const std::string& filename) {
    FileManager file = FileManager(filename);
    std::string content = file.read();
    std::vector<std::string> lines = split(content, "\n");

    std::vector<Instruction> res;
    
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
    globalScope(std::make_unique<Scope>()) {
    
    size_t tempSize = 0;

    for (const auto& i : instructions) {
        for (const auto& j : std::get<1>(i)) {
            if (!j.starts_with("%tmp")) continue;

            size_t index = std::stoull(j.substr(4));
            if (index >= tempSize) tempSize = index + 1;
        }
    }
}

Object *RuntimeState::getObject(const std::string& name) {
    if (name.starts_with("%tmp")) return getTemp(std::stoull(name.substr(4)));
    return getCurrentScope()->findAndGetMember(name, globalScope.get());
}

void RuntimeState::setObject(const std::string& name, Object *value) {
    getCurrentScope()->setMember(name, value);
}

std::unique_ptr<Object> RuntimeState::createObject(const std::string& val) {
    if (val.starts_with("\"") || val.starts_with("'")) {
        return std::make_unique<Object>(ValueType::STRING, new std::string(mergeEscape(val.substr(1, val.size() - 2))));
    }

    if (std::regex_match(val, std::regex(tokenRegexMap.at(TokenType::FLOAT)))) {
        return std::make_unique<Object>(ValueType::FLOAT, new double(scientificToNumber<double>(val)));
    }

    if (std::regex_match(val, std::regex(tokenRegexMap.at(TokenType::INTEGER)))) {
        return std::make_unique<Object>(ValueType::INTEGER, new int64_t(scientificToNumber<int64_t>(val)));
    }

    if (val == "true") return std::make_unique<Object>(ValueType::BOOLEAN, new bool(true));
    if (val == "false") return std::make_unique<Object>(ValueType::BOOLEAN, new bool(false));

    throw std::runtime_error("Failed to create object from value: " + val);
}

Object *RuntimeState::getOrCreateObject(const std::string& val, std::vector<std::unique_ptr<Object>>& created) {
    Object *obj = getObject(val);
    if (!obj) {
        try {
            created.push_back(createObject(val));
            obj = created.back().get();
        } catch (std::exception e) {
            throw std::runtime_error("Variable '" + val + "' does not exist and a value could not be created");
        }
    }

    return obj;
}

ValueType RuntimeState::determineType(const std::vector<std::string>& args) const {
    if (std::find_if(args.begin(), args.end(), [](const std::string& v) {
        return v == "array";
    }) != args.end()) return ValueType::ARRAY;

    if (args[0] == "string") return ValueType::STRING;
    if (args[0] == "int") return ValueType::INTEGER;
    if (args[0] == "float") return ValueType::FLOAT;
    if (args[0] == "bool") return ValueType::BOOLEAN;
    if (args[0] == "null") return ValueType::NULL_VAL;

    return ValueType::OBJECT;
}

SolarisFunction *RuntimeState::getFunction(size_t id) {
    return getCurrentScope()->findAndGetFunction(id, globalScope.get());
}

Scope *RuntimeState::getCurrentScope() {
    return activeScope ? activeScope : globalScope.get();
}

Scope *RuntimeState::getGlobalScope() {
    return globalScope.get();
}

void RuntimeState::createScope() {
    std::unique_ptr<Scope> scope = std::make_unique<Scope>();
    scope->parent = activeScope;
    activeScope = scope.get();
    scopes.push_back(std::move(scope));
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
    if (line >= instructions.size()) return exit(0);

    Assembly instruction = std::get<0>(instructions[line]);
    std::vector<std::string> args = std::get<1>(instructions[line]);

    switch (instruction) {
        CASE_STEP(DECLARE)
        CASE_STEP(PUSH_TEMP)
        CASE_STEP(POP_TEMP)
        CASE_STEP(DEFINE_FUNCTION)
        CASE_STEP(END_DEFINE_FUNCTION)
        CASE_STEP(ADD_FUNCTION_ARGUMENT)
        CASE_STEP(CALL)
        CASE_STEP(RETURN)
        CASE_STEP(NAMESPACE_ACCESS)
        CASE_STEP(ADD)
        CASE_STEP(SUBTRACT)
        CASE_STEP(MULTIPLY)
        CASE_STEP(DIVIDE)
        CASE_STEP(MODULO)
        CASE_STEP(EXPONENT)
        CASE_STEP(SET)

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

    Scope *scope = activeScope;
    activeScope = scope->parent;
    scopes.erase(std::find_if(scopes.begin(), scopes.end(), [scope] (std::unique_ptr<Scope>& v) {
        return v.get() == scope;
    }));

    jump(data.line);
}

void RuntimeState::pushReturn(size_t functionID) {
    returnStack.push({ functionID, line });
}

void RuntimeState::pushTemp(Object *obj) {
    tempStack.push(obj);
}

void RuntimeState::moveTemp(Object *obj) {
    tempStack.move(obj);
}

void RuntimeState::moveTemp(std::unique_ptr<Object> obj) {
    tempStack.move(std::move(obj));
}

void RuntimeState::popTemp() {
    tempStack.pop();
}

Object *RuntimeState::getTemp(size_t idx) {
    return tempStack.get(idx);
}

std::vector<Object *> RuntimeState::getTemp(const std::vector<size_t>& idxs) {
    return tempStack.get(idxs);
}

Object *RuntimeState::getReturnObject() {
    if (returnStack.empty()) return nullptr;

    Function *fn = getFunction(returnStack.top().functionID);
    return fn ? fn->returnObj : nullptr;
}
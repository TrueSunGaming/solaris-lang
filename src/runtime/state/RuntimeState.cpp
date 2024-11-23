#include "RuntimeState.hpp"
#include "../../universal/file/FileManager.hpp"
#include "../../universal/util/split.hpp"
#include "../data/function/SolarisFunction.hpp"
#include "../../universal/tokens/TokenType.hpp"
#include "../../universal/util/scientificToNumber.hpp"
#include <iostream>
#include <regex>
#include <sstream>

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

Object *RuntimeState::getObject(const std::string& name) {
    if (name.starts_with("%tmp")) return getTemp(std::stoull(name.substr(4)));
    return getCurrentScope()->findAndGetMember(name, globalScope.get());
}

std::unique_ptr<Object> RuntimeState::createObject(const std::string& val) {
    std::unique_ptr<Object> obj = std::make_unique<Object>();

    if (val.starts_with("\"") || val.starts_with("'")) {
        obj->setType(ValueType::STRING);
        obj->setValue(new std::string(val.substr(1, val.size() - 2)));

        return std::move(obj);
    }

    if (std::regex_match(val, std::regex(tokenRegexMap.at(TokenType::FLOAT)))) {
        obj->setType(ValueType::FLOAT);
        obj->setValue(new double(scientificToNumber<double>(val)));
        return std::move(obj);
    }

    if (std::regex_match(val, std::regex(tokenRegexMap.at(TokenType::INTEGER)))) {
        obj->setType(ValueType::INTEGER);
        obj->setValue(new int64_t(scientificToNumber<int64_t>(val)));
        return std::move(obj);
    }

    throw std::runtime_error("Failed to create object from value: " + val);
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
        
        case Assembly::PUSH_TEMP: {
            Object *obj = getObject(args[0]);
            if (obj) {
                pushTemp(obj);
                break;
            }

            moveTemp(createObject(args[0]));
            break;
        }

        case Assembly::NAMESPACE_ACCESS: {
            Object *ns = getObject(args[0]);
            if (!ns) throw std::runtime_error("Could not get namespace " + args[0]);

            Object *name = getObject(args[1]);
            if (!name || name->getType() != ValueType::STRING) throw std::runtime_error("Could not get name from " + args[1]);
            
            std::unordered_map<std::string, std::unique_ptr<Object>>& members = ns->getMembers();
            std::string memberName = name->getValueAs<std::string>();
            if (!members.contains(memberName)) throw std::runtime_error("Namespace " + args[0] + " does not contain member " + memberName);

            pushTemp(members.at(args[1]).get());
        }

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

void RuntimeState::pushTemp(Object *obj) {
    tempStack.push_back(obj);
}

void RuntimeState::moveTemp(Object *obj) {
    moveTemp(std::unique_ptr<Object>(obj));
}

void RuntimeState::moveTemp(std::unique_ptr<Object> obj) {
    pushTemp(obj.get());
    tempStorage[tempStack.size() - 1] = std::move(obj);
}

void RuntimeState::popTemp() {
    size_t len = tempStack.size();
    if (len > 0 && tempStorage.contains(len - 1)) tempStorage.erase(len - 1);
    tempStack.pop_back();
}

Object *RuntimeState::getTemp(size_t idx) {
    return tempStack[tempStack.size() - idx - 1];
}

Object *RuntimeState::getReturnObject() {
    if (returnStack.empty()) return nullptr;

    Function *fn = getFunction(returnStack.top().functionID);
    return fn ? fn->returnObj : nullptr;
}
#include "Scope.hpp"

Object *Scope::getMember(std::string name) {
    if (!members.contains(name)) return nullptr;
    return members.at(name).get();
}

Function *Scope::getFunction(size_t id) {
    if (!functions.contains(id)) return nullptr;
    return functions.at(id).get();
}

Function *Scope::getFunction(std::string name) {
    if (!functionIDs.contains(name)) return nullptr;
    return functions.at(functionIDs.at(name)).get();
}

Scope *Scope::findMember(std::string name, Scope *globalScope) {
    if (members.contains(name)) return this;
    if (parent) return parent->findMember(name, globalScope);
    if (globalScope && globalScope != this) return globalScope->findMember(name);

    return nullptr;
}

Scope *Scope::findFunction(size_t id, Scope *globalScope) {
    if (functions.contains(id)) return this;
    if (parent) return parent->findFunction(id, globalScope);
    if (globalScope && globalScope != this) return globalScope->findFunction(id);

    return nullptr;
}

Scope *Scope::findFunction(std::string name, Scope *globalScope) {
    if (functionIDs.contains(name)) return this;
    if (parent) return parent->findFunction(name, globalScope);
    if (globalScope && globalScope != this) return globalScope->findFunction(name);

    return nullptr;
}

Object *Scope::findAndGetMember(std::string name, Scope *globalScope) {
    Scope *location = findMember(name, globalScope);
    return location ? location->getMember(name) : nullptr;
}

Function *Scope::findAndGetFunction(size_t id, Scope *globalScope) {
    Scope *location = findFunction(id, globalScope);
    return location ? location->getFunction(id) : nullptr;
}

Function *Scope::findAndGetFunction(std::string name, Scope *globalScope) {
    Scope *location = findFunction(name, globalScope);
    return location ? location->getFunction(name) : nullptr;
}

void Scope::setMember(std::string name, Object *value) {
    members[name] = std::unique_ptr<Object>(value);
}

void Scope::setFunction(size_t id, Function *func) {
    functions[id] = std::unique_ptr<Function>(func);
}

void Scope::setFunction(size_t id, std::string name, Function *func) {
    setFunction(id, func);
    functionIDs[name] = id;
}

void Scope::createMember(std::string name, ValueType type) {
    Object *obj = new Object();
    obj->setType(type);
    setMember(name, obj);
}

void Scope::removeMember(std::string name) {
    members.erase(name);
}

void Scope::clear() {
    members.clear();
}
#include "Scope.hpp"

Object *Scope::getMember(std::string name) {
    if (!members.contains(name)) return nullptr;
    return members.at(name).get();
}

Scope *Scope::findMember(std::string name, Scope *globalScope) {
    if (members.contains(name)) return this;
    if (parent) return parent->findMember(name, globalScope);
    if (globalScope) return globalScope->findMember(name);

    return nullptr;
} 

void Scope::setMember(std::string name, Object *value) {
    members[name] = std::unique_ptr<Object>(value);
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
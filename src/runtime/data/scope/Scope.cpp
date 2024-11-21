#include "Scope.hpp"
#include <iostream>

Object *Scope::getMember(std::string name) {
    if (!members.contains(name)) return nullptr;
    return members.at(name).get();
}

Scope *Scope::findMember(std::string name, Scope *globalScope) {
    if (members.contains(name)) return this;
    if (parent) return parent->findMember(name, globalScope);
    if (globalScope && globalScope != this) return globalScope->findMember(name);

    return nullptr;
}

Object *Scope::findAndGetMember(std::string name, Scope *globalScope) {
    Scope *location = findMember(name, globalScope);
    return location ? location->getMember(name) : nullptr;
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

std::optional<std::string> Scope::getFunctionName(size_t id) const {
    auto it = std::find_if(std::begin(members), std::end(members), [&id](auto&& p) {
        Object *obj = p.second.get();
        SolarisFunction *cast = dynamic_cast<SolarisFunction *>((Function *)obj);
        return cast != nullptr && cast->id == id;
    });

    return it == std::end(members) ? std::nullopt : std::optional(it->first);
}

SolarisFunction *Scope::getFunction(size_t id) {
    std::optional<std::string> name = getFunctionName(id);
    if (!name) return nullptr;

    return (SolarisFunction *)getMember(*name);
}

Scope *Scope::findFunction(size_t id, Scope *globalScope) {
    if (getFunction(id)) return this;
    if (parent) return parent->findFunction(id, globalScope);
    if (globalScope && globalScope != this) return globalScope->findFunction(id);

    return nullptr;
}

SolarisFunction *Scope::findAndGetFunction(size_t id, Scope *globalScope) {
    Scope *location = findFunction(id, globalScope);
    return location ? location->getFunction(id) : nullptr;
}

void Scope::clear() {
    members.clear();
}
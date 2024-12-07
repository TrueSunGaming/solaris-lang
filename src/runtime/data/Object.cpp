#include "Object.hpp"
#include <iostream>

Object::Object(ValueType type, void *value) : type(type), raw(value) {}

Object::~Object() {
    free();
}

void Object::freeMembers() {
    members.clear();
    ownMembers.clear();
    iterableMembers.clear();
    ownIterableMembers.clear();
}

void Object::free() {
    freeMembers();

    if (!raw) return;

    switch (type) {
        case ValueType::STRING:
            delete static_cast<std::string *>(raw);
            break;
        
        case ValueType::INTEGER:
            delete static_cast<int64_t *>(raw);
            break;
        
        case ValueType::FLOAT:
            delete static_cast<double *>(raw);
            break;
        
        case ValueType::BOOLEAN:
            delete static_cast<bool *>(raw);
            break;
        
        default:
            std::cout << "POSSIBLE MEMORY LEAK: Value was not freed!!! Cannot cast type " << (size_t)type << "\n";
    }
}

void Object::clear(bool free) {
    setValue(nullptr, free);
    members.clear();
    iterableMembers.clear();
}

void *Object::getValue() const {
    return raw;
}

template <class T> T Object::getValueAs() const {
    return *static_cast<T *>(raw);
}

template int64_t Object::getValueAs<int64_t>() const;
template double Object::getValueAs<double>() const;
template std::string Object::getValueAs<std::string>() const;
template bool Object::getValueAs<bool>() const;

void Object::setValue(void *value, bool freeOld) {
    if (freeOld) free();
    else std::cout << "POSSIBLE MEMORY LEAK: Value was replaced but not freed!!!\n";
    raw = value;
}

void Object::resetValue(bool freeOld) {
    clear(freeOld);

    switch (type) {
        case ValueType::STRING:
            setValue(new std::string(""), freeOld);
            break;
        
        case ValueType::INTEGER:
            setValue(new int64_t(0), freeOld);
            break;
        
        case ValueType::FLOAT:
            setValue(new float(0), freeOld);
            break;
        
        case ValueType::BOOLEAN:
            setValue(new bool(false), freeOld);
            break;
    }
}

ValueType Object::getType() const {
    return type;
}

void Object::setType(ValueType type, bool reset) {
    this->type = type;
    if (reset) resetValue();
}

bool Object::is(ValueType type) const {
    return this->type == type;
}

bool Object::is(const std::set<ValueType> &types) const {
    return types.contains(type);
}

bool Object::isTruthy() const {
    switch(getType()) {
        case ValueType::NULL_VAL:
            return false;

        case ValueType::BOOLEAN:
            return getValueAs<bool>();
        
        case ValueType::INTEGER:
            return getValueAs<int64_t>() != 0;
        
        case ValueType::FLOAT:
            return getValueAs<double>() != 0.0;
        
        case ValueType::STRING:
            return !getValueAs<std::string>().empty();
        
        default:
            return true;
    }
}

Object *Object::getMember(const std::string& name) {
    if (!members.contains(name)) return nullptr;
    return members.at(name);
}

void Object::setMember(const std::string& name, Object *value) {
    members[name] = value;
}

void Object::moveMember(const std::string& name, Object *value) {
    moveMember(name, std::unique_ptr<Object>(value));
}

void Object::moveMember(const std::string& name, std::unique_ptr<Object> value) {
    setMember(name, value.get());
    ownMembers[name] = std::move(value);
}

void Object::removeMember(const std::string& name) {
    members.erase(name);
    ownMembers.erase(name);
}

Object *Object::getIterableMember(size_t index) {
    if (index >= iterableMembers.size()) return nullptr;
    return iterableMembers[index];
}

void Object::setIterableMember(size_t index, Object *value) {
    iterableMembers[index] = value;
    ownIterableMembers[index] = std::nullopt;
}

void Object::moveIterableMember(size_t index, Object *value) {
    moveIterableMember(index, std::unique_ptr<Object>(value));
}

void Object::moveIterableMember(size_t index, std::unique_ptr<Object> value) {
    setIterableMember(index, value.get());
    ownIterableMembers[index] = std::move(value);
}

void Object::removeIterableMember(size_t index) {
    iterableMembers.erase(iterableMembers.begin() + index);
    ownIterableMembers.erase(ownIterableMembers.begin() + index);
}

void Object::push(Object *value) {
    iterableMembers.push_back(value);
    ownIterableMembers.push_back(std::nullopt);
}

void Object::pushMove(Object *value) {
    pushMove(std::unique_ptr<Object>(value));
}

void Object::pushMove(std::unique_ptr<Object> value) {
    iterableMembers.push_back(value.get());
    ownIterableMembers.push_back(std::move(value));
}

Object *Object::pop() {
    if (iterableMembers.empty()) return nullptr;

    Object *res = iterableMembers.back();
    
    iterableMembers.pop_back();
    ownIterableMembers.pop_back();

    return res;
}

void *Object::cloneValue() {
    switch (type) {
        case ValueType::STRING:
            return new std::string(*static_cast<std::string *>(raw));
            break;
        
        case ValueType::INTEGER:
            return new int64_t(*static_cast<int64_t *>(raw));
            break;
        
        case ValueType::FLOAT:
            return new float(*static_cast<float *>(raw));
            break;
        
        case ValueType::BOOLEAN:
            return new bool(*static_cast<bool *>(raw));
            break;
        
        default:
            return nullptr;
    }
}

std::unique_ptr<Object> Object::clone() {
    std::unique_ptr<Object> obj = std::make_unique<Object>();
    *obj = this;
    return std::move(obj);
}

Object& Object::operator=(Object *other) {
    type = other->type;
    raw = other->cloneValue();

    freeMembers();

    iterableMembers.reserve(other->iterableMembers.size());

    for (auto &[k, v] : other->members) setMember(k, v);
    for (auto v : other->iterableMembers) push(v);

    return *this;
}
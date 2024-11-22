#include "Object.hpp"
#include <iostream>

Object::Object(ValueType type) : type(type) {}

Object::~Object() {
    free();
}

void Object::free() {
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
            setValue(new int(0), freeOld);
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

std::unordered_map<std::string, std::unique_ptr<Object>>& Object::getMembers() {
    return members;
}

std::vector<std::unique_ptr<Object>>& Object::getIterable() {
    return iterableMembers;
}
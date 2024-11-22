#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "ValueType.hpp"

class Object {
    private:
        void *raw = nullptr;
        ValueType type = ValueType::NULL_VAL;
        std::unordered_map<std::string, std::unique_ptr<Object>> members = {};
        std::vector<std::unique_ptr<Object>> iterableMembers = {};

    public:
        Object() = default;
        Object(ValueType type);
        ~Object();

        void free();
        void clear(bool free = true);

        void *getValue() const;
        template <class T> T getValueAs() const;
        void setValue(void *value, bool freeOld = true);
        void resetValue(bool freeOld = true);

        ValueType getType() const;
        void setType(ValueType type, bool reset = true);

        std::unordered_map<std::string, std::unique_ptr<Object>>& getMembers();
        std::vector<std::unique_ptr<Object>>& getIterable();
};
#pragma once

#include <unordered_map>
#include <map>
#include <optional>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include "ValueType.hpp"

class Object {
    private:
        void *raw = nullptr;
        ValueType type = ValueType::NULL_VAL;
        std::unordered_map<std::string, std::unique_ptr<Object>> ownMembers = {};
        std::unordered_map<std::string, Object *> members = {};
        std::vector<std::optional<std::unique_ptr<Object>>> ownIterableMembers = {};
        std::vector<Object *> iterableMembers = {};

        void freeMembers();
        void *cloneValue();

    public:
        Object() = default;
        Object(ValueType type, void *value = nullptr);
        ~Object();

        void free();
        void clear(bool free = true);

        void *getValue() const;
        template <class T> T getValueAs() const;
        void setValue(void *value, bool freeOld = true);
        void resetValue(bool freeOld = true);

        ValueType getType() const;
        void setType(ValueType type, bool reset = true);

        bool is(ValueType type) const;
        bool is(const std::set<ValueType> &types) const;
        bool isTruthy() const;

        Object *getMember(const std::string& name);
        void setMember(const std::string& name, Object *value);
        void moveMember(const std::string& name, Object *value);
        void moveMember(const std::string& name, std::unique_ptr<Object> value);
        void removeMember(const std::string& name);

        Object *getIterableMember(size_t index);
        void setIterableMember(size_t index, Object *value);
        void moveIterableMember(size_t index, Object *value);
        void moveIterableMember(size_t index, std::unique_ptr<Object> value);
        void removeIterableMember(size_t index);

        void push(Object *value);
        void pushMove(Object *value);
        void pushMove(std::unique_ptr<Object> value);

        std::unique_ptr<Object> clone();

        Object *pop();

        Object& operator=(Object *other);
};
#pragma once

#include "../Object.hpp"

class Scope {
    private:
        std::unordered_map<std::string, std::unique_ptr<Object>> members = {};

    public:
        Object *getMember(std::string name);
        void setMember(std::string name, Object *value);
        void createMember(std::string name, ValueType type);
        void removeMember(std::string name);
        void clear();
};
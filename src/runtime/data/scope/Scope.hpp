#pragma once

#include "../Object.hpp"
#include "../function/Function.hpp"

class Scope {
    private:
        std::unordered_map<std::string, std::unique_ptr<Object>> members = {};

    public:
        Scope *parent;

        Object *getMember(std::string name);
        Function *getFunction(size_t id);
        Scope *findMember(std::string name, Scope *globalScope = nullptr);
        Scope *findFunction(size_t id, Scope *globalScope = nullptr);
        void setMember(std::string name, Object *value);
        void createMember(std::string name, ValueType type);
        void removeMember(std::string name);
        void clear();
};
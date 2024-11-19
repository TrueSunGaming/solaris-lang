#pragma once

#include "../Object.hpp"
#include "../function/Function.hpp"

class Scope {
    private:
        std::unordered_map<std::string, std::unique_ptr<Object>> members = {};
        std::unordered_map<size_t, std::unique_ptr<Function>> functions = {};
        std::unordered_map<std::string, size_t> functionIDs = {};

    public:
        Scope *parent;

        Object *getMember(std::string name);
        Function *getFunction(size_t id);
        Function *getFunction(std::string name);

        Scope *findMember(std::string name, Scope *globalScope = nullptr);
        Scope *findFunction(size_t id, Scope *globalScope = nullptr);
        Scope *findFunction(std::string name, Scope *globalScope = nullptr);

        Object *findAndGetMember(std::string name, Scope *globalScope = nullptr);
        Function *findAndGetFunction(size_t id, Scope *globalScope = nullptr);
        Function *findAndGetFunction(std::string name, Scope *globalScope = nullptr);

        void setMember(std::string name, Object *value);
        void setFunction(size_t id, Function *func);
        void setFunction(size_t id, std::string name, Function *func);

        void createMember(std::string name, ValueType type);

        void removeMember(std::string name);
        void removeFunction(size_t id);
        void removeFunction(std::string name);

        void clear();
};
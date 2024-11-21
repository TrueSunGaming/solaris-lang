#pragma once

#include <optional>
#include "../Object.hpp"
#include "../function/SolarisFunction.hpp"

class Scope {
    private:
        std::unordered_map<std::string, std::unique_ptr<Object>> members = {};

    public:
        Scope *parent;

        Object *getMember(std::string name);
        Scope *findMember(std::string name, Scope *globalScope = nullptr);
        Object *findAndGetMember(std::string name, Scope *globalScope = nullptr);

        void setMember(std::string name, Object *value);
        void createMember(std::string name, ValueType type);
        void removeMember(std::string name);

        std::optional<std::string> getFunctionName(size_t id) const;
        SolarisFunction *getFunction(size_t id);
        Scope *findFunction(size_t id, Scope *globalScope = nullptr);
        SolarisFunction *findAndGetFunction(size_t id, Scope *globalScope = nullptr);

        void clear();
};
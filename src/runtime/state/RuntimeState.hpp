#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <stack>
#include <optional>
#include "../../universal/assembly/Assembly.hpp"
#include "FunctionReturnState.hpp"
#include "../data/scope/Scope.hpp"
#include "AbstractRuntimeState.hpp"

class RuntimeState : public AbstractRuntimeState {
    private:
        typedef std::vector<std::tuple<Assembly, std::vector<std::string>>> Instructions;

        Instructions instructions;
        std::stack<FunctionReturnState> returnStack;
        size_t line = 0;
        std::unique_ptr<Scope> globalScope;
        Scope *activeScope = nullptr;
        std::vector<std::unique_ptr<Scope>> scopes;
        std::vector<Object *> tempStack;

        static Instructions load(const std::string& filename);
        std::vector<Object *> parseArgs(std::vector<std::string> args);

        Object *getObject(std::string name);
        SolarisFunction *getFunction(size_t id);
        Scope *getCurrentScope();
    
    public:
        RuntimeState(const std::string& filename);

        size_t getLine() const override;
        void step() override;
        void jump(size_t line) override;
        void ret() override;
        void pushReturn(size_t functionID) override;
        Object *getReturnObject() override;
};
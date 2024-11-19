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
        Scope *activeScope;
        std::vector<std::unique_ptr<Scope>> scopes;

        static Instructions load(const std::string& filename);
        std::vector<Object *> parseArgs(std::vector<std::string> args) const;
    
    public:
        RuntimeState(const std::string& filename);

        void step() override;
        void jump(size_t line) override;
        void ret() override;
        void pushReturn(size_t functionID) override;
        Object *getReturnObject() override;
};
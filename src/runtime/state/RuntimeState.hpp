#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <stack>
#include <optional>
#include "../../universal/assembly/Assembly.hpp"
#include "../data/Object.hpp"
#include "FunctionReturnState.hpp"
#include "../data/scope/Scope.hpp"

class RuntimeState {
    private:
        typedef std::vector<std::tuple<Assembly, std::vector<std::string>>> Instructions;

        Instructions instructions;
        std::stack<FunctionReturnState> returnStack;
        size_t line = 0;
        Scope globalScope;
        std::optional<Scope> activeScope;
        std::vector<std::unique_ptr<Scope>> scopes;

        static Instructions load(const std::string& filename);
    
    public:
        RuntimeState(const std::string& filename);

        void jump(size_t line);
        void ret();
        void pushReturn(size_t functionID);
        Object *getReturnObject();
};
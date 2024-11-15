#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <stack>
#include "../../universal/assembly/Assembly.hpp"
#include "../data/Object.hpp"
#include "FunctionReturnState.hpp"

class RuntimeState {
    private:
        typedef std::vector<std::tuple<Assembly, std::vector<std::string>>> Instructions;

        Instructions instructions;
        std::stack<FunctionReturnState> returnStack;
        size_t line = 0;

        static Instructions load(const std::string& filename);
    
    public:
        RuntimeState(const std::string& filename);

        void jump(size_t line);
        void ret();
        void pushReturn(size_t functionID);
        Object *getReturnObject();
};
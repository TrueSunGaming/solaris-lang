#pragma once

#include <vector>
#include <tuple>
#include <string>
#include "../../universal/assembly/Assembly.hpp"

class RuntimeState {
    private:
        typedef std::vector<std::tuple<Assembly, std::vector<std::string>>> Instructions;

        Instructions instructions;
        size_t line = 0;

        static Instructions load(const std::string& filename);
    
    public:
        RuntimeState(const std::string& filename);
};
#pragma once

#include <string>
#include "ASTType.hpp"
#include "../../universal/util/Tree.hpp"

class AST : public Tree<std::string> {
    public:
        ASTType type;
};
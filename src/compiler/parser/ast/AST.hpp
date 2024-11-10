#pragma once

#include <string>
#include "ASTType.hpp"
#include "../../universal/util/Tree.hpp"

class AST : public Tree<std::string, AST> {
    public:
        ASTType type;

        AST(ASTType type = ASTType::BLOCK, std::string value = "");
        ~AST() = default;
};
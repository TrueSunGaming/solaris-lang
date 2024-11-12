#pragma once

#include "../../universal/assembly/Assembly.hpp"
#include "../parser/ast/AST.hpp"
#include <string>
#include <memory>
#include <vector>

class Generator {
    private:
        size_t nextID = 0;
        size_t currentScope = 0;
        size_t nextScope = 1;
        AST *ast;

        static std::string generateLine(Assembly type, const std::vector<std::string>& args = {});
        static std::string generateType(std::string type);
        std::string generateRecursive(AST *ast);
        std::string generateFunctionDefinition(AST *ast);
        std::string enterScope(size_t id);
        std::string createAndEnterScope();
    
    public:
        Generator(AST *ast);
        ~Generator() = default;

        std::string generate();
};
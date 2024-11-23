#pragma once

#include "../../universal/assembly/Assembly.hpp"
#include "../parser/ast/AST.hpp"
#include <string>
#include <memory>
#include <vector>
#include <tuple>

class Generator {
    private:
        size_t nextID = 0;
        AST *ast;

        static std::string generateLine(Assembly type, const std::vector<std::string>& args = {});
        static std::string generateType(std::string type);
        std::string generateRecursive(AST *ast);
        std::string generateFunctionDefinition(AST *ast);
        std::string generateFunctionCall(AST *ast);
        std::string generateOperation(AST *ast);
        std::string generateNamespaceAccess(AST *ast);
    
    public:
        Generator(AST *ast);
        ~Generator() = default;

        static std::string generate(AST *ast);
        std::string generateRoot();
};
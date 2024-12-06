#pragma once

#include "../../universal/assembly/Instruction.hpp"
#include "../parser/ast/AST.hpp"
#include <memory>

class Generator {
    private:
        size_t nextID = 0;
        AST *ast;
        std::vector<Instruction> res;

        static std::string generateLine(const Instruction& instruction);
        static std::string generateDebugLine(const Instruction& instruction);
        static std::string generateType(std::string type);
        std::vector<std::string> generateTypeRecursive(AST *ast);
        std::vector<Instruction> generateRecursive(AST *ast);
        std::vector<Instruction> generateFunctionDefinition(AST *ast);
        std::vector<Instruction> generateFunctionCall(AST *ast);
        std::vector<Instruction> generateOperation(AST *ast);
        std::vector<Instruction> generateNamespaceAccess(AST *ast);
        std::vector<Instruction> generateRoot();
        std::string toString() const;
        std::string toDebugString() const;
    
    public:
        Generator(AST *ast);
        ~Generator() = default;

        static std::string generate(AST *ast, bool debug = false);
};
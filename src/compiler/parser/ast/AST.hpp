#pragma once

#include <string>
#include <memory>
#include <vector>
#include "ASTType.hpp"

class AST {
    private:
        int id;
        static int aliveCount;

    public:
        ASTType type;
        std::string value;
        std::vector<std::unique_ptr<AST>> children;

        AST(ASTType type = ASTType::BLOCK, std::string value = "", std::vector<std::unique_ptr<AST>> children = {});
        ~AST();
        AST(const AST&) = delete;

        void addChild(AST *child);
        void addChild(std::unique_ptr<AST> child);
        std::unique_ptr<AST> removeChild(AST *child);
        void transferChild(AST *child, AST& newParent);
        AST *createChild(ASTType type = ASTType::BLOCK, std::string value = "");

        int getID() const;
};
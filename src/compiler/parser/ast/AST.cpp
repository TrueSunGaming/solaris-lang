#include "AST.hpp"
#include <iostream>

int AST::aliveCount = 0;

AST::AST(ASTType type, std::string value, std::vector<std::unique_ptr<AST>> children) : value(value), children(std::move(children)), type(type) {
    id = aliveCount++;
    std::cout << "AST#" << id << " created (alive count: " << aliveCount << ")\n";
}

AST::~AST() {
    aliveCount--;
    std::cout << "AST#" << id << " freed (alive count: " << aliveCount << ")\n";
}

AST *AST::createChild(ASTType type, std::string value) {
    AST *child = new AST(type, value);
    children.push_back(std::unique_ptr<AST>(child));

    return child;
}

int AST::getID() const {
    return id;
}
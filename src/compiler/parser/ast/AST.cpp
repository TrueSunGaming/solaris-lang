#include "AST.hpp"


AST::AST(ASTType type, std::string value, std::vector<std::unique_ptr<AST>> children) : value(value), children(std::move(children)), type(type) {}

void AST::addChild(AST *child) {
    children.push_back(std::unique_ptr<AST>(child));
}

void AST::addChild(std::unique_ptr<AST> child) {
    children.push_back(std::move(child));
}

std::unique_ptr<AST> AST::removeChild(AST *child) {
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i].get() == child) {
            std::unique_ptr<AST> res = std::move(children[i]);
            children.erase(children.begin() + i);
            return res;
        }
    }

    return nullptr;
}

void AST::transferChild(AST *child, AST& newParent) {
    newParent.addChild(std::move(removeChild(child)));
}

AST *AST::createChild(ASTType type, std::string value) {
    AST *child = new AST(type, value);
    addChild(child);

    return child;
}
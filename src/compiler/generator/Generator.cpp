#include "Generator.hpp"
#include "../parser/ParseData.hpp"
#include <iostream>

Generator::Generator(AST *ast) : ast(ast) {}

std::string Generator::generateLine(Assembly type, const std::vector<std::string>& args) {
    std::string res = std::to_string((int)type);
    for (const auto& i : args) res += " " + i;
    return res + "\n";
}

std::string Generator::generateType(std::string type) {
    return ParseData::baseTypes.contains(type) ? type : "%TYPE_" + type + "%";
}

std::string Generator::generateRecursive(AST *ast) {
    std::string res = "";

    switch (ast->type) {
        case ASTType::ROOT:
            for (const auto& i : ast->children) res += generateRecursive(i.get());
            break;

        case ASTType::BLOCK: {
            size_t outerScope = currentScope;

            res += createAndEnterScope();
            size_t scope = currentScope;

            for (const auto& i : ast->children) res += generateRecursive(i.get());

            res += generateLine(Assembly::DESTROY_SCOPE, { std::to_string(scope) });
            res += enterScope(outerScope);
            break;
        }

        case ASTType::DEFINE_FUNCTION:
            res += generateFunctionDefinition(ast);
            break;
    }

    return res;
}

std::string Generator::enterScope(size_t id) {
    std::string res = generateLine(Assembly::ENTER_SCOPE, { std::to_string(id) });
    currentScope = id;
    return res;
}

std::string Generator::createAndEnterScope() {
    std::string res = generateLine(Assembly::CREATE_SCOPE, { std::to_string(nextScope++) });
    res += enterScope(nextScope - 1);
    return res;
}

std::string Generator::generateFunctionDefinition(AST *ast) {
    size_t id = nextID++;

    std::string res = generateLine(Assembly::DEFINE_FUNCTION, {
        ast->value,
        std::to_string(id),
        generateType(ast->children[0]->value)
    });
    res += generateRecursive(ast->children[2].get());
    res += generateLine(Assembly::END_DEFINE_FUNCTION, { std::to_string(id) });

    for (const auto& i : ast->children[1]->children) {
        std::vector<std::string> args = {
            std::to_string(id),
            i->value,
            generateType(i->children[0]->value)
        };

        for (const auto& j : i->children[0]->children) args.push_back(j->value);

        res += generateLine(Assembly::ADD_FUNCTION_ARGUMENT, args);
    }

    return res;
}

std::string Generator::generate() {
    return generateRecursive(ast);
}
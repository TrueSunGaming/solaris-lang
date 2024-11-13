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
    return ParseData::baseTypes.contains(type) ? type : "%type_" + type ;
}

std::string Generator::generateRecursive(AST *ast) {
    std::string res = "";

    switch (ast->type) {
        case ASTType::ROOT:
        case ASTType::BLOCK:
            for (const auto& i : ast->children) res += generateRecursive(i.get());
            break;

        case ASTType::DEFINE_FUNCTION:
            res += generateFunctionDefinition(ast);
            break;
        
        case ASTType::CALL:
            res += generateFunctionCall(ast);
            break;
        
        case ASTType::OPERATION:
            res += generateOperation(ast);
            break;
        
        case ASTType::STRING:
            res += generateLine(Assembly::PUSH_TEMP, { "string", "\"" + ast->value + "\"" });
            break;
        
        case ASTType::GET:
            res += generateLine(Assembly::PUSH_TEMP, { "?", ast->value });
            break;
    }

    if (ast->type == ASTType::ROOT) res += generateLine(Assembly::CALL, { "main" });

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

std::string Generator::generateFunctionCall(AST *ast) {
    std::string res = "";

    std::string identifier = ast->value;
    std::vector<std::unique_ptr<AST>>& argAST = ast->children[1]->children;
    bool usingTemp = !identifier.size();

    std::vector<std::string> args = { usingTemp ? "%tmp0" : identifier };
    
    for (size_t i = 0; i < argAST.size(); i++) {
        res += generateRecursive(argAST[i].get());
        args.push_back("%tmp" + std::to_string(argAST.size() - i + size_t(usingTemp) - 1));
    }

    if (usingTemp) res += generateRecursive(ast->children[0].get());

    res += generateLine(Assembly::CALL, args);
    if (usingTemp || argAST.size()) res += generateLine(Assembly::POP_TEMP, { std::to_string(size_t(usingTemp) + argAST.size()), "0" });

    return res;
}

std::string Generator::generateOperation(AST *ast) {
    std::string res = "";

    res += generateRecursive(ast->children[0].get());
    res += generateRecursive(ast->children[1].get());

    if (ast->value == "::") res += generateLine(Assembly::NAMESPACE_ACCESS, { "%tmp1", "%tmp0" });
    else res += generateLine(Assembly::PUSH_TEMP, { "null", "null" });

    res += generateLine(Assembly::POP_TEMP, { "2", "1" });

    return res;
}

std::string Generator::generateRoot() {
    return generateRecursive(ast);
}

std::string Generator::generate(AST *ast) {
    Generator gen = Generator(ast);
    return gen.generateRoot();
}
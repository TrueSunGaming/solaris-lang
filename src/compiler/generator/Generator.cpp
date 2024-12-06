#include "Generator.hpp"
#include "../parser/ParseData.hpp"
#include "../../universal/util/concat.hpp"
#include <iostream>

Generator::Generator(AST *ast) : ast(ast) {}

std::string Generator::generateLine(const Instruction& instruction) {
    std::string line = std::to_string((int)std::get<0>(instruction));
    for (const auto& i : std::get<1>(instruction)) line += " " + i;
    return line + "\n";
}

std::string Generator::generateDebugLine(const Instruction& instruction) {
    std::string line = instructionNames.at(std::get<0>(instruction));
    for (const auto& i : std::get<1>(instruction)) line += " " + i;
    return line + "\n";
}

std::string Generator::generateType(std::string type) {
    return ParseData::baseTypes.contains(type) ? type : "%type_" + type ;
}

std::vector<std::string> Generator::generateTypeRecursive(AST *ast) {
    std::vector<std::string> type = { ast->value };

    for (const auto& i : ast->children) {
        for (const auto& j : generateTypeRecursive(i.get())) type.push_back(j);
    }

    return type;
}

std::vector<Instruction> Generator::generateRecursive(AST *ast) {
    if (!ast) return {};

    std::vector<Instruction> instructions = {};

    switch (ast->type) {
        case ASTType::ROOT:
        case ASTType::BLOCK:
            for (const auto& i : ast->children) concat(instructions, generateRecursive(i.get()));
            break;

        case ASTType::DEFINE_FUNCTION:
            concat(instructions, generateFunctionDefinition(ast));
            break;
        
        case ASTType::CALL:
            concat(instructions, generateFunctionCall(ast));
            break;
        
        case ASTType::OPERATION:
            concat(instructions, generateOperation(ast));
            break;
        
        case ASTType::STRING:
            instructions.push_back({ Assembly::PUSH_TEMP, { "\"" + ast->value + "\"" } });
            break;
        
        case ASTType::FLOAT:
        case ASTType::INTEGER:
        case ASTType::BOOLEAN:
            instructions.push_back({ Assembly::PUSH_TEMP, { ast->value } });
            break;
        
        case ASTType::GET:
            instructions.push_back({ Assembly::PUSH_TEMP, { ast->value } });
            break;
        
        case ASTType::DECLARE: {
            std::vector<std::string> args = {
                ast->value
            };

            for (const auto& i : generateTypeRecursive(ast->children[0].get())) args.push_back(i);

            instructions.push_back({ Assembly::DECLARE, args });
            break;
        }

        case ASTType::RETURN: {
            if (ast->children.size() > 0) concat(instructions, generateRecursive(ast->children[0].get()));
            instructions.push_back({ Assembly::RETURN, {} });
            
            break;
        }
    }

    if (ast->type == ASTType::ROOT) instructions.push_back({ Assembly::CALL, { "main" } });

    return instructions;
}

std::vector<Instruction> Generator::generateFunctionDefinition(AST *ast) {
    if (ast->children.size() < 3) throw std::runtime_error("Function definition requires 3 AST children");

    size_t id = nextID++;

    std::vector<Instruction> instructions = { { Assembly::DEFINE_FUNCTION, {
        ast->value,
        std::to_string(id),
        generateType(ast->children[0]->value)
    } } };
    concat(instructions, generateRecursive(ast->children[2].get()));
    instructions.push_back({ Assembly::END_DEFINE_FUNCTION, { std::to_string(id) } });

    for (const auto& i : ast->children[1]->children) {
        std::vector<std::string> args = {
            std::to_string(id),
            i->value
        };
        concat(args, generateTypeRecursive(i->children[0].get()));

        instructions.push_back({ Assembly::ADD_FUNCTION_ARGUMENT, args });
    }

    return instructions;
}

std::vector<Instruction> Generator::generateFunctionCall(AST *ast) {
    std::vector<Instruction> instructions;

    std::string identifier = ast->value;
    std::vector<std::unique_ptr<AST>>& argAST = ast->children[1]->children;
    bool usingTemp = !identifier.size();

    std::vector<std::string> args = { usingTemp ? "%tmp0" : identifier };
    
    for (size_t i = 0; i < argAST.size(); i++) {
        concat(instructions, generateRecursive(argAST[i].get()));
        args.push_back("%tmp" + std::to_string(argAST.size() - i + size_t(usingTemp) - 1));
    }

    if (usingTemp) concat(instructions, generateRecursive(ast->children[0].get()));

    instructions.push_back({ Assembly::CALL, args });
    if (usingTemp || argAST.size()) {
        std::string& returnType = ast->children[0]->value;
        instructions.push_back({ Assembly::POP_TEMP, { std::to_string(size_t(usingTemp) + argAST.size()), returnType == "void" ? "0" : "1" } });
    }

    return instructions;
}

std::vector<Instruction> Generator::generateOperation(AST *ast) {
    if (ast->value == "::") return generateNamespaceAccess(ast);

    std::vector<Instruction> instructions;

    concat(instructions, generateRecursive(ast->children[0].get()));
    concat(instructions, generateRecursive(ast->children[1].get()));

    if (ast->value == "+") instructions.push_back({ Assembly::ADD, { "%tmp1", "%tmp0" } });
    else if (ast->value == "-") instructions.push_back({ Assembly::SUBTRACT, { "%tmp1", "%tmp0" } });
    else if (ast->value == "*") instructions.push_back({ Assembly::MULTIPLY, { "%tmp1", "%tmp0" } });
    else if (ast->value == "/") instructions.push_back({ Assembly::DIVIDE, { "%tmp1", "%tmp0" } });
    else if (ast->value == "%") instructions.push_back({ Assembly::MODULO, { "%tmp1", "%tmp0" } });
    else if (ast->value == "**") instructions.push_back({ Assembly::EXPONENT, { "%tmp1", "%tmp0" } });
    else if (ast->value == "=") instructions.push_back({ Assembly::SET, { "%tmp1", "%tmp0" } });
    else instructions.push_back({ Assembly::PUSH_TEMP, { "null" } });

    instructions.push_back({ Assembly::POP_TEMP, { "2", "1" } });

    return instructions;
}

std::vector<Instruction> Generator::generateNamespaceAccess(AST *ast) {
    if (ast->children.size() < 2) throw std::runtime_error("Namespace access must have at least two arguments");

    std::vector<Instruction> instructions = generateRecursive(ast->children[0].get());
    instructions.push_back({ Assembly::NAMESPACE_ACCESS, { "%tmp0", "\"" + ast->children[1]->value + "\"" } });
    instructions.push_back({ Assembly::POP_TEMP, { "1", "1" } });

    return instructions;
}

std::vector<Instruction> Generator::generateRoot() {
    return generateRecursive(ast);
}

std::string Generator::toString() const {
    std::string str;
    for (const auto& i : res) str += generateLine(i);
    return str;
}

std::string Generator::toDebugString() const {
    std::string str;
    for (const auto& i : res) str += generateDebugLine(i);
    return str;
}

std::string Generator::generate(AST *ast, bool debug) {
    Generator gen = Generator(ast);
    concat(gen.res, gen.generateRoot());
    if (debug) std::cout << gen.toDebugString();
    return gen.toString();
}
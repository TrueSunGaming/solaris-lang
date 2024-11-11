#include <iostream>
#include "./lexer/minimize.hpp"
#include "./lexer/Lexer.hpp"
#include "./parser/Parser.hpp"
#include "../universal/file/FileManager.hpp"
#include "../universal/regex/SubstringPosition.hpp"

std::string astToString(const AST& ast, int depth = 0) {
    std::string res = "";

    for (int j = 0; j < depth; j++) res += "| ";
    res += ast.value + " (" + std::to_string((int)ast.type) + ", #" + std::to_string(ast.getID()) + ")\n";

    for (const auto& i : ast.children) {
        if (!i) {
            res += "NULL\n";
            continue;
        }

        res += astToString(*i, depth + 1);
    }

    return res;
}

int main() {
    FileManager file = FileManager("test.sol");
    std::vector<Token> tokens = Lexer::tokenize(file.read());

    for (const auto& i : tokens) std::cout << i.value << " (" << (int)i.type << ")\n";

    std::unique_ptr<AST> ast = Parser::parse(tokens);

    std::cout << astToString(*ast);
}
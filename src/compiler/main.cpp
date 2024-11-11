#include <iostream>
#include "./lexer/minimize.hpp"
#include "./lexer/Lexer.hpp"
#include "./parser/Parser.hpp"
#include "../universal/file/FileManager.hpp"
#include "../universal/regex/SubstringPosition.hpp"

std::string astToString(const AST& ast, int depth = 0) {
    std::string res = "";

    for (int j = 0; j < depth; j++) res += "| ";
    res += ast.value + " (" + std::to_string((int)ast.type) + ")\n";

    for (const auto& i : ast.children) res += astToString(*i, depth + 1);

    return res;
}

int main() {
    FileManager file = FileManager("test.sol");
    std::vector<Token> tokens = Lexer::tokenize(file.read());
    std::unique_ptr<AST> ast = Parser::parse(tokens);

    std::cout << astToString(*ast);
}
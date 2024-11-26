
#include "./lexer/minimize.hpp"
#include "./lexer/Lexer.hpp"
#include "./parser/Parser.hpp"
#include "./generator/Generator.hpp"
#include "../universal/file/FileManager.hpp"
#include "../universal/regex/SubstringPosition.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) throw std::runtime_error("No input file specified");
    std::string filename = argv[1];
    if (filename.ends_with(".sol")) filename.resize(filename.size() - 4);

    FileManager file = FileManager(filename + ".sol");
    std::vector<Token> tokens = Lexer::tokenize(file.read());
    std::unique_ptr<AST> ast = Parser::parse(tokens);
    std::string assembly = Generator::generate(ast.get());
    
    FileManager output = FileManager(filename + ".solex");
    output.write(assembly);
}
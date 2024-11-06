#include <iostream>
#include "./lexer/minimize.hpp"
#include "./lexer/Lexer.hpp"
#include "../universal/file/FileManager.hpp"
#include "../universal/regex/SubstringPosition.hpp"

int main() {
    FileManager file = FileManager("test.sol");
    
    for (const auto& i : Lexer::tokenize(file.read())) {
        std::cout << i.type << ": " << i.value << "\n";
    }
}
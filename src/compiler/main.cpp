#include <iostream>
#include "./lexer/minimize.hpp"
#include "../universal/file/FileManager.hpp"
#include "../universal/regex/SubstringPosition.hpp"

int main() {
    FileManager file = FileManager("test.sol");
    std::cout << minimize(file.read()) << "\n";
}
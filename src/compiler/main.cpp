#include <iostream>
#include "./tokenizer/minimize.hpp"
#include "../universal/file/FileManager.hpp"

int main() {
    FileManager file = FileManager("test.sol");
    std::cout << minimize(file.read()) << std::endl;
}
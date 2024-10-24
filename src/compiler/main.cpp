#include <iostream>
#include "../universal/string/splitString.hpp"

int main() {
    std::vector<std::string> split = splitString("hello1 hello2 hello3", " ");

    for (auto i : split) std::cout << i << std::endl;
}
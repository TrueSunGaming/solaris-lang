#include "RuntimeState.hpp"
#include "../../universal/file/FileManager.hpp"
#include "../../universal/util/split.hpp"
#include <iostream>

RuntimeState::Instructions RuntimeState::load(const std::string& filename) {
    FileManager file = FileManager(filename);
    std::string content = file.read();
    std::vector<std::string> lines = split(content, "\n");

    Instructions res;
    
    for (const auto& i : lines) {
        std::vector<std::string> parts;
        char openingQuote = '\0';
        std::string currentPart;

        for (char c : i) {
            if (currentPart.size() && openingQuote == '\0' && c == ' ') {
                parts.push_back(currentPart);
                currentPart.clear();
                continue;
            }

            if (c == '"' || c == '\'') {
                if (c == openingQuote) openingQuote = '\0';
                else if (!openingQuote) openingQuote = c;
            }

            if (c != ' ' || openingQuote != '\0') currentPart += c;
        }

        if (openingQuote != '\0') throw std::runtime_error("Assembly Syntax Error: Unexpected EOL while parsing string");

        parts.push_back(currentPart);

        int instruction = std::stoi(parts[0]);
        if (instruction >= (int)Assembly::ASSEMBLY_MAX) throw std::runtime_error("Assembly Syntax Error: Invalid instruction " + std::to_string((int)instruction));

        res.push_back({ (Assembly)instruction, parts });
    }

    return res;
}

RuntimeState::RuntimeState(const std::string& filename) : instructions(load(filename)) {}
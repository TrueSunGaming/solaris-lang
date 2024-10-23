#include "FileManager.hpp"
#include <fstream>

FileManager::FileManager(std::string path) : path(path) {}

std::string FileManager::read() const {
    std::ifstream file = std::ifstream(path);
    
    std::string res;
    std::string line;
    while (std::getline(file, line)) res += line;

    file.close();

    return res;
}

void FileManager::write(std::string content) const {
    std::ofstream file = std::ofstream(path);
    file << content;

    file.close();
}
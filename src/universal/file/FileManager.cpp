#include "FileManager.hpp"
#include <fstream>

FileManager::FileManager(std::string path) : path(path) {}

bool FileManager::exists() const {
    std::ifstream file = std::ifstream(path);

    bool res = file.good();
    file.close();

    return res;
}

std::string FileManager::read() const {
    if (!exists()) throw std::runtime_error("File '" + path + "' does not exist");

    std::ifstream file = std::ifstream(path);
    
    std::string res;
    std::string line;
    while (std::getline(file, line)) res += line + "\n";

    file.close();

    return res;
}

void FileManager::write(std::string content) const {
    std::ofstream file = std::ofstream(path);
    file << content;

    file.close();
}
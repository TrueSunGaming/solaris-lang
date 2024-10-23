#pragma once

#include <string>

class FileManager {
    protected:
        std::string path;
    public:
        FileManager(std::string path);
        ~FileManager() = default;

        std::string read() const;
        void write(std::string content) const;
};
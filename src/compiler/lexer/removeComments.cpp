#include "removeComments.hpp"

void removeLineComment(std::string& line) {
    size_t pos = line.find("//");
    if (pos == std::string::npos) return;

    line.erase(pos);
}

void removeComments(std::string& code) {

}

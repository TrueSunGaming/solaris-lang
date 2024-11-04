#include <regex>
#include <string>
#include "SubstringPosition.hpp"

void eraseRegex(std::string& str, const std::regex& regex, const std::vector<SubstringPosition>& exclude = {});
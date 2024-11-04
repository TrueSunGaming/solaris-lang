#pragma once

#include <string>
#include <regex>
#include <vector>
#include "SubstringPosition.hpp"

std::vector<SubstringPosition> findRegex(const std::string& str, const std::regex& regex, const std::vector<SubstringPosition>& exclude = {});
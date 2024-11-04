#pragma once

#include <regex>
#include <vector>
#include "SubstringPosition.hpp"

void excludeFromRegexMatch(SubstringPosition& match, std::vector<SubstringPosition>& matches, const std::vector<SubstringPosition>& exclude);
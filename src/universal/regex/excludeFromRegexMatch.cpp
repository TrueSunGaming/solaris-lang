#include "excludeFromRegexMatch.hpp"

void excludeFromRegexMatch(SubstringPosition& match, std::vector<SubstringPosition>& matches, const std::vector<SubstringPosition>& exclude) {
    for (auto& i : exclude) {
        std::optional<SubstringPosition> secondPart = match.exclude(i);
        if (secondPart) matches.push_back(*secondPart);
    }
}
#include "findRegex.hpp"
#include "excludeFromRegexMatch.hpp"

std::vector<SubstringPosition> findRegex(const std::string& str, const std::regex& regex, const std::vector<SubstringPosition>& exclude) {
    std::smatch match;
    size_t pos = 0;
    std::string substr = str;
    std::vector<SubstringPosition> res;

    while(pos < str.size() && std::regex_search(substr, match, regex)) {
        size_t matchPos = match.position() + pos;
        if (matchPos == std::string::npos) break;

        size_t matchLength = match.length();

        res.emplace_back(matchPos, matchLength);
        excludeFromRegexMatch(res[res.size() - 1], res, exclude);

        pos = matchPos + matchLength;
        substr = str.substr(pos);
    }
    
    return res;
}
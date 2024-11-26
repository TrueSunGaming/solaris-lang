#include "eraseRegex.hpp"
#include "findRegex.hpp"
#include "excludeFromRegexMatch.hpp"

void eraseRegex(std::string& str, const std::regex& regex, const std::vector<SubstringPosition>& exclude) {
    std::vector<SubstringPosition> matches = findRegex(str, regex, exclude);

    size_t offset = 0;
    for (auto& i : matches) {
        size_t erasePos = i.start - offset;

        str.erase(erasePos, i.length);
        offset += i.length;
    }
}
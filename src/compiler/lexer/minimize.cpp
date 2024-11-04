#include "minimize.hpp"
#include "../../universal/util/split.hpp"
#include "../../universal/util/trim.hpp"
#include "../../universal/util/filter.hpp"
#include "../../universal/regex/eraseRegex.hpp"
#include "../../universal/regex/findRegex.hpp"
#include "removeComments.hpp"
#include "TokenType.hpp"

std::string minimize(const std::string code) {
    std::vector<std::string> lines = split(code, "\n");

    for (auto &i : lines) {
        removeLineComment(i);
        trim(i);
    }

    std::vector<std::string> emptyFiltered = filter(lines, (std::function<bool(std::string)>)[](std::string v) {
        return v.size() > 0;
    });

    std::string res;
    for (auto i : emptyFiltered) res += i;

    eraseRegex(res, MULTILINE_COMMENT_REGEX, findRegex(res, STRING_REGEX));

    return res;
}
#include "minimize.hpp"
#include "../../universal/util/split.hpp"
#include "../../universal/util/trim.hpp"
#include "../../universal/util/filter.hpp"
#include "removeComments.hpp"
#include <vector>

using std::string;
using std::vector;
using std::function;

string minimize(const string code) {
    vector<string> lines = split(code, "\n");

    for (auto &i : lines) {
        removeLineComment(i);
        trim(i);
    }

    vector<string> emptyFiltered = filter(lines, (function<bool(string)>)[](string v) {
        return v.size() > 0;
    });

    string res;
    for (auto i : emptyFiltered) res += i;

    return res;
}
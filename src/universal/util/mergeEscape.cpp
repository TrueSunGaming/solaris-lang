#include "mergeEscape.hpp"
#include <regex>

std::string mergeEscape(const std::string& str) {
    std::string res;

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] != '\\') {
            res += str[i];
            continue;
        }
        
        std::string next3 = str.substr(i + 1, 3);
        bool octal = std::regex_match(next3, std::regex(R"(\d{3})"));
        bool hex = std::regex_match(next3, std::regex(R"(x[\da-fA-F]{2})"));

        if (octal || hex) {
            std::stringstream ss;
            if (octal) ss << std::oct;
            else ss << std::hex;

            ss << (octal ? next3 : str.substr(i + 2, 2));

            int dec;
            ss >> dec;

            res += (char)dec;
            i += 3;
            continue;
        }

        switch (str[i + 1]) {
            case 'a':
                res += '\a';
                break;
            
            case 'b':
                res += '\b';
                break;
            
            case 'f':
                res += '\f';
                break;
            
            case 'n':
                res += '\n';
                break;
            
            case 'r':
                res += '\r';
                break;
            
            case 't':
                res += '\t';
                break;
            
            case 'v':
                res += '\v';
                break;
            
            case '\\':
                res += '\\';
                break;
            
            case '\'':
                res += '\'';
                break;
            
            case '"':
                res += '"';
                break;
            
            case '?':
                res += '?';
                break;
            
            case '0':
                res += '\0';
                break;
            
            case 'e':
                res += '\e';
                break;
            
            default:
                continue;
        }

        i++;
    }

    return res;
}
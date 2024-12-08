#pragma once

#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2.h>
#include <string>

class PCRECode {
    private:
        pcre2_code *code;
        pcre2_match_data *matchData;

        static std::string getError(int errCode);
    
    public:
        PCRECode(const std::string& pattern);
        ~PCRECode();

        bool match(const std::string& str) const;
};
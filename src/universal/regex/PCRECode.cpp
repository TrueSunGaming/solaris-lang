#include "PCRECode.hpp"
#include <stdexcept>
#include <iostream>

std::string PCRECode::getError(int errCode) {
    PCRE2_UCHAR *errMsg = new PCRE2_UCHAR[128];
    pcre2_get_error_message(errCode, errMsg, 128);

    std::string msg;
    for (size_t i = 0; i < 128; i++) {
        if (errMsg[i] == 0) break;
        msg += errMsg[i];
    }

    delete[] errMsg;
    return msg;
}

PCRECode::PCRECode(const std::string& pattern) {
    int err;
    PCRE2_SIZE errOffset;

    code = pcre2_compile((PCRE2_SPTR)pattern.c_str(), PCRE2_ZERO_TERMINATED, 0, &err, &errOffset, NULL);
    if (err != 0) {
        std::string errMsg = getError(err);
        if (errMsg != "no error") throw std::runtime_error(std::string("Failed to compile regex: ") + errMsg);
    }

    err = pcre2_jit_compile(code, PCRE2_JIT_COMPLETE);
    if (err != 0) throw std::runtime_error(std::string("Failed to JIT compile regex: ") + getError(err));
    matchData = pcre2_match_data_create_from_pattern(code, NULL);
}

PCRECode::~PCRECode() {
    pcre2_code_free(code);
    pcre2_match_data_free(matchData);
}

bool PCRECode::match(const std::string& str) const {
    return pcre2_match(code, (PCRE2_SPTR)str.c_str(), str.size(), 0, 0, matchData, NULL) != PCRE2_ERROR_NOMATCH;
}
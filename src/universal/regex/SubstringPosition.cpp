#include "SubstringPosition.hpp"
#include <algorithm>

SubstringPosition::SubstringPosition() {}
SubstringPosition::SubstringPosition(size_t start, size_t length) : start(start), length(length) {}

size_t SubstringPosition::end() const {
    return start + length - 1;
}

bool SubstringPosition::overlaps(const SubstringPosition& other) const {
    if (length <= 0 || other.length <= 0) return false;
    return end() >= other.start && start <= other.end();
}

bool SubstringPosition::encapsulates(const SubstringPosition& other) const {
    if (length <= 0 || other.length <= 0) return false;
    return other.start >= start && other.end() <= end();
}

void SubstringPosition::moveEndTo(size_t pos) {
    length = pos - start + 1;
}

void SubstringPosition::moveStartTo(size_t pos) {
    size_t oldEnd = end();
    start = pos;
    moveEndTo(oldEnd);
}

std::optional<SubstringPosition> SubstringPosition::exclude(const SubstringPosition& other) {
    if (!overlaps(other)) return std::nullopt;

    if (other.encapsulates(*this)) {
        length = 0;
        return std::nullopt;
    }

    if (other.start >= start && other.end() >= end()) {
        moveEndTo(other.start);
        return std::nullopt;
    }

    if (other.start <= start && other.end() <= end()) {
        moveStartTo(other.end() + 1);
        return std::nullopt;
    }

    if (encapsulates(other)) {
        SubstringPosition res = SubstringPosition(
            other.end() + 1,
            length - other.end()
        );
        
        moveEndTo(other.start - 1);
        return res;
    }

    return std::nullopt;
}

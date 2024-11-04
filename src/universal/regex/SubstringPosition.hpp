#pragma once

#include <cstddef>
#include <array>
#include <optional>

class SubstringPosition {
    public:
        size_t start;
        size_t length;

        SubstringPosition();
        SubstringPosition(size_t start, size_t length);

        size_t end() const;
        bool overlaps(const SubstringPosition& other) const;
        bool encapsulates(const SubstringPosition& other) const;
        void moveEndTo(size_t pos);
        void moveStartTo(size_t pos);
        std::optional<SubstringPosition> exclude(const SubstringPosition& other);
};
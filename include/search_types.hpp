#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct SearchResult {
    std::vector<std::string> matches;

    std::size_t size() const noexcept {
        return matches.size();
    }

    bool empty() const noexcept {
        return matches.empty();
    }
};

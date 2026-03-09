#include "search_data.hpp"
#include "metrics.hpp"

#include <algorithm>
#include <array>

namespace {
constexpr std::size_t kAsciiSize = 256;

std::array<int, kAsciiSize> preprocessBadCharacter(const std::string& pattern) {
    std::array<int, kAsciiSize> badChar{};
    badChar.fill(-1);
    metrics::usedOperationsAlgorithm2 += kAsciiSize;

    for (std::size_t i = 0; i < pattern.size(); ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = static_cast<int>(i);
        metrics::usedOperationsAlgorithm2++;
    }

    return badChar;
}

bool boyerMooreContains(const std::string& text, const std::string& pattern) {
    const int textSize = static_cast<int>(text.size());
    const int patternSize = static_cast<int>(pattern.size());

    if (patternSize == 0 || textSize == 0 || textSize < patternSize) {
        return false;
    }

    const auto badChar = preprocessBadCharacter(pattern);
    int shift = 0;

    while (shift <= textSize - patternSize) {
        int j = patternSize - 1;

        while (j >= 0 && text[shift + j] == pattern[j]) {
            --j;
            metrics::usedOperationsAlgorithm2++;
        }

        if (j < 0) {
            metrics::usedOperationsAlgorithm2++;
            return true;
        }

        const int badCharShift = badChar[static_cast<unsigned char>(text[shift + j])];
        shift += std::max(1, j - badCharShift);
        metrics::usedOperationsAlgorithm2++;
    }

    return false;
}
} // namespace

SearchResult SearchBenchmarkData::checkSubwordsBoyerMoore() const {
    metrics::usedOperationsAlgorithm2 = 0;

    SearchResult result;
    const auto& text = getWord();
    const auto& patterns = getSubwords();

    if (patterns.empty() || text.empty()) {
        return result;
    }

    for (const auto& pattern : patterns) {
        if (pattern.empty()) {
            continue;
        }

        if (boyerMooreContains(text, pattern)) {
            result.matches.push_back(pattern);
        }
    }

    return result;
}

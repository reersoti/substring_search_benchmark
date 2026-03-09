#include "search_data.hpp"
#include "metrics.hpp"

SearchResult SearchBenchmarkData::checkSubwordsNaive() const {
    metrics::usedOperationsAlgorithm1 = 0;

    SearchResult result;
    const auto& text = getWord();
    const auto& patterns = getSubwords();

    for (const auto& pattern : patterns) {
        metrics::usedOperationsAlgorithm1++;

        if (pattern.empty() || pattern.size() > text.size()) {
            continue;
        }

        for (std::size_t start = 0; start + pattern.size() <= text.size(); ++start) {
            metrics::usedOperationsAlgorithm1++;

            if (text[start] != pattern[0]) {
                continue;
            }

            bool matched = true;
            for (std::size_t offset = 1; offset < pattern.size(); ++offset) {
                metrics::usedOperationsAlgorithm1++;
                if (text[start + offset] != pattern[offset]) {
                    matched = false;
                    break;
                }
            }

            if (matched) {
                result.matches.push_back(pattern);
                break;
            }
        }
    }

    return result;
}

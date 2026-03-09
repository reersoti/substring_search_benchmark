#pragma once

#include "search_data.hpp"

#include <string>

class TestRunner {
public:
    void generateWords(std::size_t alphabetSize, std::size_t wordSize) const;
    void runAlphabetBenchmark(
        const std::string& inputFilename,
        const std::string& outputFilename1,
        const std::string& outputFilename2,
        std::size_t alphabetSize
    ) const;
    void runLengthBenchmark(
        const std::string& inputFilename,
        const std::string& outputFilename1,
        const std::string& outputFilename2,
        std::size_t wordSize
    ) const;
    bool validate(const SearchData& data, const SearchResult& result) const;
};

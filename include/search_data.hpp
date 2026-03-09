#pragma once

#include "search_types.hpp"

#include <string>
#include <vector>

class SearchData {
public:
    explicit SearchData(const std::string& filename);
    virtual ~SearchData() = default;

    const std::string& getWord() const noexcept;
    const std::vector<std::string>& getSubwords() const noexcept;
    std::size_t getAmount() const noexcept;

    void print() const;
    void writeFile(const std::string& filename, const SearchResult& results) const;
    SearchResult checkWithStdFind() const;

    virtual SearchResult checkSubwordsNaive() const = 0;
    virtual SearchResult checkSubwordsBoyerMoore() const = 0;

    void saveToCsvByAlphabet(std::size_t alphabetSize) const;
    void saveToCsvByWordSize(std::size_t wordSize) const;

private:
    std::string word_;
    std::vector<std::string> subwords_;
};

class SearchBenchmarkData final : public SearchData {
public:
    using SearchData::SearchData;

    SearchResult checkSubwordsNaive() const override;
    SearchResult checkSubwordsBoyerMoore() const override;
};

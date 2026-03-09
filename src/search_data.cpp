#include "search_data.hpp"
#include "metrics.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

SearchData::SearchData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::size_t count = 0;
    file >> count;
    file.ignore();
    std::getline(file, word_);

    subwords_.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        std::string value;
        std::getline(file, value);
        subwords_.push_back(std::move(value));
    }
}

const std::string& SearchData::getWord() const noexcept {
    return word_;
}

const std::vector<std::string>& SearchData::getSubwords() const noexcept {
    return subwords_;
}

std::size_t SearchData::getAmount() const noexcept {
    return subwords_.size();
}

void SearchData::print() const {
    std::cout << "Word: " << word_ << '\n';
    for (std::size_t i = 0; i < subwords_.size(); ++i) {
        std::cout << "Subword #" << i + 1 << ": " << subwords_[i] << '\n';
    }
}

void SearchData::writeFile(const std::string& filename, const SearchResult& results) const {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }

    if (results.empty()) {
        file << "nothing\n";
        return;
    }

    for (const auto& match : results.matches) {
        file << match << '\n';
    }
}

SearchResult SearchData::checkWithStdFind() const {
    SearchResult result;
    for (const auto& subword : subwords_) {
        if (word_.find(subword) != std::string::npos) {
            result.matches.push_back(subword);
        }
    }
    return result;
}

void SearchData::saveToCsvByAlphabet(std::size_t alphabetSize) const {
    std::ofstream outFile("out1.csv", std::ios::app);
    if (!outFile.is_open()) {
        throw std::runtime_error("Не удалось открыть out1.csv");
    }

    outFile << alphabetSize << ','
            << metrics::usedOperationsAlgorithm1 << ','
            << metrics::usedOperationsAlgorithm2 << ','
            << metrics::usedTimeAlgorithm1 << ','
            << metrics::usedTimeAlgorithm2 << '\n';
}

void SearchData::saveToCsvByWordSize(std::size_t wordSize) const {
    std::ofstream outFile("out2.csv", std::ios::app);
    if (!outFile.is_open()) {
        throw std::runtime_error("Не удалось открыть out2.csv");
    }

    outFile << wordSize << ','
            << metrics::usedOperationsAlgorithm1 << ','
            << metrics::usedOperationsAlgorithm2 << ','
            << metrics::usedTimeAlgorithm1 << ','
            << metrics::usedTimeAlgorithm2 << '\n';
}

#include "test_runner.hpp"
#include "metrics.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

namespace {
constexpr int kMaxSubwords = 500;
const std::string kFullAlphabet =
    "abcdefghijklmnopqrstuvwxyz1234567890"
    "йцукенгшщзхъёфывапролджэячсмитьбю/!№%:,.;()_+-=@#$%^&*{}";

std::string generateRandomString(std::size_t length, const std::string& alphabet, std::mt19937& generator) {
    std::uniform_int_distribution<std::size_t> dist(0, alphabet.size() - 1);
    std::string result;
    result.reserve(length);

    for (std::size_t i = 0; i < length; ++i) {
        result.push_back(alphabet[dist(generator)]);
    }

    return result;
}

void insertSubwords(std::string& word, const std::vector<std::string>& subwords, std::mt19937& generator) {
    if (word.empty() || subwords.empty()) {
        return;
    }

    std::uniform_int_distribution<int> countDist(10, 30);
    const std::size_t insertCount = std::min<std::size_t>(countDist(generator), subwords.size());

    std::ofstream file("guaranted.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать guaranted.txt");
    }
    file << insertCount << '\n';

    for (std::size_t i = 0; i < insertCount; ++i) {
        const auto& subword = subwords[i];
        if (subword.empty() || subword.size() > word.size()) {
            continue;
        }

        std::uniform_int_distribution<std::size_t> posDist(0, word.size() - subword.size());
        const std::size_t pos = posDist(generator);
        word.replace(pos, subword.size(), subword);
        file << subword << '\n';
    }
}
} // namespace

void TestRunner::generateWords(std::size_t alphabetSize, std::size_t wordSize) const {
    if (alphabetSize == 0 || alphabetSize > kFullAlphabet.size()) {
        throw std::invalid_argument("Некорректный размер алфавита");
    }
    if (wordSize == 0) {
        throw std::invalid_argument("Размер слова должен быть больше 0");
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    const std::size_t maxSubwordLength = std::max<std::size_t>(1, wordSize / 10);
    const std::string alphabet = kFullAlphabet.substr(0, alphabetSize);

    std::string mainWord = generateRandomString(wordSize, alphabet, generator);

    std::uniform_int_distribution<std::size_t> lengthDist(1, maxSubwordLength);
    std::vector<std::string> subwords;
    subwords.reserve(kMaxSubwords);

    for (int i = 0; i < kMaxSubwords; ++i) {
        subwords.push_back(generateRandomString(lengthDist(generator), alphabet, generator));
    }

    insertSubwords(mainWord, subwords, generator);

    std::ofstream file("data/stdIn.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать data/stdIn.txt");
    }

    file << kMaxSubwords << '\n';
    file << mainWord << '\n';
    for (const auto& subword : subwords) {
        file << subword << '\n';
    }
}

void TestRunner::runAlphabetBenchmark(
    const std::string& inputFilename,
    const std::string& outputFilename1,
    const std::string& outputFilename2,
    std::size_t alphabetSize
) const {
    SearchBenchmarkData data(inputFilename);

    const SearchResult validation = data.checkWithStdFind();
    data.writeFile("validation.txt", validation);

    const auto start1 = std::chrono::high_resolution_clock::now();
    const SearchResult result1 = data.checkSubwordsNaive();
    const auto stop1 = std::chrono::high_resolution_clock::now();
    metrics::usedTimeAlgorithm1 = std::chrono::duration_cast<std::chrono::duration<double>>(stop1 - start1).count();

    if (validate(data, result1)) {
        data.writeFile(outputFilename1, result1);
        std::cout << "Первый алгоритм валидный\n";
    }

    const auto start2 = std::chrono::high_resolution_clock::now();
    const SearchResult result2 = data.checkSubwordsBoyerMoore();
    const auto stop2 = std::chrono::high_resolution_clock::now();
    metrics::usedTimeAlgorithm2 = std::chrono::duration_cast<std::chrono::duration<double>>(stop2 - start2).count();

    if (validate(data, result2)) {
        data.writeFile(outputFilename2, result2);
        std::cout << "Второй алгоритм валидный\n";
    }

    data.saveToCsvByAlphabet(alphabetSize);
}

void TestRunner::runLengthBenchmark(
    const std::string& inputFilename,
    const std::string& outputFilename1,
    const std::string& outputFilename2,
    std::size_t wordSize
) const {
    SearchBenchmarkData data(inputFilename);

    const auto start1 = std::chrono::high_resolution_clock::now();
    const SearchResult result1 = data.checkSubwordsNaive();
    const auto stop1 = std::chrono::high_resolution_clock::now();
    metrics::usedTimeAlgorithm1 = std::chrono::duration_cast<std::chrono::duration<double>>(stop1 - start1).count();

    if (validate(data, result1)) {
        data.writeFile(outputFilename1, result1);
        std::cout << "Первый алгоритм валидный\n";
    }

    const auto start2 = std::chrono::high_resolution_clock::now();
    const SearchResult result2 = data.checkSubwordsBoyerMoore();
    const auto stop2 = std::chrono::high_resolution_clock::now();
    metrics::usedTimeAlgorithm2 = std::chrono::duration_cast<std::chrono::duration<double>>(stop2 - start2).count();

    if (validate(data, result2)) {
        data.writeFile(outputFilename2, result2);
        std::cout << "Второй алгоритм валидный\n";
    }

    const SearchResult validation = data.checkWithStdFind();
    data.writeFile("validation.txt", validation);
    data.saveToCsvByWordSize(wordSize);
}

bool TestRunner::validate(const SearchData& data, const SearchResult& result) const {
    const SearchResult expected = data.checkWithStdFind();

    if (expected.size() != result.size()) {
        std::cout << "Размеры результатов не совпадают!\n";
        return false;
    }

    for (std::size_t i = 0; i < expected.size(); ++i) {
        if (expected.matches[i] != result.matches[i]) {
            std::cout << "Результаты не совпадают!\n";
            return false;
        }
    }

    std::cout << "Результаты совпадают!\n";
    return true;
}

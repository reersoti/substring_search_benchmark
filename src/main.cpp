#include "metrics.hpp"
#include "test_runner.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
    TestRunner runner;
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz1234567890";

    {
        std::ofstream outFile1("out1.csv", std::ios::out);
        if (!outFile1.is_open()) {
            std::cerr << "Не удалось создать out1.csv\n";
            return 1;
        }
        outFile1 << "Alphabet Size,Used Operations Algorithm 1,Used Operations Algorithm 2,"
                    "Used Time Algorithm 1,Used Time Algorithm 2\n";
    }

    {
        std::ofstream outFile2("out2.csv", std::ios::out);
        if (!outFile2.is_open()) {
            std::cerr << "Не удалось создать out2.csv\n";
            return 1;
        }
        outFile2 << "Word Size,Used Operations Algorithm 1,Used Operations Algorithm 2,"
                    "Used Time Algorithm 1,Used Time Algorithm 2\n";
    }

    for (std::size_t i = 1; i < alphabet.size() - 15; ++i) {
        metrics::alphabetSize = i + 1;
        for (std::size_t j = 0; j < 5; ++j) {
            runner.generateWords(metrics::alphabetSize, 3000);
            runner.runAlphabetBenchmark(
                "data/stdIn.txt",
                "algoritm.txt",
                "algoritm2.txt",
                metrics::alphabetSize
            );
        }
    }

    return 0;
}

#include "console.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <vector>

void Console::input() const {
    std::size_t amount = 0;
    std::string word;

    while (true) {
        std::cout << "Введите количество подслов: ";
        std::cin >> amount;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода: нужно число.\n";
            continue;
        }

        std::cout << "Введите исходное слово: ";
        std::cin >> word;
        break;
    }

    std::vector<std::string> subwords(amount);
    for (std::size_t i = 0; i < amount; ++i) {
        std::cout << "Введите подслово #" << (i + 1) << ": ";
        std::cin >> subwords[i];
    }

    std::ofstream file("data/in.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать data/in.txt");
    }

    file << amount << '\n' << word << '\n';
    for (const auto& subword : subwords) {
        file << subword << '\n';
    }
}

std::string Console::readFile() const {
    std::string filename;
    while (true) {
        std::cout << "Введите путь к файлу: ";
        std::cin >> filename;

        std::ifstream file(filename);
        if (file.is_open()) {
            return filename;
        }

        std::cout << "Файл не найден, попробуйте ещё раз.\n";
    }
}

void Console::start(TestRunner& runner) {
    while (true) {
        int mode = 0;
        std::cout << "Выберите режим работы:\n"
                  << "0) Пользовательский тест\n"
                  << "1) Стандартный тест\n"
                  << "2) Случайный тест\n"
                  << "10) Выход\n";
        std::cin >> mode;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода: нужно число.\n";
            continue;
        }

        if (mode == 0) {
            int source = 0;
            std::cout << "0) Ввести вручную\n1) Прочитать из файла\n10) Назад\n";
            std::cin >> source;
            if (source == 0) {
                input();
                runner.runAlphabetBenchmark("data/in.txt", "out.txt", "out3.txt", 0);
            } else if (source == 1) {
                runner.runAlphabetBenchmark(readFile(), "out.txt", "out3.txt", 0);
            } else if (source != 10) {
                std::cout << "Недоступный пункт меню.\n";
            }
        } else if (mode == 1) {
            runner.runAlphabetBenchmark("data/stdIn.txt", "out.txt", "out3.txt", 0);
        } else if (mode == 2) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<std::size_t> wordSizeDist(100, 10000);
            std::uniform_int_distribution<std::size_t> alphabetSizeDist(2, 100);

            runner.generateWords(alphabetSizeDist(gen), wordSizeDist(gen));
            runner.runAlphabetBenchmark("data/stdIn.txt", "out.txt", "out3.txt", 0);
        } else if (mode == 10) {
            break;
        } else {
            std::cout << "Недоступный пункт меню.\n";
        }
    }
}

#pragma once

#include "test_runner.hpp"

#include <string>

class Console {
public:
    void start(TestRunner& runner);

private:
    void input() const;
    std::string readFile() const;
};

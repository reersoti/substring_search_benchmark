# Substring Search Benchmark

A small C++ project for comparing substring search algorithms on generated test data.

## Overview

This project benchmarks two approaches for substring search:

- Naive search
- Boyer–Moore (bad character heuristic)

The program can generate datasets, run both algorithms on the same input, save the results, and visualize execution time with plots.

## Features

- comparison of two substring search algorithms
- random test data generation
- CSV export for benchmark results
- execution time measurement
- result visualization with Python scripts

## Algorithms

### Naive Search
Checks each possible position in the text and compares characters one by one.

### Boyer–Moore (Bad Character Heuristic)
Uses preprocessing of the pattern to skip unnecessary comparisons and improve performance on larger inputs.

## Project Structure

```text
.
├── include/        # headers
├── src/            # C++ source files
├── data/           # input/output benchmark data
├── scripts/        # plotting utilities
├── CMakeLists.txt
└── README.md
Build
cmake -S . -B build
cmake --build build
Run
./build/substring_search_benchmark
Output

The program generates benchmark results that can be exported to CSV and then plotted using Python scripts.

Visualization

Example plotting script:

python scripts/plot.py
Why this project matters

This project demonstrates:

implementation of classical string-search algorithms

performance measurement in C++

working with generated datasets

basic benchmark automation and result analysis

Possible Improvements

add Knuth–Morris–Pratt

add full Boyer–Moore implementation

support larger benchmark suites

add unit tests

improve CLI options

Tech Stack

C++

CMake

Python (for plotting)

Author

Student project focused on algorithm analysis and benchmarking.

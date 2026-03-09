# Substring Search Benchmark

A small C++ project for comparing substring search algorithms on generated test data.

## Overview

This project benchmarks two approaches for substring search:

- **Naive search** — basic character-by-character comparison
- **Boyer–Moore** (bad character heuristic) — optimized with pattern preprocessing

The program can generate datasets, run both algorithms on the same input, save the results, and visualize execution time with plots.

## Features

- 🔍 Comparison of two substring search algorithms
- 🎲 Random test data generation
- 📊 CSV export for benchmark results
- ⏱️ Execution time measurement
- 📈 Result visualization with Python scripts

## Algorithms

### Naive Search
Checks each possible position in the text and compares characters one by one. Simple but inefficient for large inputs.

### Boyer–Moore (Bad Character Heuristic)
Uses preprocessing of the pattern to skip unnecessary comparisons and improve performance on larger inputs.

## Project Structure

```
.
├── include/        # Header files
├── src/            # C++ source files
├── data/           # Input/output benchmark data
├── scripts/        # Plotting utilities
├── CMakeLists.txt  # Build configuration
└── README.md       # This file
```

## Building and Running

### Build
```bash
cmake -S . -B build
cmake --build build
```

### Run
```bash
./build/substring_search_benchmark
```

### Output
The program generates benchmark results that can be exported to CSV and then plotted using Python scripts.

## Visualization

Plot the results using the provided Python script:

```bash
python scripts/plot.py
```

## Why This Project Matters

This project demonstrates:

- Implementation of classical string-search algorithms
- Performance measurement techniques in C++
- Working with generated datasets
- Basic benchmark automation and result analysis

## Possible Improvements

- [ ] Add Knuth–Morris–Pratt algorithm
- [ ] Add full Boyer–Moore implementation
- [ ] Support larger benchmark suites
- [ ] Add unit tests
- [ ] Improve CLI options

## Tech Stack

- **C++** — Core implementation
- **CMake** — Build system
- **Python** — Data visualization

## Author

Student project focused on algorithm analysis and benchmarking.
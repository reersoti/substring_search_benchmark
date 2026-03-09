# Substring Search Benchmark

A C++ project for benchmarking classical substring search algorithms on generated test data.

## Overview

This project compares two approaches to substring search:

- Naive search
- Boyer–Moore (bad character heuristic)

The repository was created to study how different string matching strategies behave in practice, especially as the size of the input data grows. The program can generate datasets, run both algorithms on the same input, collect performance metrics, and visualize the results.

The project is focused on algorithm analysis, benchmarking, and performance comparison rather than on building a production-ready library.

## Features

- implementation of substring search algorithms in C++
- comparison of naive search and Boyer–Moore
- generated benchmark datasets
- execution time measurement
- CSV export for results
- visualization of benchmark output with Python scripts

## Algorithms

### Naive Search

The naive algorithm checks every possible position in the source string and compares the pattern character by character.  
It is simple to implement, but its efficiency decreases significantly on large inputs.

### Boyer–Moore (Bad Character Heuristic)

This implementation uses the bad character rule to skip unnecessary comparisons.  
In many practical cases, it performs much faster than naive search, especially on longer texts and patterns.

## Project Structure

```text
.
├── include/        # header files
├── src/            # source files
├── data/           # benchmark input/output data
├── scripts/        # plotting utilities
├── CMakeLists.txt
└── README.md
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/substring_search_benchmark
```

## Visualization

If benchmark results are exported to CSV, they can be visualized with a Python plotting script:

```bash
python scripts/plot.py
```

## Example Use Case

This project can be used to:

- compare classical substring search algorithms
- demonstrate why heuristic-based approaches matter
- generate performance plots for coursework or algorithm analysis
- study the effect of input size on execution time

## What This Project Demonstrates

- implementation of classical algorithms in C++
- practical benchmarking
- work with generated datasets
- collection and analysis of experimental results
- basic automation of research-style experiments

## Possible Improvements

- add Knuth–Morris–Pratt (KMP)
- add more complete Boyer–Moore heuristics
- support command-line configuration
- improve dataset generation options
- add unit tests and reproducible benchmark scenarios

## Tech Stack

- C++
- CMake
- Python (for plotting and visualization)

## Notes

This repository is intended as an educational and experimental project focused on algorithm comparison and performance measurement.

# Benchmark Results

This document is intended to store reproducible benchmark results for substring search algorithms.

## Algorithms Compared

- Naive substring search
- Boyer-Moore search with bad character heuristic

## Example Results Table

| Dataset Size | Pattern Length | Naive Time | Boyer-Moore Time | Faster Algorithm |
|---:|---:|---:|---:|---|
| 10,000 | 5 | to be measured | to be measured | to be measured |
| 100,000 | 10 | to be measured | to be measured | to be measured |
| 1,000,000 | 20 | to be measured | to be measured | to be measured |

## Recommended Benchmark Procedure

1. Build the project in release mode.
2. Run the benchmark executable.
3. Export the result data to CSV if supported by the current implementation.
4. Generate a chart with the plotting script.
5. Add the result table and chart to this document or to the main README.

## Release Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/substring_search_benchmark
```

## Notes

Benchmark results should be measured on the same machine with the same compiler settings to keep comparisons meaningful.

cmake_minimum_required(VERSION 3.16)
project(substring_search_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(substring_search_benchmark
    src/main.cpp
    src/console.cpp
    src/search_data.cpp
    src/naive_search.cpp
    src/boyer_moore_search.cpp
    src/test_runner.cpp
)

target_include_directories(substring_search_benchmark PRIVATE include)

if (MSVC)
    target_compile_options(substring_search_benchmark PRIVATE /W4)
else()
    target_compile_options(substring_search_benchmark PRIVATE -Wall -Wextra -Wpedantic)
endif()

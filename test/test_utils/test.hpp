#pragma once

#include <iostream>

void print_test_header(std::string name);
int summarize_tests();

void prepare_test(std::string name);
void handle_test_result(bool success);

template <typename T>
inline void printSuccess(std::string name, bool (*test_func)(T), T arg) {
    prepare_test(name);
    const bool success = test_func(arg);
    handle_test_result(success);
}

template <typename T, typename U>
bool iterableEqual(T starta, T enda, U startb, U endb) {
    if (std::distance(starta, enda) != std::distance(startb, endb)) {
        return false;
    }
    for (; starta != enda; starta++) {
        if (*starta != *startb) {
            return false;
        }
        startb++;
    }
    return true;
}
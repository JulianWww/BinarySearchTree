#include "test.hpp"

int successful_tests = 0;
int run_tests = 0;

void prepare_test(std::string name){
    run_tests++;
    std::cout << "- " << name;
    for (int i=name.size(); i<50; i++) {
        std::cout << " ";
    }
}

void handle_test_result(bool success){
    if (success) {
        std::cout << "\033[1;32mSuccess\033[0m";
        successful_tests++;
    }
    else {
        std::cout << "\033[1;31mFailed\033[0m";
    }
    std::cout << std::endl;
}

void print_test_header(std::string name) {
    std::cout << std::endl << std::endl << "Testing \033[1;94m" << name << "\033[1;0m" << std::endl;
    std::cout << "test name                                           Status" << std::endl;
}

int summarize_tests() {
    std::cout << std::endl;
    printf("ran %i test\n", run_tests);
    printf("%i Successes\n", successful_tests),
    printf("%i fails\n", run_tests - successful_tests);
    return run_tests - successful_tests;
}
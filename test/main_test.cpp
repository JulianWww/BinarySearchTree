#include <iostream>
#include "test_utils/test.hpp"
#include "run_test.hpp"

int main(){
    test_linked_tree();
    test_linked_tree_released();
    
    return summarize_tests();
}

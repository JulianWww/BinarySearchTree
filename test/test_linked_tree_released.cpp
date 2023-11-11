#include "run_test.hpp"
#include "test_utils/test.hpp"
#include <bst.h>

bool test_tree(char) {
    BST::LinkedTreeReleased<int> tree;
    tree.insert("a", 8, 6);
    tree.insert("a", 5, 6);
    tree.insert("z", 8, 6);
    tree.insert("g", 8, 6);
    tree.remove("a", 5);
//    tree.print();
    return *tree.get("a", 8) == 6;
}

void test_linked_tree_released() {
    print_test_header("Linked Tree Released");
    printSuccess<char>("run Test", &test_tree, 'd');
}
# BinarySearchTree
A header only library that contains binary search trees.

## Import
You can import and link it to your project using cmake as follows:
```
add_subdirectory(BinarySearchTree)
arget_link_libraries(<project name> binary-search-tree)
```

## Contents
Every tree has an ```insert```, ```get``` and ```remove```. What they do is fairly self explenatory, insert inserts an element into the key, get gets an element form the tree and remove removes a certain element from a tree. The keys within the tree a binary char arrays, a lenght must always be specified in bits.

### Linked Tree
The linked tree stores the data in a linked tree

### Linked Tree Released
The same as the linked tree but it does not delete object upon deletion.

## Todo
[ ] Make the released tree not be a copy of the linked tree with a couple of modifications
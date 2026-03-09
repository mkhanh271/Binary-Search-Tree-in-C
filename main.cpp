#include <iostream>
#include "BinarySearchTree.h"

int main() {
    // Create a Binary Search Tree for integers
    BinarySearchTree<int> intTree([](const int& a, const int& b) { return a < b; });

    // Add elements to the integer tree
    intTree.add(5);
    intTree.add(3);
    intTree.add(7);
    intTree.add(2);
    intTree.add(4);
    intTree.add(6);
    intTree.add(8);

    // Perform in-order traversal
    std::cout << "In-order traversal of integer tree: ";
    intTree.inOrderTraversal();

    // Search for an element
    int searchValue = 4;
    if (intTree.search(searchValue)) {
        std::cout << searchValue << " found in the tree." << std::endl;
    } else {
        std::cout << searchValue << " not found in the tree." << std::endl;
    }

    // Delete an element
    intTree.remove(3);
    std::cout << "In-order traversal after deleting 3: ";
    intTree.inOrderTraversal();

    // Create a Binary Search Tree for strings
    BinarySearchTree<std::string> stringTree([](const std::string& a, const std::string& b) { return a < b; });

    // Add elements to the string tree
    stringTree.add("apple");
    stringTree.add("banana");
    stringTree.add("cherry");
    stringTree.add("date");

    // Perform in-order traversal
    std::cout << "In-order traversal of string tree: ";
    stringTree.inOrderTraversal();

    return 0;
}
#include "BinarySearchTree.h"
#include <iostream>

template <typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T, typename Comparator>
class BinarySearchTree {
private:
    BinaryTreeNode<T>* root;
    Comparator comp;

    void add(BinaryTreeNode<T>*& node, const T& value) {
        if (!node) {
            node = new BinaryTreeNode<T>(value);
        } else if (comp(value, node->data)) {
            add(node->left, value);
        } else {
            add(node->right, value);
        }
    }

    void inOrder(BinaryTreeNode<T>* node) const {
        if (node) {
            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }
    }

public:
    BinarySearchTree(Comparator cmp) : root(nullptr), comp(cmp) {}

    void add(const T& value) {
        add(root, value);
    }

    void inOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }

    // Additional methods for delete and search can be implemented similarly
};

// Example usage
int main() {
    auto intComparator = [](const int& a, const int& b) { return a < b; };
    BinarySearchTree<int, decltype(intComparator)> intTree(intComparator);
    
    intTree.add(5);
    intTree.add(3);
    intTree.add(7);
    
    std::cout << "In-order traversal of integer BST: ";
    intTree.inOrder();

    return 0;
}
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <functional>

template <typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
private:
    BinaryTreeNode<T>* root;
    std::function<bool(const T&, const T&)> comparator;

    void addNode(BinaryTreeNode<T>*& node, const T& value);
    void inOrderTraversal(BinaryTreeNode<T>* node);
    BinaryTreeNode<T>* searchNode(BinaryTreeNode<T>* node, const T& value);
    BinaryTreeNode<T>* deleteNode(BinaryTreeNode<T>* node, const T& value);
    BinaryTreeNode<T>* findMin(BinaryTreeNode<T>* node);

public:
    BinarySearchTree(std::function<bool(const T&, const T&)> comp);
    ~BinarySearchTree();

    void add(const T& value);
    void inOrder();
    BinaryTreeNode<T>* search(const T& value);
    void remove(const T& value);
};

#endif // BINARYSEARCHTREE_H
#include <iostream>
#include <functional>
#include <string>
#include <stack>
#include <vector>

using namespace std;

template <typename T>
class BinaryTreeNode {
public:
    T value;
    BinaryTreeNode* leftChild = nullptr;
    BinaryTreeNode* rightChild = nullptr;

    BinaryTreeNode(T _value) : value(_value) {}

    void printTree() const {
        cout << value << endl; 
        printTreeChildren();
    }

private:
    void printTreeChildren(string prefix = "") const {
        if (leftChild) {
            cout << prefix << (rightChild ? "├─" : "└─") << leftChild->value << endl;
            leftChild->printTreeChildren(prefix + (rightChild ? "│ " : "  "));
        }

        if (rightChild) {
            cout << prefix << "└─" << rightChild->value << endl;
            rightChild->printTreeChildren(prefix + "  ");
        }
    }
};

template <typename T>
class BinarySearchTree {
private:
    BinaryTreeNode<T>* root = nullptr;
    function<bool(const T&, const T&)> compare;  // Store comparator

public:
    // Constructor with a default comparator
    BinarySearchTree(function<bool(const T&, const T&)> comp = less<T>())
        : compare(comp) {}

    ~BinarySearchTree() {
        clearTree();
    }

    void clearTree() {
        if (!root) return;
        stack<BinaryTreeNode<T>*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            BinaryTreeNode<T>* node = nodes.top();
            nodes.pop();
            if (node->leftChild) nodes.push(node->leftChild);
            if (node->rightChild) nodes.push(node->rightChild);
            delete node;
        }
        root = nullptr;
    }

    // Add a value
    void add(const T& value) {
        BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(value);
        if (!root) {
            root = newNode;
            return;
        }

        BinaryTreeNode<T>* current = root;
        while (true) {
            if (compare(value, current->value)) {
                if (!current->leftChild) {
                    current->leftChild = newNode;
                    break;
                }
                current = current->leftChild;
            } else {
                if (!current->rightChild) {
                    current->rightChild = newNode;
                    break;
                }
                current = current->rightChild;
            }
        }
    }

    // In-order traversal
    void inorder() const {
        if (!root) {
            cout << "The tree is empty." << endl;
            return;
        }

        std::stack<BinaryTreeNode<T>*> stack;
        BinaryTreeNode<T>* current = root;

        while (!stack.empty() || current) {
            while (current) {
                stack.push(current);
                current = current->leftChild;
            }
            current = stack.top();
            stack.pop();
            cout << current->value << " ";
            current = current->rightChild;
        }
        cout << endl;
    }

    // Searching and show location
    vector<int> search(const T& value) const {
        vector<int> indices;
        BinaryTreeNode<T>* current = root;
        int index = 1; // Root index is 1
        stack<pair<BinaryTreeNode<T>*, int>> stack;

        if (current) stack.push({current, index});

        while (!stack.empty()) {
            auto [node, idx] = stack.top();
            stack.pop();

            if (node->value == value) {
                indices.push_back(idx);
            }

            if (node->rightChild) {
                stack.push({node->rightChild, 2 * idx + 1});
            }

            if (node->leftChild) {
                stack.push({node->leftChild, 2 * idx});
            }
        }

        return indices;
    }

    // Delete a value
    void deleteValue(const T& value) {
        while (true) {
            BinaryTreeNode<T>* current = root;
            BinaryTreeNode<T>* parent = nullptr;

            while (current && current->value != value) {
                parent = current;
                if (compare(value, current->value)) {
                    current = current->leftChild;
                } else {
                    current = current->rightChild;
                }
            }

            if (!current) break; // Value not found

            // Case 1: Node with only one child or no child
            if (!current->leftChild || !current->rightChild) {
                BinaryTreeNode<T>* child = current->leftChild ? current->leftChild : current->rightChild;

                if (!parent) {
                    root = child;
                } else if (parent->leftChild == current) {
                    parent->leftChild = child;
                } else {
                    parent->rightChild = child;
                }

                delete current;
            } else {
                // Case 2: Node with two children
                BinaryTreeNode<T>* successorParent = current;
                BinaryTreeNode<T>* successor = current->rightChild;

                while (successor->leftChild) {
                    successorParent = successor;
                    successor = successor->leftChild;
                }

                current->value = successor->value;

                if (successorParent->leftChild == successor) {
                    successorParent->leftChild = successor->rightChild;
                } else {
                    successorParent->rightChild = successor->rightChild;
                }

                delete successor;
            }
        }
    }

    void printTree() const {
        if (root) {
            root->printTree();
        } else {
            cout << "The tree is empty." << endl;
        }
    }
};

int main() {
    BinarySearchTree<int> intTree;
    BinarySearchTree<string> stringTree;

    string mode;
    cout << "=== Interactive Binary Search Tree Program ===\n";

    while (true) {
        cout << "\nChoose input mode ('int', 'string', or 'quit'): ";
        getline(cin, mode);

        if (mode == "quit") break;

        if (mode == "int") {
            cout << "\n[INT MODE] Commands: add, delete, search, exit\n";

            while (true) {
                cout << "Enter command: ";
                string command;
                getline(cin, command);

                if (command == "exit") {
                    cout << "Exiting integer mode...\n";
                    break;
                } 
                else if (command == "add") {
                    cout << "Enter integers to add (type 'exit' to stop adding):\n";
                    while (true) {
                        cout << "Add int: ";
                        string valStr;
                        getline(cin, valStr);
                        if (valStr == "exit") break;

                        try {
                            int value = stoi(valStr);
                            intTree.add(value);
                            cout << "\nTree after adding " << value << ":\n";
                            intTree.printTree();
                            cout << "In-order traversal: ";
                            intTree.inorder();
                        } catch (...) {
                            cout << "Invalid integer.\n";
                        }
                    }
                } 
                else if (command == "delete") {
                    cout << "Enter integers to delete (type 'exit' to stop deleting):\n";
                    while (true) {
                        cout << "Delete int: ";
                        string valStr;
                        getline(cin, valStr);
                        if (valStr == "exit") break;

                        try {
                            int value = stoi(valStr);
                            intTree.deleteValue(value);
                            cout << "\nTree after deleting " << value << ":\n";
                            intTree.printTree();
                            cout << "In-order traversal: ";
                            intTree.inorder();
                        } catch (...) {
                            cout << "Invalid integer.\n";
                        }
                    }
                } 
                else if (command == "search") {
                    cout << "Enter integers to search (type 'exit' to stop searching):\n";
                    while (true) {
                        cout << "Search int: ";
                        string valStr;
                        getline(cin, valStr);
                        if (valStr == "exit") break;

                        try {
                            int value = stoi(valStr);
                            vector<int> locations = intTree.search(value);
                            if (locations.empty()) {
                                cout << value << " not found in the tree.\n";
                            } else {
                                cout << value << " found at location(s): ";
                                for (int loc : locations) cout << loc << " ";
                                cout << "\n";
                            }
                        } catch (...) {
                            cout << "Invalid integer.\n";
                        }
                    }
                } 
                else {
                    cout << "Unknown command. Commands: add, delete, search, exit\n";
                }
            }
        } 
        else if (mode == "string") {
            cout << "\n[STRING MODE] Commands: add, delete, search, exit\n";

            while (true) {
                cout << "Enter command: ";
                string command;
                getline(cin, command);

                if (command == "exit") {
                    cout << "Exiting string mode...\n";
                    break;
                } 
                else if (command == "add") {
                    cout << "Enter strings to add (type 'exit' to stop adding):\n";
                    while (true) {
                        cout << "Add string: ";
                        string valStr;
                        getline(cin, valStr);
                        if (valStr == "exit") break;

                        stringTree.add(valStr);
                        cout << "\nTree after adding \"" << valStr << "\":\n";
                        stringTree.printTree();
                        cout << "In-order traversal: ";
                        stringTree.inorder();
                    }
                } 
                else if (command == "delete") {
                    cout << "Enter strings to delete (type 'exit' to stop deleting):\n";
                    while (true) {
                        cout << "Delete string: ";
                        string valStr;
                        getline(cin, valStr);
                        if (valStr == "exit") break;

                        stringTree.deleteValue(valStr);
                        cout << "\nTree after deleting \"" << valStr << "\":\n";
                        stringTree.printTree();
                        cout << "In-order traversal: ";
                        stringTree.inorder();
                    }
                } 
                else if (command == "search") {
                    cout << "Enter strings to search (type 'exit' to stop searching):\n";
                    while (true) {
                        cout << "Search string: ";
                        string valStr;
                        getline(cin, valStr);
                        if (valStr == "exit") break;

                        vector<int> locations = stringTree.search(valStr);
                        if (locations.empty()) {
                            cout << "\"" << valStr << "\" not found in the tree.\n";
                        } else {
                            cout << "\"" << valStr << "\" found at location(s): ";
                            for (int loc : locations) cout << loc << " ";
                            cout << "\n";
                        }
                    }
                } 
                else {
                    cout << "Unknown command. Commands: add, delete, search, exit\n";
                }
            }
        } 
        else {
            cout << "Unknown mode. Please type 'int', 'string', or 'quit'.\n";
        }
    }

    cout << "\n=== Final Trees ===\n";
    cout << "\nInteger Tree:\n";
    intTree.printTree();

    cout << "\nString Tree:\n";
    stringTree.printTree();

    return 0;
}

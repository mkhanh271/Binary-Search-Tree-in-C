#include <iostream>
#include <functional>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// ANSI color codes (foreground colors)
const vector<string> COLORS = {
    "\033[31m", // Red
    "\033[32m", // Green
    "\033[33m", // Yellow
    "\033[34m", // Blue
    "\033[35m", // Magenta
    "\033[36m", // Cyan
    "\033[91m", // Light Red
    "\033[92m", // Light Green
    "\033[93m", // Light Yellow
    "\033[94m", // Light Blue
    "\033[95m", // Light Magenta
    "\033[96m"  // Light Cyan
};

const string COLOR_RESET = "\033[0m";
const string RESET_COLOR = "\033[0m";


// Additional colors for messaging
const string COLOR_ERROR = "\033[31m";    // Red for errors
const string COLOR_PROMPT = "\033[36m";   // Cyan for prompts
const string COLOR_SUCCESS = "\033[32m";  // Green for success
const string COLOR_INFO = "\033[33m";     // Yellow for info

template <typename T>
class BinaryTreeNode {
public:
    T value;
    BinaryTreeNode* leftChild = nullptr;
    BinaryTreeNode* rightChild = nullptr;

    BinaryTreeNode(T _value) : value(_value) {}

    void printTree(const map<T, string>& valueColorMap) const {
        printNode(valueColorMap);
        printTreeChildren(valueColorMap);
    }

private:
    void printNode(const map<T, string>& valueColorMap) const {
        auto it = valueColorMap.find(value);
        if (it != valueColorMap.end()) {
            cout << it->second << value << RESET_COLOR << endl;
        } else {
            cout << value << endl;
        }
    }

    void printTreeChildren(const map<T, string>& valueColorMap, string prefix = "") const {
        if (leftChild) {
            cout << prefix << (rightChild ? "├─" : "└─");
            auto it = valueColorMap.find(leftChild->value);
            if (it != valueColorMap.end()) cout << it->second;
            cout << leftChild->value << RESET_COLOR << endl;
            leftChild->printTreeChildren(valueColorMap, prefix + (rightChild ? "│ " : "  "));
        }

        if (rightChild) {
            cout << prefix << "└─";
            auto it = valueColorMap.find(rightChild->value);
            if (it != valueColorMap.end()) cout << it->second;
            cout << rightChild->value << RESET_COLOR << endl;
            rightChild->printTreeChildren(valueColorMap, prefix + "  ");
        }
    }
};

template <typename T>
class BinarySearchTree {
private:
    BinaryTreeNode<T>* root = nullptr;
    function<bool(const T&, const T&)> compare;  // Store comparator

public:
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

    void inorder() const {
        if (!root) {
            cout << COLOR_ERROR << "The tree is empty." << COLOR_RESET << endl;
            return;
        }

        stack<BinaryTreeNode<T>*> stack;
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

    vector<int> search(const T& value) const {
        vector<int> indices;
        if (!root) return indices;

        stack<pair<BinaryTreeNode<T>*, int>> stack;
        stack.push({root, 1});

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

            if (!current) break; // Not found

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
    bool contains(const T& value) const {
        return !search(value).empty();
    }

private:
    void collectUniqueValues(BinaryTreeNode<T>* node, vector<T>& uniqueValues) const {
        if (!node) return;
        uniqueValues.push_back(node->value);
        collectUniqueValues(node->leftChild, uniqueValues);
        collectUniqueValues(node->rightChild, uniqueValues);
    }

    void buildValueColorMap(const vector<T>& uniqueValues, map<T, string>& colorMap) const {
        int colorIndex = 0;
        for (const T& val : uniqueValues) {
            if (colorMap.find(val) == colorMap.end()) {
                colorMap[val] = COLORS[colorIndex % COLORS.size()];
                colorIndex++;
            }
        }
    }

public:
    void printTreeColored() const {
        if (!root) {
            cout << COLOR_ERROR << "The tree is empty." << COLOR_RESET << endl;
            return;
        }

        vector<T> uniqueValues;
        collectUniqueValues(root, uniqueValues);

        sort(uniqueValues.begin(), uniqueValues.end());
        uniqueValues.erase(unique(uniqueValues.begin(), uniqueValues.end()), uniqueValues.end());

        map<T, string> valueColorMap;
        buildValueColorMap(uniqueValues, valueColorMap);

        root->printTree(valueColorMap);
    }
};

void printMenu(bool isIntMode) {
    cout << "\n==============================================\n";
    cout << (isIntMode ? "[INTEGER MODE]" : "[STRING MODE]") << endl;
    cout << "Available operations:\n";
    cout << "  add    - Add values to the tree\n";
    cout << "  delete - Delete values from the tree\n";
    cout << "  search - Search values in the tree\n";
    cout << "  show   - Show current tree structure\n";
    cout << "  exit   - Exit current mode\n";
    cout << "==============================================\n";
}

int main() {
    BinarySearchTree<int> intTree;
    BinarySearchTree<string> stringTree;

    string mode;
    cout << COLOR_INFO << "============= Interactive Binary Search Tree Program ==============" << COLOR_RESET << "\n\n";

    while (true) {
        cout << COLOR_PROMPT << "Choose input mode ('int', 'string', or 'quit'): " << COLOR_RESET;
        getline(cin, mode);
        if (mode == "quit") break;

        BinarySearchTree<int>* iTree = nullptr;
        BinarySearchTree<string>* sTree = nullptr;
        bool isIntMode = false;

        if (mode == "int") {
            iTree = &intTree;
            isIntMode = true;
        } else if (mode == "string") {
            sTree = &stringTree;
        } else {
            cout << COLOR_ERROR << "Unknown mode. Please type 'int', 'string', or 'quit'." << COLOR_RESET << endl;
            continue;
        }

        while (true) {
            cout << "\n==============================================\n";
            cout << (isIntMode ? "[INTEGER MODE]" : "[STRING MODE]") << endl;
            cout << "Available operations:\n";
            cout << "  add    - Add values to the tree\n";
            cout << "  delete - Delete values from the tree\n";
            cout << "  search - Search values in the tree\n";
            cout << "  show   - Show current tree structure\n";
            cout << "  exit   - Exit current mode\n";
            cout << "==============================================\n";

            cout << COLOR_PROMPT << "\nEnter operation : " << COLOR_RESET;
            string operation;
            getline(cin, operation);

            if (operation == "exit") {
                cout << COLOR_INFO << "Exiting " << (isIntMode ? "integer" : "string") << " mode..." << COLOR_RESET << endl;
                break;
            }

            if (operation == "show") {
                cout << "\n--- Current Tree Structure ---\n";
                if (isIntMode) iTree->printTreeColored();
                else sTree->printTreeColored();
                cout << "------------------------------\n";
                continue;
            }

            if (operation != "add" && operation != "delete" && operation != "search") {
                cout << COLOR_ERROR << "Unknown operation." << COLOR_RESET << endl;
                continue;
            }

            cout << COLOR_PROMPT << "\nEnter values to " << operation << " (type 'exit' to stop):\n" << COLOR_RESET;
            while (true) {
                cout << COLOR_PROMPT << "> " << COLOR_RESET;
                string val;
                getline(cin, val);
                if (val == "exit") break;

                if (isIntMode) {
                    try {
                        int v = stoi(val);
                        if (operation == "add") {
                            iTree->add(v);
                            cout << COLOR_SUCCESS << "Added " << v << ". Tree updated:\n" << COLOR_RESET;
                            iTree->printTreeColored();
                        } else if (operation == "delete") {
                            if (iTree->contains(v)) {
                                iTree->deleteValue(v);
                                cout << COLOR_SUCCESS << "Deleted " << v << ". Tree updated:\n" << COLOR_RESET;
                                iTree->printTreeColored();
                            } else {
                                cout << COLOR_ERROR << "Can't delete " << v << " (not found)." << COLOR_RESET << endl;
                            }
                        } else if (operation == "search") {
                            vector<int> indices = iTree->search(v);
                            if (indices.empty()) {
                                cout << COLOR_ERROR << "Value " << v << " not found." << COLOR_RESET << endl;
                            } else {
                                cout << COLOR_INFO << "Value " << v << " found at indices: ";
                                for (int idx : indices) cout << idx << " ";
                                cout << COLOR_RESET << endl;
                            }
                        }
                    } catch (const invalid_argument&) {
                        cout << COLOR_ERROR << "Invalid integer: " << val << COLOR_RESET << endl;
                    }
                } else {
                    if (operation == "add") {
                        sTree->add(val);
                        cout << COLOR_SUCCESS << "Added \"" << val << "\". Tree updated:\n" << COLOR_RESET;
                        sTree->printTreeColored();
                    } else if (operation == "delete") {
                        if (sTree->contains(val)) {
                            sTree->deleteValue(val);
                            cout << COLOR_SUCCESS << "Deleted \"" << val << "\". Tree updated:\n" << COLOR_RESET;
                            sTree->printTreeColored();
                        } else {
                            cout << COLOR_ERROR << "Can't delete \"" << val << "\" (not found)." << COLOR_RESET << endl;
                        }
                    } else if (operation == "search") {
                        vector<int> indices = sTree->search(val);
                        if (indices.empty()) {
                            cout << COLOR_ERROR << "Value \"" << val << "\" not found." << COLOR_RESET << endl;
                        } else {
                            cout << COLOR_INFO << "Value \"" << val << "\" found at indices: ";
                            for (int idx : indices) cout << idx << " ";
                            cout << COLOR_RESET << endl;
                        }
                    }
                }
            }
        }
    }

    cout << COLOR_INFO << "\nThanks for using the Interactive Binary Search Tree Program!" << COLOR_RESET << endl;
    return 0;
}

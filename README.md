# Binary Search Tree in C++

> A fully interactive, template-based **Binary Search Tree (BST)** implementation in C++, featuring colored terminal output, ASCII tree visualization, iterative traversal, and support for multiple data types. Built and evolved across multiple versions from a basic implementation to a feature-rich interactive CLI application.

---
## This is a funny and easy to replicate project that's just my personal project in free time. It still need some improvement so feel free to use and upgrade my code. Thank you !

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Build & Run](#build--run)
- [Usage](#usage)
- [File Versions](#file-versions)
- [References](#references)

---

## Overview

This project implements a **generic Binary Search Tree** using C++ templates, supporting any comparable data type (e.g., `int`, `string`). The implementation evolved through several versions, progressively adding:

- Iterative (non-recursive) algorithms for all operations
- Custom comparator support via `std::function`
- Colored ASCII tree visualization using ANSI escape codes
- An interactive command-line interface

---

## Features

| Feature | Description |
|---|---|
| **Generic / Template** | Works with `int`, `string`, or any comparable type |
| **Custom Comparator** | Pass any `std::function<bool(T,T)>` to define ordering |
| **Add** | Iterative insertion maintaining BST property |
| **Delete** | Handles all 3 cases: leaf, one child, two children (in-order successor) |
| **Search** | Returns all node indices (1-based heap indexing) where value is found |
| **In-order Traversal** | Iterative in-order using explicit stack — outputs sorted sequence |
| **ASCII Tree Print** | Renders tree structure with `├─`, `└─`, `│` box-drawing characters |
| **Color Output** | Each unique value gets a distinct ANSI color in terminal |
| **Interactive CLI** | Menu-driven interface supporting `int` and `string` modes |
| **Memory Safe** | Destructor uses iterative post-order stack traversal to free all nodes |

---

## Project Structure

```
.
├── BinarySearchTree.h           # Header: template class declarations
├── BinarySearchTree.cpp         # Basic recursive BST implementation
├── main.cpp                     # Simple demo: int + string tree
├── binarysearchtree(better).cpp # Improved iterative BST + interactive CLI
├── colortree.cpp                # Colored ASCII tree + interactive CLI
├── save_load_BST.cpp            # Final version: color + styled prompts + CLI
└── README.md
```

| File | Version | Key Addition |
|------|---------|--------------|
| `BinarySearchTree.h` + `BinarySearchTree.cpp` | v1 | Base recursive implementation |
| `main.cpp` | v1 | Basic usage demo |
| `binarysearchtree(better).cpp` | v2 | Fully iterative algorithms, interactive CLI |
| `colortree.cpp` | v3 | ANSI color per node, colored tree rendering |
| `save_load_BST.cpp` | v4 | Styled prompts (colored input/output messages) |

---

## How It Works

### BST Property

```
         5
        / \
       3   7
      / \ / \
     2  4 6  8
```

- Every left child < parent
- Every right child ≥ parent
- In-order traversal always yields a **sorted sequence**

---

### Iterative Algorithms

All core operations use **explicit stacks** instead of recursion to avoid stack overflow on large trees:

**Add** — walks left/right until an empty slot is found, inserts new node.

**Delete** — handles 3 cases:
1. Leaf node → remove directly
2. One child → replace node with its child
3. Two children → find in-order successor (leftmost node in right subtree), copy value, delete successor

**In-order Traversal** — uses a stack to simulate the call stack:
```
push left nodes → visit top → go right → repeat
```

**Search** — BFS-style traversal using heap indexing (root = 1, left = 2i, right = 2i+1), returns all matching indices.

---

### Colored Tree Rendering

Each unique value in the tree is assigned a distinct ANSI foreground color from a pool of 12 colors:

```
Red, Green, Yellow, Blue, Magenta, Cyan,
Light Red, Light Green, Light Yellow, Light Blue, Light Magenta, Light Cyan
```

The ASCII tree is rendered using box-drawing characters:
```
5
├─3
│ ├─2
│ └─4
└─7
  ├─6
  └─8
```

---

## Build & Run

### Requirements
- C++17 or later
- GCC / Clang / MSVC

### Compile (recommended: final version)

```bash
g++ -std=c++17 -o bst "save_load_BST.cpp"
./bst
```

### Compile basic version

```bash
g++ -std=c++17 -o bst_basic main.cpp BinarySearchTree.cpp
./bst_basic
```

### Compile iterative version

```bash
g++ -std=c++17 -o bst_iter "binarysearchtree(better).cpp"
./bst_iter
```

---

## Usage

After running, you will see an interactive menu:

```
============= Interactive Binary Search Tree Program ==============

Choose input mode ('int', 'string', or 'quit'):
```

### Mode Selection

| Input | Description |
|-------|-------------|
| `int` | Work with integer BST |
| `string` | Work with string BST |
| `quit` | Exit the program |

### Available Operations

| Command | Description |
|---------|-------------|
| `add` | Add one or more values to the tree |
| `delete` | Remove one or more values from the tree |
| `search` | Find a value and display its index in the tree |
| `show` | Display the current tree structure with colors |
| `exit` | Return to mode selection |

### Example Session

```
Choose input mode: int

Enter operation: add
> 5
Added 5. Tree updated:
5

> 3
Added 3. Tree updated:
5
└─3

> 7
Added 7. Tree updated:
5
├─3
└─7

> exit

Enter operation: search
> 3
Value 3 found at indices: 2

Enter operation: delete
> 5
Deleted 5. Tree updated:
6
└─3
  └─7
```

> **Note:** Colors are visible in terminals that support ANSI escape codes (Linux, macOS Terminal, Windows Terminal).

---

## File Versions

### v1 — `BinarySearchTree.h` + `BinarySearchTree.cpp` + `main.cpp`
- Recursive insert, in-order, search, delete
- Templated with `std::function` comparator
- Basic demo in `main.cpp`

### v2 — `binarysearchtree(better).cpp`
- All operations converted to **iterative** using `std::stack`
- Interactive CLI with `int` and `string` modes
- ASCII tree print with `├─` / `└─` connectors

### v3 — `colortree.cpp`
- Added **ANSI color** per unique node value
- `printTreeColored()` assigns and renders colors
- `contains()` helper for safe delete checking

### v4 — `save_load_BST.cpp` *(Final)*
- All v3 features retained
- **Colored prompt messages**: errors in red, success in green, prompts in cyan, info in yellow
- Cleaner UX with consistent color-coded feedback throughout

---

## References

- Cormen, T.H. et al. — *Introduction to Algorithms (CLRS)*, 3rd ed., MIT Press
- Stroustrup, B. — *The C++ Programming Language*, 4th ed.
- [cppreference.com — std::function](https://en.cppreference.com/w/cpp/utility/functional/function)
- [ANSI Escape Codes — Wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code)

---

## License

MIT License — see [LICENSE](LICENSE) for details.

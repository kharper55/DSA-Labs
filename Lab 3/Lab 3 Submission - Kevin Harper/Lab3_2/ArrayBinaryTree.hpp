#ifndef ARRAY_BINARY_TREE_HPP
#define ARRAY_BINARY_TREE_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename E>
class ArrayBinaryTree {
private:
    std::vector<E> tree;     // Dynamic array for storing elements
    int capacity;            // Maximum size of the tree
    int n;                   // Number of elements in the tree

public:
    class Position {
        private:
            int index;           // Index of the element in the array
            ArrayBinaryTree* tree; // Pointer to the tree for access
        public:
            Position(int i, ArrayBinaryTree* t) : index(i), tree(t) {}

            E& operator*() {
                if (index >= tree->tree.size() || index < 0)
                    throw std::out_of_range("Invalid position");
                return tree->tree[index];
            }

            Position left() const {
                int leftIndex = 2 * index + 1;
                if (leftIndex >= tree->capacity)
                    throw std::out_of_range("No left child");
                return Position(leftIndex, tree);
            }

            Position right() const {
                int rightIndex = 2 * index + 2;
                if (rightIndex >= tree->capacity)
                    throw std::out_of_range("No right child");
                return Position(rightIndex, tree);
            }

            Position parent() const {
                if (index == 0)
                    throw std::out_of_range("Root node has no parent");
                return Position((index - 1) / 2, tree);
            }

            bool isRoot() const {
                return index == 0;
            }

            bool isExternal() const {
                int leftIndex = 2 * index + 1;
                int rightIndex = 2 * index + 2;
                return (leftIndex >= tree->n && rightIndex >= tree->n);
            }

            int getIndex() const { // Public accessor for index
                return index;
            }
        };

        using PositionList = std::vector<Position>; // list of positions

    public:
        ArrayBinaryTree(int cap = 100) : capacity(cap), n(0) {
            tree.resize(capacity, E{}); // Initialize with default values
        }

        int size() const {
            return n;
        }

        bool empty() const {
            return n == 0;
        }

        Position root() {
            if (empty())
                throw std::out_of_range("Tree is empty");
            return Position(0, this);
        }

        void addRoot(const E& e) {
            if (n > 0)
                throw std::runtime_error("Root already exists");
            tree[0] = e;
            n++;
        }

        void expandExternal(const Position& p, const E& leftVal, const E& rightVal) {
            int index = p.getIndex();              // Access index through public accessor
            int leftIndex = 2 * index + 1;
            int rightIndex = 2 * index + 2;

            if (leftIndex >= capacity || rightIndex >= capacity)
                throw std::out_of_range("Exceeded tree capacity");
            if (n <= leftIndex) n = leftIndex + 1;
            if (n <= rightIndex) n = rightIndex + 1;

            tree[leftIndex] = leftVal;
            tree[rightIndex] = rightVal;
        }

        PositionList positions() const {
            PositionList pl;
            preorder(0, pl);               // Start traversal from root index
            return pl;                     // Return resulting list
        }

        // Recursive function to build the binary tree using positions
        void buildTree(const std::vector<E>& nodes, int index) {
            // If the index is out of bounds, return
            if (index >= nodes.size()) {
                return;
            }

            // Assign value at the current index in the tree
            tree[index] = nodes[index];
            n = std::max(n, index + 1);  // Update the number of elements if necessary

            // Recursively build the left and right children
            buildTree(nodes, 2 * index + 1);  // Left child
            buildTree(nodes, 2 * index + 2);  // Right child
        }

        // Function to start the tree construction from the root using the buildTree helper
        void constructTree(const std::vector<E>& nodes) {
            if (nodes.empty()) return; // Check if the input vector is empty

            addRoot(nodes[0]);  // Start with the root

            // Recursively build the tree starting from the root
            buildTree(nodes, 0);
        }

    private:
        void preorder(int index, PositionList& pl) const {
            if (index >= n || tree[index] == E{}) // Check for invalid index or empty node
                return;

            pl.emplace_back(index, const_cast<ArrayBinaryTree*>(this)); // Visit current node
            preorder(2 * index + 1, pl);                                // Visit left child
            preorder(2 * index + 2, pl);                                // Visit right child
        }
};

#endif // ARRAY_BINARY_TREE_HPP

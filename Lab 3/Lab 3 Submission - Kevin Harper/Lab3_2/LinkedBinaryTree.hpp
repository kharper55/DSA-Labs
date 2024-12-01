#ifndef LINKED_BINARY_TREE_HPP
#define LINKED_BINARY_TREE_HPP

#include <stdio.h> // for NULL
#include <list>    // for std::list
#include <vector>

template <typename E> // base element type
class LinkedBinaryTree {
    protected:
        struct Node {                    // a node of the tree
            E elt;                       // element value
            Node* par;                   // parent
            Node* left;                  // left child
            Node* right;                 // right child
            Node() : elt(), par(NULL), left(NULL), right(NULL) { } // def constructor
            Node(const E& val) : elt(val), par(NULL), left(NULL), right(NULL) { } // constructor
        };

    public:
        class Position {                 // position in the tree
        private:
            Node* v;                     // pointer to the node
        public:
            Position(Node* _v = NULL) : v(_v) { } // constructor
            E& operator*()               // get element
            { return v->elt; }
            Position left() const        // get left child
            { return Position(v->left); }
            Position right() const       // get right child
            { return Position(v->right); }
            Position parent() const      // get parent
            { return Position(v->par); }
            bool isRoot() const          // root of the tree?
            { return v->par == NULL; }
            bool isExternal() const      // an external node?
            { return v->left == NULL && v->right == NULL; }
            friend class LinkedBinaryTree; // give tree access
        };

        using PositionList = std::list<Position>; // list of positions

    public:
        LinkedBinaryTree() : _root(NULL), n(0) { } // constructor
        int size() const                           // number of nodes
        { return n; }
        bool empty() const                         // is tree empty?
        { return size() == 0; }
        Position root() const                      // get the root
        { return Position(_root); }
        void addRoot(const E& val)                             // add root to empty tree
        { _root = new Node(val); n = 1; }
        PositionList positions() const;            // list of nodes
        void expandExternal(const Position& p);    // expand external node
        Position removeAboveExternal(const Position& p); // remove p and parent

        // Recursive function to build the binary tree, assuming a complete binary tree
        Node* buildTree(const std::vector<E>& nodes, int index, Node* parent) {
            // If the index is out of bounds, return null
            if (index >= nodes.size()) {
                return nullptr;
            }

            // Create the node at the current index
            Node* node = new Node(nodes[index]);
            node->par = parent; // Set the parent

            // Recursively build the left and right subtrees
            node->left = buildTree(nodes, 2 * index + 1, node);  // Left child
            node->right = buildTree(nodes, 2 * index + 2, node); // Right child

            return node;
        }

        // Function to start the tree construction from the root
        void constructTree(const std::vector<E>& nodes) {
            if (nodes.empty()) return; // Check if the input vector is empty

            addRoot(nodes[0]);  // Start with the root
            _root = buildTree(nodes, 0, nullptr);  // Build the tree recursively from index 0
        }

    protected: // local utilities
        void preorder(Node* v, PositionList& pl) const; // preorder utility

    private:
        Node* _root; // pointer to the root
        int n;       // number of nodes
};

// list of all nodes
template <typename E>
typename LinkedBinaryTree<E>::PositionList LinkedBinaryTree<E>::positions() const {
    PositionList pl;
    if (_root != nullptr) preorder(_root, pl); // preorder traversal
    return pl;                        // return resulting list
}

// preorder traversal
template <typename E>
void LinkedBinaryTree<E>::preorder(Node* v, PositionList& pl) const {
    pl.push_back(Position(v));        // add this node
    if (v->left != NULL)              // traverse left subtree
        preorder(v->left, pl);
    if (v->right != NULL)             // traverse right subtree
        preorder(v->right, pl);
}

// expand external node
template <typename E>
void LinkedBinaryTree<E>::expandExternal(const Position& p) {
    Node* v = p.v;                   // p's node
    v->left = new Node;              // add a new left child
    v->left->par = v;                // v is its parent
    v->right = new Node;             // and a new right child
    v->right->par = v;               // v is its parent
    n += 2;                          // two more nodes
}

// remove p and parent
template <typename E>
typename LinkedBinaryTree<E>::Position LinkedBinaryTree<E>::removeAboveExternal(const Position& p) {
    Node* w = p.v; Node* v = w->par; // get p's node and parent
    Node* sib = (w == v->left ? v->right : v->left);
    if (v == _root) {                // child of root?
        _root = sib;                 // ...make sibling root
        sib->par = NULL;
    } else {
        Node* gpar = v->par;         // w's grandparent
        if (v == gpar->left) gpar->left = sib; // replace parent by sib
        else gpar->right = sib;
        sib->par = gpar;
    }
    delete w; delete v;              // delete removed nodes
    n -= 2;                          // two fewer nodes
    return Position(sib);
}

#endif // LINKED_BINARY_TREE_HPP

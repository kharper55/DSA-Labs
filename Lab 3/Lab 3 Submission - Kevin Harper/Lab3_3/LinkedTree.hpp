#ifndef LINKED_TREE_HPP
#define LINKED_TREE_HPP

#include <stdio.h> // for NULL
#include <list>    // for std::list

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

template <typename E>
class LinkedTree {
    protected:
        struct Node {                      // a node of the tree
            E elt;                         // element value
            Node* par;                     // parent
            std::vector<Node*> children;   // children of the node
            Node() : elt(), par(NULL) { }  // constructor
        };

    public:
        class Position {                   // position in the tree
        private:
            Node* v;                        // pointer to the node
        public:
            Position(Node* _v = NULL) : v(_v) { }  // constructor
            E& operator*()                    // get element
            { return v->elt; }
            Position parent() const           // get parent
            { return Position(v->par); }
            bool isRoot() const               // root of the tree?
            { return v->par == NULL; }
            bool isExternal() const           // an external node?
            { return v->children.empty(); }
            size_t numChildren() const        // number of children
            { return v->children.size(); }
            Position child(int index) const   // get child at index
            { return Position(v->children[index]); }
            friend class LinkedTree;         // give tree access
        };

        using PositionList = std::list<Position>;  // list of positions

    public:
        LinkedTree() : _root(NULL), n(0) { } // constructor
        int size() const                      // number of nodes
        { return n; }
        bool empty() const                    // is tree empty?
        { return size() == 0; }
        Position root() const                 // get the root
        { return Position(_root); }
        void addRoot(const E& value)          // add root to empty tree
        { _root = new Node; _root->elt = value; n = 1; }
        PositionList positions(bool isPreorder) const;       // list of nodes
        void expandExternal(const Position& p, const std::vector<E>& children); // expand external node
        Position removeAboveExternal(const Position& p); // remove p and parent
        void addChildren(const Position& parentPos, const std::vector<E>& children);
        void populateTreeFromFile(const std::string& filename);

    protected:  // local utilities
        void postorder(Node* v, PositionList& pl) const;
        void preorder(Node* v, PositionList& pl) const; // preorder utility

    private:
        Node* _root; // pointer to the root
        int n;       // number of nodes
};

// list of all nodes
template <typename E>
typename LinkedTree<E>::PositionList LinkedTree<E>::positions(bool isPreorder) const {
    PositionList pl;
    if (isPreorder) {
        preorder(_root, pl);          // preorder traversal
    } else {
        postorder(_root, pl);         // postorder traversal
    }
    return pl;                        // return resulting list
}

// preorder traversal
template <typename E>
void LinkedTree<E>::preorder(Node* v, PositionList& pl) const {
    pl.push_back(Position(v));        // add this node
    for (auto child : v->children)    // traverse all children
        preorder(child, pl);
}

// Postorder traversal
template <typename E>
void LinkedTree<E>::postorder(Node* v, PositionList& pl) const {
    for (auto child : v->children)    // traverse all children
        postorder(child, pl);         // recursive postorder traversal
    pl.push_back(Position(v));        // add this node after its children
}

// expand external node with multiple children
template <typename E>
void LinkedTree<E>::expandExternal(const Position& p, const std::vector<E>& children) {
    Node* v = p.v;  // p's node
    for (const auto& childVal : children) {
        Node* newChild = new Node;
        newChild->elt = childVal;
        newChild->par = v;              // v is its parent
        v->children.push_back(newChild); // add child to the children list
    }
    n += children.size();  // increase the size by the number of new children
}

// remove p and parent
template <typename E>
typename LinkedTree<E>::Position LinkedTree<E>::removeAboveExternal(const Position& p) {
    Node* w = p.v; Node* v = w->par; // get p's node and parent
    Node* sib = nullptr;

    // Remove the child from parent's children list
    for (auto it = v->children.begin(); it != v->children.end(); ++it) {
        if (*it == w) {
            sib = *it;
            v->children.erase(it);  // remove child
            break;
        }
    }

    if (v == _root) {  // child of root?
        _root = nullptr;  // ...make the tree empty
    } else {
        delete w; delete v;  // delete removed nodes
        n -= 2;               // two fewer nodes
    }

    return Position(sib);
}

template <typename E>
void LinkedTree<E>::addChildren(const Position& parentPos, const std::vector<E>& children) {
    Node* parentNode = parentPos.v;  // Access the node from the position
    for (const auto& childVal : children) {
        Node* child = new Node;      // Create a new node for each child
        child->elt = childVal;       // Assign the child's value
        child->par = parentNode;     // Set the parent
        parentNode->children.push_back(child); // Add child to parent's children vector
        ++n;                         // Increment the node count
    }
}

// Populate the tree from a file
template <typename E>
void LinkedTree<E>::populateTreeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Error opening file " + filename + ".");
    }

    std::string line;
    bool isRootProcessed = false;
    std::stack<Position> parentStack;  // Stack to keep track of parents

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string parentName;
        iss >> parentName;  // Read the parent node name

        // Process the root node first
        if (!isRootProcessed) {
            addRoot(parentName);  // Initialize the root
            isRootProcessed = true;
            parentStack.push(root());  // Push root onto stack
        }

        // Read the children part of the line
        std::string childrenStr;
        std::getline(iss, childrenStr);  // The rest is the children part

        std::vector<std::string> children;  // To store children of the current node

        // If there are children (not just "#"), process them
        if (!childrenStr.empty() && childrenStr != " #") {
            childrenStr = childrenStr.substr(1, childrenStr.size() - 2);  // Remove surrounding brackets
            std::istringstream childStream(childrenStr);
            std::string child;
            while (childStream >> child) {
                children.push_back(child);  // Add child names to vector
            }
        }

        // Add children to the parent node
        if (!parentStack.empty()) {
            Position parentPos = parentStack.top();  // Get the current parent position
            addChildren(parentPos, children);  // Add children to parent node

            // Push each child to the stack for future processing
            for (const auto& childName : children) {
                Position childPos = parentPos.child(parentPos.numChildren() - 1);  // Get the child position
                parentStack.push(childPos);  // Push child onto stack
            }
        }

        // If the current line ends with "#", it indicates the end of the children for the current parent node
        if (childrenStr.empty() || childrenStr == " #") {
            parentStack.pop();  // Pop the parent from the stack after processing its children
        }
    }

    file.close();
}

#endif // LINKED_TREE_HPP

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "BinaryTreeExceptions.hpp"
#include "LinkedBinaryTree.hpp"
#include "TreeEntry.hpp"
#include <string>
#include <cstring>

template <typename E>
class SearchTree {					// a binary search tree
    public: 						// public types
        typedef typename E::Key K;				// a key
        typedef typename E::Value V;			// a value
        class Iterator;					// an iterator/position
    public:						// public functions
        SearchTree() : T(), n(0) { T.addRoot(); T.expandExternal(T.root()); } // constructor
        int size() const { return n; }					// number of entries
        bool empty() const	{ return n == 0;}				// is the tree empty?
        Iterator find(const K& k);				// find entry with key k
        Iterator insert(const K& k, const V& x);		// insert (k,x)
        void erase(const K& k) /*throw(NonexistentElement)*/;	// remove key k entry
        void erase(const Iterator& p);			// remove entry at p
        Iterator begin();					// iterator to first entry
        Iterator end();					// iterator to end entry
        void createBalancedBST(const std::vector<typename E::Key>& keys, 
                       const std::vector<typename E::Value>& values, int start, int end);
        //void inorderTraversal(const TPos& node, const bool printKey) const;
        void printTree() const;
    protected:						// local utilities
        typedef LinkedBinaryTree<E> BinaryTree;			// linked binary tree
        typedef typename LinkedBinaryTree<E>::Position TPos;		// position in the tree
        void printTree(const TPos& node, const TPos& parent, const std::string& relationship) const;
        void inorderTraversal(const TPos& node, const bool printKey) const;
        TPos root() const;					// get virtual root
        TPos finder(const K& k, const TPos& v);		// find utility
        TPos inserter(const K& k, const V& x);		// insert utility
        TPos eraser(TPos& v);				// erase utility
        TPos restructure(const TPos& v); 			// restructure
            /*throw(BoundaryViolation);*/ //C++17 violation
    private: 						// member data
        BinaryTree T;				// the binary tree
        int n;						// number of entries
        public:
        class Iterator {
            private:
                TPos v;  // position in the tree
            public:
                Iterator(const TPos& vv) : v(vv) { }  // constructor

                // Make const version of operator*() to support const iterators
                const E& operator*() const { return *v; }  // get entry (read-only)
                E& operator*() { return *v; }  // get entry (read/write)

                bool operator==(const Iterator& p) const { return v == p.v; }  // compare iterators

                Iterator& operator++();  // inorder successor
                friend class SearchTree;  // give search tree access
                TPos getPosition() const { return v; }
        };
};

template <typename E>					// inorder successor
typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
    TPos w = v.right();
    if (!(w.isExternal())) {				// have right subtree?
        do { v = w; w = w.left(); }			// move down left chain
        while (!(w.isExternal()));
    }
    else {
        w = v.parent();					// get parent
        while (v == w.right())				// move up right chain
        { v = w; w = w.parent(); }
        v = w;						// and first link to left
    }
    return *this;
}

template <typename E>					// iterator to first entry
typename SearchTree<E>::Iterator SearchTree<E>::begin() {
    TPos v = root();					// start at virtual root
    while (!(v.isExternal())) v = v.left();		// find leftmost node
    return Iterator(v.parent());
}
  
template <typename E>					// iterator to end entry
typename SearchTree<E>::Iterator SearchTree<E>::end() { 
    return Iterator(T.root()); // return the super root
}			

template <typename E>					// remove utility
typename SearchTree<E>::TPos SearchTree<E>::eraser(TPos& v) {
    TPos w;
    if (v.left().isExternal()) w = v.left();		// remove from left
    else if (v.right().isExternal()) w = v.right();	// remove from right
    else {						// both internal?
        w = v.right();					// go to right subtree
        do { w = w.left(); } while (!(w.isExternal()));	// get leftmost node
        TPos u = w.parent();
        v->setKey(u->key()); v->setValue(u->value());	// copy w's parent to v
    }
    n--;						// one less entry
    return T.removeAboveExternal(w);			// remove w and parent
}
  
template <typename E>					// remove key k entry
void SearchTree<E>::erase(const K& k) {
    TPos v = finder(k, root());				// search from virtual root
    if (v.isExternal())					// not found?
        throw NonexistentElement("Erase of nonexistent");
    eraser(v);						// remove it
}
  
template <typename E>					// erase entry at p
void SearchTree<E>::erase(const Iterator& p) { 
    eraser(p.v); 
}

template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::finder(const K& k, const TPos& v) {
    if (v.isExternal()) return v; // key not found
    if (k < (*v).key()) return finder(k, v.left()); // search left subtree
    else if ((*v).key() < k) return finder(k, v.right()); // search right subtree
    else return v; // found it here
}

template <typename E>					// find entry with key k
typename SearchTree<E>::Iterator SearchTree<E>::find(const K& k) {
    TPos v = finder(k, root());				// search from virtual root
    if (!(v.isExternal())) return Iterator(v);		// found it
    else return end();					// didn't find it
}

template <typename E>					// insert utility
typename SearchTree<E>::TPos SearchTree<E>::inserter(const K& k, const V& x) {
    TPos v = finder(k, root());				// search from virtual root
    while (!(v.isExternal()))				// key already exists?
        v = finder(k, v.right());				// look further
    T.expandExternal(v);				// add new internal node
    (*v).setKey(k); (*v).setValue(x);			// set entry
    n++;						// one more entry
    return v;						// return insert position
}
  
template <typename E>					// insert (k,x)
typename SearchTree<E>::Iterator SearchTree<E>::insert(const K& k, const V& x) { 
    TPos v = inserter(k, x); return Iterator(v); 
}

template <typename E>					// get virtual root
typename SearchTree<E>::TPos SearchTree<E>::root() const{ // left child of super root
    return T.root().left(); 
}	

template <typename E>
void SearchTree<E>::createBalancedBST(const std::vector<typename E::Key>& keys, 
                       const std::vector<typename E::Value>& values, int start, int end) {
    if (start > end) {
        return; // Base case: no elements to process
    }
    
    int mid = start + (end - start) / 2; // Find the middle element
    insert(keys[mid], values[mid]); // Insert middle element as root/subroot

    // Recursively construct the left and right subtrees
    createBalancedBST(keys, values, start, mid - 1); // Left subtree
    createBalancedBST(keys, values, mid + 1, end);   // Right subtree
}

template <typename E>
void SearchTree<E>::inorderTraversal(const TPos& node, const bool printKey) const {
    if (node.isExternal()) return; // Base case: empty node

    // Traverse left subtree
    inorderTraversal(node.left(), printKey);

    // Visit current node and print
    if (printKey) std::cout << "Key: " << (*node).key() << ", Value: " << (*node).value() << std::endl;
    else std::cout << (*node).value() << std::endl;

    // Traverse right subtree
    inorderTraversal(node.right(), printKey);
}

template <typename E>
void SearchTree<E>::printTree() const {
    std::cout << "\nList contents: \n";
    inorderTraversal(root(), false);
}

template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::restructure(const TPos& x) {
    TPos y = x.parent();  // y is the parent of x
    TPos z = y.parent();  // z is the grandparent of x

    // Identify the rotation type based on the positions of x, y, and z
    if ((x == y.left() && y == z.left()) || (x == y.right() && y == z.right())) {
        // Single rotation (LL or RR)
        if (x == y.left() && y == z.left()) {
            T.rotateRight(z);  // LL case: perform a right rotation on z
        } else {
            T.rotateLeft(z);   // RR case: perform a left rotation on z
        }
        return y;  // Return the new root of the subtree
    } else {
        // Double rotation (LR or RL)
        if (x == y.right() && y == z.left()) {
            T.rotateLeft(y);   // LR case: perform a left rotation on y
            T.rotateRight(z);  // Then perform a right rotation on z
        } else {
            T.rotateRight(y);  // RL case: perform a right rotation on y
            T.rotateLeft(z);   // Then perform a left rotation on z
        }
        return x;  // Return the new root of the subtree
    }
}


#endif // BINARY_SEARCH_TREE_HPP

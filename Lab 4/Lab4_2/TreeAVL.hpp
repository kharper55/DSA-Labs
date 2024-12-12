#ifndef TREE_AVL_HPP
#define TREE_AVL_HPP

#include "EntryAVL.hpp"
#include "BinarySearchTree.hpp"
#include "BinaryTreeExceptions.hpp"

template <typename E>					// an AVL tree
class AVLTree : public SearchTree< AVLEntry<E> > {
    public:						// public types
        typedef AVLEntry<E> AVLEntry;			// an entry
        typedef typename SearchTree<AVLEntry>::Iterator Iterator; // an iterator
        protected:						// local types
        typedef typename AVLEntry::Key K;			// a key
        typedef typename AVLEntry::Value V;			// a value
        typedef SearchTree<AVLEntry> ST;			// a search tree
        typedef typename ST::TPos TPos;			// a tree position
    public:						// public functions
        AVLTree() : ST() { };						// constructor
        Iterator insert(const K& k, const V& x);		// insert (k,x)
        void erase(const K& k) /*throw(NonexistentElement)*/;	// remove key k entry
        void erase(const Iterator& p);			// remove entry at p
    protected:						// utility functions 
        int height(const TPos& v) const { return (v.isExternal() ? 0 : (*v).height()); };			// node height utility
        void setHeight(TPos v);				// set height utility
        bool isBalanced(const TPos& v) const;		// is v balanced?
        TPos tallGrandchild(const TPos& v) const;		// get tallest grandchild
        void rebalance(const TPos& v);			// rebalance utility
};

template <typename E>					// remove key k entry
void AVLTree<E>::erase(const K& k) /*throw(NonexistentElement)*/ {
    TPos v = finder(k, ST::root());			// find in base tree
    if (Iterator(v) == ST::end())			// not found?
        throw NonexistentElement("Erase of nonexistent");
    TPos w = eraser(v);					// remove it
    rebalance(w);					// rebalance if needed
}

template <typename E>					// insert (k,x)
typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    TPos v = SearchTree<AVLEntry>::inserter(k, x);				// insert in base tree
    setHeight(v);					// compute its height
    rebalance(v);					// rebalance if needed
    return Iterator(v);
}

template <typename E>					// set height utility
void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
}

template <typename E>					// is v balanced?
bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

template <typename E>					// get tallest grandchild
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr)) {			// left child taller
        if (height(zl.left()) >= height(zl.right())) return zl.left();
        else return zl.right();
    }
    else {			// right child taller
        if (height(zr.right()) >= height(zr.left())) return zr.right();
        else return zr.left();
    }
}

template <typename E>					// rebalancing utility
void AVLTree<E>::rebalance(const TPos& v) {
    TPos z = v;
    while (!(z == ST::root())) {			// rebalance up to root
        z = z.parent();
        setHeight(z);					// compute new height
        if (!isBalanced(z)) {				// restructuring needed
            TPos x = tallGrandchild(z);
            z = SearchTree<AVLEntry>::restructure(x);				// trinode restructure
            setHeight(z.left());				// update heights
            setHeight(z.right());
            setHeight(z);
        }
    }
}

#endif // TREE_AVL_HPP

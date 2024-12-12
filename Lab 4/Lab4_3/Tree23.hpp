#ifndef TREE_2_3_HPP
#define TREE_2_3_HPP

#include "Entry23.hpp" // Optional entry class specific to 2-3 tree
#include "BinarySearchTree.hpp"
#include "BinaryTreeExceptions.hpp"

template <typename E>					// a 2-3 tree
class TwoThreeTree : public SearchTree<E> {
public:						// public types
    typedef E Entry;					// an entry
    typedef typename SearchTree<E>::Iterator Iterator; // an iterator
protected:						// local types
    typedef typename E::Key K;				// a key
    typedef typename E::Value V;				// a value
    typedef SearchTree<E> ST;				// a search tree
    typedef typename ST::TPos TPos;			// a tree position
public:						// public functions
    TwoThreeTree() : ST() { };						// constructor
    Iterator insert(const K& k, const V& x);		// insert (k,x)
    void erase(const K& k) /*throw(NonexistentElement)*/;	// remove key k entry
    void erase(const Iterator& p);			// remove entry at p
protected:						// utility functions 
    bool isBalanced(const TPos& v) const;		// is v balanced?
    TPos restructure(const TPos& x);			// restructure utility specific to 2-3 tree
};

template <typename E>					// remove key k entry
void TwoThreeTree<E>::erase(const K& k) /*throw(NonexistentElement)*/ {
    TPos v = finder(k, ST::root());			// find in base tree
    if (Iterator(v) == ST::end())			// not found?
        throw NonexistentElement("Erase of nonexistent");
    TPos w = eraser(v);					// remove it
    rebalance(w);					// rebalance if needed
}

template <typename E>					// insert (k,x)
typename TwoThreeTree<E>::Iterator TwoThreeTree<E>::insert(const K& k, const V& x) {
    TPos v = SearchTree<E>::inserter(k, x);				// insert in base tree
    SearchTree<E>::restructure(v);					// rebalance if needed
    return Iterator(v);
}

template <typename E>					// is v balanced?
bool TwoThreeTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

#endif // TREE_2_3_HPP

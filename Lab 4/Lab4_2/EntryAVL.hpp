#ifndef ENTRY_AVL_HPP
#define ENTRY_AVL_HPP

#include "TreeAVL.hpp"

template <typename E>
class AVLTree;

template <typename E>
class AVLEntry : public E {				// an AVL entry
    private:
        int ht;						// node height
    protected:						// local types
        typedef typename E::Key K;				// key type
        typedef typename E::Value V;			// value type
        int height() const { return ht; }			// get height
        void setHeight(int h) { ht = h; }			// set height
    public:						// public functions
        AVLEntry(const K& k = K(), const V& v = V())	// constructor
            : E(k,v), ht(0) { }	
    
    friend class AVLTree<E>;				// allow AVLTree access
};

#endif // ENTRY_AVL_HPP
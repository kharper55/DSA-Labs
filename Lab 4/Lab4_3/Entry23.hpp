#ifndef ENTRY_2_3_HPP
#define ENTRY_2_3_HPP

#include "Tree23.hpp"

template <typename E>
class TwoThreeTree;

template <typename E>
class Entry23 : public E {				// a 2-3 tree entry
    protected:						// local types
        typedef typename E::Key K;				// key type
        typedef typename E::Value V;			// value type
        typedef Entry23<E> ChildType;			// child type for convenience
        ChildType* left;				// left child
        ChildType* mid;				// middle child (for 3-node internal entries)
        ChildType* right;				// right child
        K keys[2];					// up to 2 keys
        V values[2];					// up to 2 values
        
    public:						// public functions
        Entry23(const K& k1 = K(), const V& v1 = V(), const K& k2 = K(), const V& v2 = V()) // constructor
            : E(), left(nullptr), mid(nullptr), right(nullptr) {
            keys[0] = k1;
            values[0] = v1;
            keys[1] = k2;
            values[1] = v2;
        }
    
    // Allow access to the TwoThreeTree for insertion, deletion, and rebalancing
    friend class TwoThreeTree<E>;
};

#endif // ENTRY_2_3_HPP
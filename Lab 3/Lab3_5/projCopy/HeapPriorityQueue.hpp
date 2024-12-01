#ifndef HEAP_PRIORITY_QUEUE_HPP
#define HEAP_PRIORITY_QUEUE_HPP

#include <functional>  // For std::greater
#include "VectorCompleteTree.hpp"

template <typename E, typename C = std::greater<E>>
class HeapPriorityQueue { 
    public:
        HeapPriorityQueue(const C& comp = C()) : comp(comp) {} // constructor with user specified comparator
        int size() const; 			// number of elements
        bool empty() const;  		// is the queue empty?
        void insert(const E& e);	// insert element
        const E& root();			// minimum element
        void removeRoot();			// remove minimum
    private: 
        VectorCompleteTree<E> T;	// priority queue contents
        C comp;					    // user specified comparator
                                    // shortcut for tree position
        typedef typename VectorCompleteTree<E>::Position Position;
};

template <typename E, typename C>		// insert element
void HeapPriorityQueue<E,C>::insert(const E& e) {
    T.addLast(e);				    // add e to heap
    Position v = T.last();			// e's position
    while (!T.isRoot(v)) {			// up-heap bubbling
        Position u = T.parent(v);
        if (!comp(*v, *u)) break;		// if v in order, we're done
        T.swap(v, u);				// ...else swap with parent
        v = u;
    }
}

template <typename E, typename C>		// remove minimum
void HeapPriorityQueue<E,C>::removeRoot() {
    if (size() == 1)				// only one node?
        T.removeLast();				// ...remove it
    else {
        Position u = T.root();			// root position
        T.swap(u, T.last());			// swap last with root
        T.removeLast();				// ...and remove last
        while (T.hasLeft(u)) { 			// down-heap bubbling
            Position v = T.left(u);
            if (T.hasRight(u) && comp(*(T.right(u)), *v))
                v = T.right(u);			// v is u's smaller child
            if (comp(*v, *u)) {			// is u out of order?
                T.swap(u, v);				// ...then swap
                u = v;
            }
            else break;				// else we're done
        }
    }
}

template <typename E, typename C>		// number of elements
int HeapPriorityQueue<E,C>::size() const { 
    return T.size(); 
}

template <typename E, typename C>		// is the queue empty?
bool HeapPriorityQueue<E,C>::empty() const {
    return size() == 0; 
}

template <typename E, typename C>		// minimum element
const E& HeapPriorityQueue<E,C>::root() { 
    return *(T.root()); 
}			// return reference to root element

#endif // HEAP_PRIORITY_QUEUE_HPP
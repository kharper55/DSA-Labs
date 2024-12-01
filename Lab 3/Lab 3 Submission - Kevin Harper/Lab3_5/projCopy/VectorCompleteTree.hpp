#ifndef VECTOR_COMPLETE_TREE_HPP
#define VECTOR_COMPLETE_TREE_HPP

#include <vector>

template <typename E>
class VectorCompleteTree {
    //... insert private member data and protected utilities here
    private:					// member data
        std::vector<E> V;				// tree contents
    public:
        VectorCompleteTree() : V(1) {}		// constructor
        typedef typename std::vector<E>::iterator Position; // a position in the tree
        int size() const				                { return V.size() - 1; }
        Position left(const Position& p)		        { return pos(2*idx(p)); }
        Position right(const Position& p)		        { return pos(2*idx(p) + 1); }
        Position parent(const Position& p)		        { return pos(idx(p)/2); }
        bool hasLeft(const Position& p) const	        { return 2*idx(p) <= size(); }
        bool hasRight(const Position& p) const 	        { return 2*idx(p) + 1 <= size(); }
        bool isRoot(const Position& p) const	        { return idx(p) == 1; }
        Position root()				                    { return pos(1); }
        Position last()				                    { return pos(size()); }
        void addLast(const E& e)			            { V.push_back(e); }
        void removeLast()				                { V.pop_back(); }
        void swap(const Position& p, const Position& q) { E e = *q; *q = *p; *p = e; }
    protected:					// protected utility functions
        Position pos(int i)		                        { return V.begin() + i; } // map an index to a position
        int idx(const Position& p) const                { return p - V.begin(); } // map a position to an index
};

#endif // VECTOR_COMPLETE_TREE_HPP
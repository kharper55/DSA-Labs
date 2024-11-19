#ifndef D_NODE_HPP
#define D_NODE_HPP

// Forward declaration of DLinkedList template
template <typename Elem>
class DLinkedList;

template <typename Elem>		// list element type
class DNode {					// doubly linked list node

    public:
        // Constructor
        DNode(const Elem& e = Elem(), DNode* p = nullptr, DNode* n = nullptr)
           : elem(e), prev(p), next(n) {}
    
    private:
        Elem elem;					    // node element value
        DNode<Elem>* prev;				// previous node in list
        DNode<Elem>* next;				// next node in list
        friend class DLinkedList<Elem>;	// allow DLinkedList access
};

#endif // D_NODE_HPP
#ifndef D_NODE_HPP
#define D_NODE_HPP

// Forward declaration of DLinkedList template
template <typename Elem>
class DLinkedList;

// Forward declaration of TextEditor template
template <typename Elem>
class TextEditor;

template <typename Elem>		// list element type
class DNode {					// doubly linked list node

    friend class DLinkedList<Elem>;	// allow DLinkedList access
    friend class TextEditor<Elem>;	// allow TextEditor access

    public:
        // Constructor
        DNode(const Elem& e = Elem(), DNode* p = nullptr, DNode* n = nullptr)
           : elem(e), prev(p), next(n) {}
    
    protected:
        Elem elem;					    // node element value
        DNode<Elem>* prev;				// previous node in list
        DNode<Elem>* next;				// next node in list
};

#endif // D_NODE_HPP
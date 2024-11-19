#ifndef S_NODE_HPP
#define S_NODE_HPP

// Forward declaration of Singly Linked List template
template <typename Elem>
class SLinkedList;

template <typename E>
class SNode {					// singly linked list node
    public:
        // Constructor
        SNode(const E& e = E(), SNode* n = nullptr) : elem(e), next(n) {}
    private:
        E elem;					     // linked list element value
        SNode<E>* next;				 // next item in the list
        friend class SLinkedList<E>; // provide SLinkedList access
};
  
#endif // S_NODE_HPP
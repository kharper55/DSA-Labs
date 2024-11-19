
#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include "SLinkedList.hpp"
#include "StackExceptions.hpp" // for stack empty exception

template <typename E>
class LinkedStack {				// stack as a linked list
    public:
        LinkedStack();				// constructor
        int size() const;				// number of items in the stack
        bool empty() const;				// is the stack empty?
        const E& top() const /*throw(StackEmpty)*/;	// the top element
        void push(const E& e);  			// push element onto stack
        void pop() /*throw(StackEmpty)*/;		// pop the stack
    private:                                	// member data
        SLinkedList<E> S;			// linked list of elements
        int n;					// number of elements
};

template <typename E>
LinkedStack<E>::LinkedStack(): S(), n(0) { } // constructor

template <typename E>
int LinkedStack<E>::size() const { // number of items in the stack
    return n; 
}				

template <typename E>
bool LinkedStack<E>::empty() const { // is the stack empty?
    return n == 0; 
}		

template <typename E>
const E& LinkedStack<E>::top() const /*throw(StackEmpty)*/ { // get the top element	
    if (empty()) throw StackEmpty("Top of empty stack");
    return S.front();
}

template <typename E>
void LinkedStack<E>::push(const E& e) {	// push element onto stack
    ++n;
    S.addFront(e);
}
                    
template <typename E>
void LinkedStack<E>::pop() /*throw(StackEmpty)*/ { // pop the stack
if (empty()) throw StackEmpty("Pop from empty stack");
    --n;
    S.removeFront();
}

#endif // LINKED_STACK_HPP
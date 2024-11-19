#ifndef ARRAY_STACK_HPP
#define ARRAY_STACK_HPP

#include "arrayStackExceptions.hpp"

template <typename E>
class ArrayStack {
    const static int DEF_CAPACITY = 125;		     // default stack capacity

    public:
        ArrayStack(int cap = DEF_CAPACITY);  // constructor from capacity
        //~ArrayStack();                       // Destructor to clean up
        int size() const;				     // number of items in the stack
        bool empty() const;				     // is the stack empty?
        const E& top() const /*throw(StackEmpty)*/;	// get the top element
        void push(const E& e) /*throw(StackFull)*/;	// push element onto stack
        void pop() /*throw(StackEmpty)*/;		// pop the stack
        int getCapacity() const;
        void emptyStack();                   // Remove all items from stack
        void printStack();                   // Print stack to console from top to bottom
    private:                                 // member data
        E* S;					             // array of stack elements
        int capacity;				         // stack capacity
        int t;					             // index of the top of the stack
};

// Constructor
template <typename E> 
ArrayStack<E>::ArrayStack(int cap)
: S(new E[cap]), capacity(cap), t(-1) { }	// constructor from capacity

// Destructor
/*
template <typename E>
ArrayStack<E>::~ArrayStack() {
    delete[] S; // Free the dynamically allocated array
}*/

template <typename E>				// push element onto the stack
void ArrayStack<E>::push(const E& e) /*throw(StackFull)*/ {
    if (size() == capacity) throw StackFull("Push to full stack");
    S[++t] = e;
}
  
template <typename E>				// pop the stack
void ArrayStack<E>::pop() /*throw(StackEmpty)*/ {
    if (empty()) throw StackEmpty("Pop from empty stack");
    --t;
}
  
template <typename E> 
int ArrayStack<E>::size() const
{ return (t + 1); }				// number of items in the stack

template <typename E> 
bool ArrayStack<E>::empty() const
{ return (t < 0); }				// is the stack empty?

template <typename E>				// return top of stack
const E& ArrayStack<E>::top() const /*throw(StackEmpty)*/ {		
    if (empty()) throw StackEmpty("Top of empty stack");
    return S[t];
}

template <typename E>				// return top of stack
int ArrayStack<E>::getCapacity() const /*throw(StackEmpty)*/ {		
    return capacity;
}

// return top of stack
template <typename E>	
void ArrayStack<E>::emptyStack() /*throw(StackEmpty)*/ {		
    while(!empty()) {
        pop();
    }
}


template <typename E>
void  ArrayStack<E>::printStack() {
    /*
    ArrayStack<E> tempStack = self;
    for (int i = tempStack.size(); i > 0; i--) {
        cout << tempStack.top() << "\n";
        tempStack.pop();
    }*/

    // Copy the original stack to preserve its state
    ArrayStack<E> copy = *this; // Use the copy constructor

    // Print elements from the copied stack
    while (!copy.empty()) {
        cout << copy.top() << "\n"; // Print the top element
        copy.pop();                 // Remove from the copied stack
    }
}

#endif // ARRAY_STACK_HPP
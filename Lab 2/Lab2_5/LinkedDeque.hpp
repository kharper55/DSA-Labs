#ifndef LINKED_DEQUE_HPP
#define LINKED_DEQUE_HPP

#include "DLinkedList.hpp"
#include "DequeExceptions.hpp"

template <typename Elem>
class LinkedDeque {				// deque as doubly linked list
    public:
        LinkedDeque();				// constructor
        int size() const;				// number of items in the deque
        bool empty() const;				// is the deque empty?
        const Elem& front() const /*throw(DequeEmpty)*/; // the first element
        const Elem& back() const /*throw(DequeEmpty)*/;	// the last element
        void insertFront(const Elem& e);		// insert new first element
        void insertBack(const Elem& e);		// insert new last element
        void removeFront() /*throw(DequeEmpty)*/;	// remove first element
        void removeBack() /*throw(DequeEmpty)*/;	// remove last element
        void printDeque();
    private:					// member data
        DLinkedList<Elem> D;				// linked list of elements
        int n;					// number of elements
};

template <typename Elem>
LinkedDeque<Elem>::LinkedDeque() : D(), n(0) { }	 // constructor

// Get size of deque
template <typename Elem>
int LinkedDeque<Elem>::size() const {
    return (n);
}

// Is deque empty?
template <typename Elem>
bool LinkedDeque<Elem>::empty() const {
    return (n == 0);
}

// Return front element
template <typename Elem>
const Elem& LinkedDeque<Elem>::front() const {
    if(empty()) throw DequeEmpty("Front of empty deque");
    return D.front();
}

// Return back element
template <typename Elem>
const Elem& LinkedDeque<Elem>::back() const {
    if(empty()) throw DequeEmpty("Back of empty deque");
    return D.back();
}

// insert new first element
template <typename Elem>
void LinkedDeque<Elem>::insertFront(const Elem& e) {
    D.addFront(e);
    n++;
}

// insert new last element
template <typename Elem>
void LinkedDeque<Elem>::insertBack(const Elem& e) {
    D.addBack(e);
    n++;
}

// remove first element
template <typename Elem>
void LinkedDeque<Elem>::removeFront() /*throw(DequeEmpty)*/ {
    if (empty()) throw DequeEmpty("removeFront of empty deque");
    D.removeFront();
    n--;
}

// remove last element
template <typename Elem>
void LinkedDeque<Elem>::removeBack() /*throw(DequeEmpty)*/  {
    if (empty()) throw DequeEmpty("removeBack of empty deque");
    D.removeBack();
    n--;
}

// Print deque from front to back
template <typename Elem>
void LinkedDeque<Elem>::printDeque() /*throw(DequeEmpty)*/  {
    cout << "\n";
    if (empty()) cout << "Deque is empty.";
    else D.printList();
}

#endif // LINKED_DEQUE_HPP
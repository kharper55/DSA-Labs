#ifndef D_LINKED_LIST_HPP
#define D_LINKED_LIST_HPP

#include "DNode.hpp"
#include "LinkedListExceptions.hpp"

template <typename Elem>
class DLinkedList {				       // doubly linked list
    public:
        DLinkedList();				   // constructor
        DLinkedList(const DLinkedList<Elem>& other); // copy constructor
        DLinkedList<Elem>& operator=(const DLinkedList<Elem>& other); // operator overload
        ~DLinkedList();				   // destructor
        bool empty() const;			   // is list empty?
        const Elem& front() const;	   // get front element
        const Elem& back() const;	   // get back element
        void addFront(const Elem& e);  // add to front of list
        void addBack(const Elem& e);   // add to back of list
        void removeFront();			   // remove from front
        void removeBack();			   // remove from back
        int getSize() const;           // get size of list
        //DNode<Elem>* findNode(const Elem& value);  // find first occurence of a node by value
        //void add(DNode<Elem>* v, const Elem& e); // insert new node before v
        //bool remove(DNode<Elem>* v);   // remove node v
        void printList() const;        // print the contents of the list
    private:					       // local type definitions
        DNode<Elem>* header;		   // list sentinels
        DNode<Elem>* trailer;
        int size;                      // list size
    protected:					       // local utilities
        void add(DNode<Elem>* v, const Elem& e); // insert new node before v
        void remove(DNode<Elem>* v);   // remove node v
};

template <typename Elem>
DLinkedList<Elem>::DLinkedList() {	 // constructor
    header = new DNode<Elem>;		 // create sentinels
    trailer = new DNode<Elem>;
    header->next = trailer;			 // have them point to each other
    trailer->prev = header;
    size = 0;
}

template <typename Elem>
DLinkedList<Elem>::DLinkedList(const DLinkedList<Elem>& other) : size(0) {
    header = new DNode<Elem>();  // Create header sentinel
    trailer = new DNode<Elem>(); // Create trailer sentinel
    header->next = trailer;      // Link header to trailer
    trailer->prev = header;

    DNode<Elem>* current = other.header->next; // Start from the first real node
    while (current != other.trailer) {
        addBack(current->elem);  // Use the addBack method to maintain order
        current = current->next; // Move to the next node
    }
}

template <typename Elem>
DLinkedList<Elem>& DLinkedList<Elem>::operator=(const DLinkedList<Elem>& other) {
    if (this != &other) { // Check for self-assignment
        // Clear current list
        while (!empty()) {
            removeFront();
        }
        
        // Copy other list
        DNode<Elem>* current = other.header->next;
        while (current != other.trailer) {
            addBack(current->elem);
            current = current->next;
        }
    }
    return *this;
}

template <typename Elem>
DLinkedList<Elem>::~DLinkedList() {	 // destructor
    while (!empty()) removeFront();  // remove all but sentinels
    delete header;				     // remove the sentinels
    delete trailer;
}

// remove node v, exceptions handled in specific calls to removeFront or removeBack which invoke this method
template <typename Elem>
void DLinkedList<Elem>::remove(DNode<Elem>* v) {
    DNode<Elem>* u = v->prev;				// predecessor
    DNode<Elem>* w = v->next;				// successor
    u->next = w;				            // unlink v from list
    w->prev = u;
    delete v;
    size--;
}

template <typename Elem>
void DLinkedList<Elem>::add(DNode<Elem>* v, const Elem& e) {
    DNode<Elem>* u = new DNode<Elem>(e); // Create and initialize the new node
    u->next = v;                         // Link the new node to v
    u->prev = v->prev;                   // Link to the previous node of v
    v->prev->next = u;                   // Link the previous node of v to the new node
    v->prev = u;                         // Update v's previous to the new node
    size++;
}

// add to front of list
template <typename Elem>
void DLinkedList<Elem>::addFront(const Elem& e)	{ 
    add(header->next, e); 
}

/*
template <typename Elem>
void DLinkedList<Elem>::addFront(const Elem& e) {
    DNode<Elem>* newNode = new DNode<Elem>(e); // Create new node
    newNode->next = header->next; // Link new node to the first actual node
    newNode->prev = header; // Link new node back to header
    header->next->prev = newNode; // Update the next node's previous link
    header->next = newNode; // Link header to the new node
    // Update size if you have a size member
}*/

// add to back of list
template <typename Elem>
void DLinkedList<Elem>::addBack(const Elem& e) { 
    add(trailer, e); 
}

// remove from front
template <typename Elem>
void DLinkedList<Elem>::removeFront() { 
    if (!empty()) {
        remove(header->next); 
    }
    else throw LinkedListEmpty("Removal from empty doubly linked list");
}

// remove from back
template <typename Elem>  
void DLinkedList<Elem>::removeBack() { 
    if (!empty()) {
        remove(trailer->prev); 
    }
    else throw LinkedListEmpty("Removal from empty doubly linked list");
}

// is list empty?
template <typename Elem>
bool DLinkedList<Elem>::empty() const { 
    return (header->next == trailer); 
}

// get front element
template <typename Elem>
const Elem& DLinkedList<Elem>::front() const { 
    if (!empty()) {
        return header->next->elem;
    }
    else throw LinkedListEmpty("Front of empty doubly linked list");
}

// get back element
template <typename Elem>
const Elem& DLinkedList<Elem>::back() const	{ 
    if (!empty()) {
        return trailer->prev->elem; 
    }
    else throw LinkedListEmpty("Back of empty doubly linked list");
}

// get size of list
template <typename Elem>
int DLinkedList<Elem>::getSize() const {
    return size;
}

/*
template <typename Elem>
DNode<Elem>* DLinkedList<Elem>::findNode(const Elem& value) {
    DNode<Elem>* current = header->next; // Start from the first actual node

    // Traverse the list until we reach the trailer
    while (current != trailer) {
        if (current->elem == value) {
            return current; // Node found
        }
        current = current->next; // Move to the next node
    }

    return nullptr; // Node not found
}
*/

// print list contents
template <typename Elem>
void DLinkedList<Elem>::printList() const {
    if (empty()) {
        cout << "List is empty.\n";
        return;
    }
    DNode<Elem>* current = header->next; // Start from the first element
    while (current != trailer) {         // Stop at the trailer sentinel
        cout << current->elem << "\n";    // Print the element
        current = current->next;         // Move to the next node
    }
    cout << "\n";                        // Print a newline at the end
}

#endif // D_LINKED_LIST_HPP
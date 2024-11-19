#ifndef S_LINKED_LIST_HPP
#define S_LINKED_LIST_HPP

#include "SNode.hpp"
#include "LinkedListExceptions.hpp"

template <typename E>
class SLinkedList {				    // a singly linked list
    public:
        SLinkedList();				// empty list constructor
        ~SLinkedList();				// destructor
        SLinkedList(const SLinkedList& other); // copy constructor
        SLinkedList& operator=(const SLinkedList& other); // assignment operator
        bool empty() const;			// is list empty?
        const E& front() const;	    // return front element
        void addFront(const E& e);	// add to front of list
        void addBack(const E& e);   // add to back of list
        //void removeBack();        // Not efficient so not implemented
        void removeFront();			// remove front item list
        int getSize() const;        // get size of the list
        void printList() const;     // print the contents of the list
    private:
        SNode<E>* head;				// head of the list
        int size;
};

// constructor
template <typename E>
SLinkedList<E>::SLinkedList() : head(NULL) {
    size = 0;
}

// destructor
template <typename E>
SLinkedList<E>::~SLinkedList() { 
    while (!empty()) removeFront(); 
}

// copy constructor
template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList& other) : head(nullptr), size(0) {
    if (!other.head) return; // If the other list is empty, do nothing

    SNode<E>* current = other.head; // Pointer to traverse the source list
    while (current) {
        addBack(current->elem); // Add each element to the back of the new list
        current = current->next; // Move to the next node in the source list
    }
}

// assignment operator overload
template <typename E>
SLinkedList<E>& SLinkedList<E>::operator=(const SLinkedList& other) {
    if (this != &other) { // Self-assignment check
        while (!empty()) {
            removeFront(); // Remove nodes one by one from the front
        }    // Clear the current list to avoid memory leaks

        // Copy elements from the other list
        SNode<E>* current = other.head;
        while (current) {
            addBack(current->elem);
            current = current->next;
        }
    }
    return *this;
}

// is list empty?
template <typename E>
bool SLinkedList<E>::empty() const { 
    return head == NULL; 
}

// return front element
template <typename E>
const E& SLinkedList<E>::front() const { 
    if (!empty()) return head->elem; 
    else throw(LinkedListEmpty("Front of empty singularly linked list"));
}

// add to front of list
template <typename E>
void SLinkedList<E>::addFront(const E& e) {		
    SNode<E>* v = new SNode<E>;				// create new node
    v->elem = e;					// store data
    v->next = head;					// head now follows v
    head = v;						// v is now the head
    size++;
}

// add to back of list
template <typename E>
void SLinkedList<E>::addBack(const E& e) {
    SNode<E>* newNode = new SNode<E>(e); // Create a new node
    newNode->next = nullptr;              // Set next to nullptr (new end of list)

    if (empty()) {                        // If the list is empty
        head = newNode;                   // The new node is now the head
    } else {
        SNode<E>* current = head;         // Start at the head
        while (current->next) {           // Traverse to the last node
            current = current->next;
        }
        current->next = newNode;          // Link the last node to the new node
    }
    size++;
}

// remove front item
template <typename E>
void SLinkedList<E>::removeFront() {			
    if (!empty()) {
        SNode<E>* old = head;				// save current head
        head = old->next;					// skip over old head
        delete old;						// delete the old head
        size--;
    }
    else throw(LinkedListEmpty("Removal from empty singularly linked list"));
}

// Size method without a count member
template <typename E>
int SLinkedList<E>::getSize() const {
    return size; // Return the total size
}

// print list contents
template <typename E>
void SLinkedList<E>::printList() const {
    if (empty()) {
        cout << "List is empty.\n";
        return;
    }
    SNode<E>* current = head; // Start from the head
    while (current != nullptr) { // Traverse until the end of the list
        cout << current->elem << " "; // Print the current element
        current = current->next; // Move to the next node
    }
    cout << "\n"; // Print a newline at the end
}

#endif // S_LINKED_LIST_HPP
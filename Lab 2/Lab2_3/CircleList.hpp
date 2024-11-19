#ifndef C_LINKED_LIST_HPP
#define C_LINKED_LIST_HPP

#include "CNode.hpp"
#include "LinkedListExceptions.hpp"

template <typename Elem>
class CircleList {				      // a circularly linked list, singly linked
    public:
        CircleList();				  // constructor
        ~CircleList();				  // destructor
        CircleList(const CircleList& other); // copy constructor
        CircleList& operator=(const CircleList& other); // assignment operator overload
        bool empty() const;		      // is list empty?
        /*const*/ Elem& front() /*const*/;	  // element following cursor
        const Elem& back() const;	  // element at cursor 
        void advance();				  // advance cursor
        void addFront(const Elem& e); // add after cursor
        void addBack(const Elem& e);  // new cursor
        void removeFront();			  // remove node after cursor
        int getSize() const;          // get size
        void printList() const;       // print the contents of the list
        //CNode<Elem>* findNode(const Elem& value); // find first occurrence of node according to passed value
    private:
        CNode<Elem>* cursor;		  // the cursor node
        int size;                     // size of list
    protected:    
        bool remove(CNode<Elem>* v);  // remove specific node
};

// constructor
template <typename Elem>
CircleList<Elem>::CircleList() : cursor(NULL) { 
    size = 0;
}

// destructor
template <typename Elem>
CircleList<Elem>::~CircleList()	{ 
    while (!empty()) removeFront(); 
}

// copy constructor
template <typename Elem>
CircleList<Elem>::CircleList(const CircleList& other) : cursor(nullptr), size(0) {
    if (other.empty()) return; // If the other list is empty, do nothing

    CNode<Elem>* current = other.cursor; // Start at the cursor of the other list
    do {
        addBack(current->elem);          // Copy each element to the new list
        current = current->next;         // Move to the next node
    } while (current != other.cursor);   // Continue until we've looped back to the start

    // Set cursor to the same position as in the other list
    cursor = (size > 0) ? this->cursor : nullptr; // Assuming head points to the first node in the new list
}

// assignment operator overload
template <typename Elem>
CircleList<Elem>& CircleList<Elem>::operator=(const CircleList& other) {
    if (this != &other) { // Self-assignment check
        // Clear the current list
        while (!empty()) {
            removeFront(); 
        }

        // Copy elements from the other list
        CNode<Elem>* current = other.cursor;
        if (other.empty()) return *this; // Handle the empty case

        do {
            //current = current->next;
            addBack(current->elem); // Add elements from the other list
            current = current->next;
        } while (current != other.cursor);

        // Set the cursor to the same position (needed to set past the cursor for some reason)
        cursor = (size > 0) ? this->cursor->next : nullptr; // Assuming head points to the first node in the new list
    }
    return *this;
}

// Add element at the front of the list
template <typename Elem>
void CircleList<Elem>::addFront(const Elem& e) {		
    CNode<Elem>* v = new CNode<Elem>(); // Create a new node
    v->elem = e;

    if (cursor == nullptr) { // List is empty
        v->next = v; // Point to itself
        cursor = v;  // Cursor points to the new node
    } else { // List is non-empty
        v->next = cursor->next; // New node points to the first node
        cursor->next = v;       // Cursor now points to the new node
    }
    size++; // Increment size
}

// Add element at the back of the list
template <typename Elem>
void CircleList<Elem>::addBack(const Elem& e) {		
    CNode<Elem>* v = new CNode<Elem>(); // Create a new node
    v->elem = e;

    if (cursor == nullptr) { // List is empty
        v->next = v; // Point to itself
        cursor = v;  // Cursor points to the new node
    } else { // List is non-empty
        v->next = cursor->next; // New node points to the first node
        cursor->next = v;       // Current last node points to the new node
        cursor = v;             // Update cursor to point to the new last node
    }
    size++; // Increment size
}

// remove node after cursor
template <typename Elem>
void CircleList<Elem>::removeFront() {			
    if (!empty()) {
        CNode<Elem>* old = cursor->next; // the node being removed
        if (old == cursor) 				 // removing the only node?
            cursor = NULL;				 // list is now empty
        else 
            cursor->next = old->next;	 // link out the old node 
        delete old;					     // delete the old node
        size--;
    } 
    else throw(LinkedListEmpty("Removal from empty circular linked list"));
}

// is list empty?
template <typename Elem>
bool CircleList<Elem>::empty() const { 
    return cursor == NULL; 
}

// element at cursor
template <typename Elem>
const Elem& CircleList<Elem>::back() const { 
    if (!empty()) return cursor->elem; 
    else throw(LinkedListEmpty("Back of empty circular linked  list"));  
}

// element following cursor
template <typename Elem>
/*const*/ Elem& CircleList<Elem>::front() /*const*/	{ 
    if (!empty()) return cursor->next->elem; 
    else throw(LinkedListEmpty("Front of empty circular linked list"));  
}

// advance cursor
template <typename Elem>
void CircleList<Elem>::advance() { 
    if (!empty()) cursor = cursor->next; 
    else throw(LinkedListEmpty("Advance cursor of empty circular linked list"));   
}

// get size of circular linked list
template <typename Elem>
int CircleList<Elem>::getSize() const {
    return size;
}

/*
// find first occurrence of node according to passed value
template <typename Elem>
CNode<Elem>* CircleList<Elem>::findNode(const Elem& value) {
    if (empty()) return nullptr;   // Return nullptr if the list is empty

    CNode<Elem>* current = cursor; // Start from the cursor
    do {
        if (current->elem == value) {
            return current;        // Return the node if found
        }
        current = current->next;   // Move to the next node
    } while (current != cursor);   // Loop until we return to the cursor

    return nullptr; // Return nullptr if not found
}
*/

// remove a specific node
template <typename Elem>
bool CircleList<Elem>::remove(CNode<Elem>* v) {
    if (v == nullptr || empty()) return false; // Check for null pointer and empty list

    // If v is the only node in the list
    if (v->next == v) {
        cursor = nullptr; // Set cursor to null, list will be empty
        delete v;         // Delete the only node
        return true;
    } 
    else {
        // Find the node just before v (the predecessor)
        CNode<Elem>* u = cursor; // Start from the cursor
        do {
            if (u->next == v) { // Check if the next node is v
                // Unlink v from the list
                u->next = v->next; // Bypass v
                if (v == cursor) {
                    cursor = u; // Update cursor if we are removing the current cursor
                }
                delete v;    // Delete the node
                return true; // Successfully removed
            }
            u = u->next; // Move to the next node
        } while (u != cursor); // Loop until we've gone around the list
    }

    return false; // Node v was not found in the list
}

// print list contents
template <typename Elem>
void CircleList<Elem>::printList() const {
    if (empty()) {
        cout << "List is empty.\n";
        return;
    }

    CNode<Elem>* current = cursor->next; // Start from the element past the cursor
    do {
        cout << current->elem << "\n";    // Print the current element
        current = current->next;         // Move to the next node
    } while (current != cursor->next);   // Stop when we circle back to the cursor

    cout << "\n"; // Print a newline at the end
}

#endif // C_LINKED_LIST_HPP
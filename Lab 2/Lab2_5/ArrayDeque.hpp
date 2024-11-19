#ifndef ARRAY_DEQUE_HPP
#define ARRAY_DEQUE_HPP

#include "DequeExceptions.hpp"
#include "ArrayDequeExceptions.hpp"

template <typename Elem>
class ArrayDeque {				// deque as array
    const static int DEF_CAPACITY = 100;		     // default queue capacity
    public:
        ArrayDeque(int cap = DEF_CAPACITY);				// constructor
        ArrayDeque(const ArrayDeque<Elem>& other); // copy constructor
        ArrayDeque<Elem>& operator=(const ArrayDeque<Elem>& other); // copy assignment operator
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
        Elem *arr;		        // array of elements
        int capacity;		    // stack capacity
        int n;					// number of elements
        int f;                  // front pointer
        int r;                  // rear pointer
};

// Constructor
template <typename Elem> 
ArrayDeque<Elem>::ArrayDeque(int cap): arr(new Elem[cap]), capacity(cap), n(0), f(0), r(0) { }

// Copy Constructor
template <typename Elem>
ArrayDeque<Elem>::ArrayDeque(const ArrayDeque<Elem>& other)
    : capacity(other.capacity), n(other.n), f(other.f), r(other.r) {
    // Allocate new array for the copy
    arr = new Elem[capacity];

    // Copy the elements from the other queue
    for (int i = 0; i < n; i++) {
        arr[(f + i) % capacity] = other.arr[(other.f + i) % other.capacity];
    }
}

// Copy Assignment Operator
template <typename Elem>
ArrayDeque<Elem>& ArrayDeque<Elem>::operator=(const ArrayDeque<Elem>& other) {
    if (this != &other) { // Check for self-assignment
        delete[] arr; // Free existing resource

        // Copy data from the other queue
        capacity = other.capacity;
        n = other.n;
        f = other.f;
        r = other.r;
        arr = new Elem[capacity];

        for (int i = 0; i < n; i++) {
            arr[(f + i) % capacity] = other.arr[(other.f + i) % other.capacity];
        }
    }
    return *this; // Return the current object
}

// Get number of elements in deque
template <typename Elem> 
int ArrayDeque<Elem>::size() const {
    return n;
}

// Is deque empty?
template <typename Elem> 
bool ArrayDeque<Elem>::empty() const {
    return (n == 0);
}

// Get number of elements in deque
template <typename Elem> 
const Elem& ArrayDeque<Elem>::front() const {
    if (empty()) throw DequeEmpty("Front of empty deque");
    return (arr[f]);
}

// Get number of elements in deque
template <typename Elem> 
const Elem& ArrayDeque<Elem>::back() const {
    if (empty()) throw DequeEmpty("Back of empty deque");
    return (arr[(r - 1 + capacity) % capacity]);
}

// Enqueue to rear
template <typename Elem>
void ArrayDeque<Elem>::insertBack(const Elem& e) {
    if (size() == capacity) throw DequeFull("Enqueue to full deque");
    arr[r] = e;
    r = (r + 1) % capacity;
    n++;
}

// Enqueue to front
template <typename Elem>
void ArrayDeque<Elem>::insertFront(const Elem& e) {
    if (size() == capacity) throw DequeFull("Enqueue to full deque");
    //arr[f] = e;
    f = (f - 1 + capacity) % capacity;
    arr[f] = e;
    n++;
}

// Dequeue at front
template <typename Elem>
void ArrayDeque<Elem>::removeFront() {
    if (empty()) throw DequeEmpty("Dequeue from empty deque");
    f = (f + 1) % capacity;
    n--;
}

// Dequeue at rear
template <typename Elem>
void ArrayDeque<Elem>::removeBack() {
    if (empty()) throw DequeEmpty("Dequeue from empty deque");
    r = (r - 1 + capacity) % capacity;
    n--;
}

// Print Queue contents from front to back
template <typename Elem>
void ArrayDeque<Elem>::printDeque() {
    //cout << "\n";
    if (empty()) {
        cout << "Deque is empty.";
        return;
    }
    if (f > r) {
        for (int i = f; i < capacity; i++) {
            cout << arr[i] << "\n";
        }
        for (int i = 0; i < r; i++) {
            cout << arr[i] << "\n";
        }
    }
    else {
        for (int i = f; i < r; i++) {
            cout << arr[i] << "\n";
        }
    }
}

#endif // ARRAY_DEQUE_HPP
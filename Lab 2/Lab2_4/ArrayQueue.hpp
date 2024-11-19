#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

#include "QueueExceptions.hpp"      // QueueEmpty
#include "ArrayQueueExceptions.hpp" // QueueFull

template <typename Elem>				// queue element type
class ArrayQueue {				// queue as array
    const static int DEF_CAPACITY = 20;		     // default queue capacity
    public:
        ArrayQueue(int cap = DEF_CAPACITY); // constructor
        ArrayQueue(const ArrayQueue<Elem>& other); // copy constructor
        ArrayQueue<Elem>& operator=(const ArrayQueue<Elem>& other); // copy assignment operator
        int size() const;				// number of items in the queue
        bool empty() const;				// is the queue empty?
        /*const*/ Elem& front() /*const*/ /*throw(QueueEmpty)*/; // the front element
        void enqueue(const Elem& e) /*throw(QueueFull)*/;		// enqueue element at rear
        void dequeue() /*throw(QueueEmpty)*/;		// dequeue element at front
        void printQueue();
    private:					// member data
        Elem *arr;		// circular list of elements
        int capacity;		// stack capacity
        int n;			    // number of elements
        int f;			    // index of front of queue
        int r;			    // index of rear of queue
};

// Constructor
template <typename Elem> 
ArrayQueue<Elem>::ArrayQueue(int cap): arr(new Elem[cap]), capacity(cap), n(0), f(0), r(0) { }

// Copy Constructor
template <typename Elem>
ArrayQueue<Elem>::ArrayQueue(const ArrayQueue<Elem>& other)
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
ArrayQueue<Elem>& ArrayQueue<Elem>::operator=(const ArrayQueue<Elem>& other) {
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

// Get number of elements in queue
template <typename Elem> 
int ArrayQueue<Elem>::size() const {
    return n;
}

// Determine whether queue is empty
template <typename Elem> 
bool ArrayQueue<Elem>::empty() const {
    return (n == 0);
}

// Get element at front of queue
template <typename Elem>
/*const*/ Elem& ArrayQueue<Elem>::front() /*const*/ {
    if (empty()) throw QueueEmpty("Front of empty queue");
    return arr[f];
}

// Enqueue to rear
template <typename Elem>
void ArrayQueue<Elem>::enqueue(const Elem& e) {
    if (size() == capacity) throw QueueFull("Enqueue to full queue");
    arr[r] = e;
    r = (r + 1) % capacity;
    n++;
}

// Dequeue at front
template <typename Elem>
void ArrayQueue<Elem>::dequeue() {
    if (empty()) throw QueueEmpty("Dequeue from empty queue");
    f = (f + 1) % capacity;
    n--;
}

// Print Queue contents from front to back
template <typename Elem>
void ArrayQueue<Elem>::printQueue() {
    cout << "\n";
    if (empty()) {
        cout << "Queue is empty.";
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

#endif // ARRAY_QUEUE_HPP

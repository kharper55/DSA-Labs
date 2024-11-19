#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include "CircleList.hpp"
#include "QueueExceptions.hpp"

template <typename Elem>				// queue element type
class CircularQueue {				// queue as cicular linked list
    public:
        CircularQueue();				// constructor
        int size() const;				// number of items in the queue
        bool empty() const;				// is the queue empty?
        /*const*/ Elem& front() /*const*/ /*throw(QueueEmpty)*/; // the front element
        void enqueue(const Elem& e);		// enqueue element at rear
        void dequeue() /*throw(QueueEmpty)*/;		// dequeue element at front
        void printQueue();
    private:					// member data
        CircleList<Elem> C;				// circular list of elements
        int n;					// number of elements
};

template <typename Elem>
CircularQueue<Elem>::CircularQueue(): C(), n(0) { }	// constructor


template <typename Elem>
int CircularQueue<Elem>::size() const {			// number of items in the queue
    return n; 
}

template <typename Elem>
bool CircularQueue<Elem>::empty() const {		// is the queue empty?
    return n == 0; 
}
   
template <typename Elem>                 // get the front element
/*const*/ Elem& CircularQueue<Elem>::front() /*const*/ /*throw(QueueEmpty)*/ {
    if (empty())
        throw QueueEmpty("Front of empty queue");
    return C.front();				// list front is queue front
}

// enqueue element at rear
template <typename Elem>   
void CircularQueue<Elem>::enqueue(const Elem& e) {
    C.addFront(e);					// insert after cursor
    C.advance();				// ...and advance
    n++;
}
                    // dequeue element at front
template <typename Elem>  
void CircularQueue<Elem>::dequeue() /*throw(QueueEmpty)*/ {
    if (empty())
        throw QueueEmpty("Dequeue of empty queue");
    C.removeFront();					// remove from list front
    n--;
}

template <typename Elem>  
void CircularQueue<Elem>::printQueue() {
    cout << "\n";
    if (empty()) {
        cout << "Queue is empty.";
        return;
    }
    C.printList();
}


#endif // CIRCULAR_QUEUE_HPP
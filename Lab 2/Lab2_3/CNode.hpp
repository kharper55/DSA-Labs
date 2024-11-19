#ifndef C_NODE_HPP
#define C_NODE_HPP

// Forward declaration of CircleList template
template <typename Elem>
class CircleList;

template <typename Elem> // element type
class CNode { // circularly linked list node
    public:
        CNode(const Elem& e = Elem(), CNode* n = nullptr) : elem(e), next(n) {} // constructor

    private:
        Elem elem;                     // linked list element value
        CNode<Elem>* next;             // next item in the list
        friend class CircleList<Elem>; // provide CircleList access
};

#endif // C_NODE_HPP
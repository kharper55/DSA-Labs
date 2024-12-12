#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "GraphEdgeLinked.hpp"

// Forward declarations
template <typename V, typename E>
class GraphEdgeLinked;

// Vertex object
template <typename V>
class Vertex {
    public:
        typedef std::shared_ptr<Vertex<V>> Ptr;

        explicit Vertex(const V& elem) : element(elem) {}

        const V& getElement() const { return element; }

    private:
        V element;                                // Element stored in the vertex
        typename std::list<Ptr>::iterator position;  // Position in vertex sequence
        template <typename, typename> friend class GraphEdgeLinked;  // Grant access to Graph
};

#endif // VERTEX_HPP
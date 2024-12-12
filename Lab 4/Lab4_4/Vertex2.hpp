#ifndef VERTEX_2_HPP
#define VERTEX_2_HPP

#include "GraphAdjacencyList.hpp"
#include "GraphAdjacencyMatrix.hpp"

// alternate vertex with position as integer instead of iterator
// for use with array/vector based graph structures

// Forward declarations
template <typename V, typename E>
class GraphAdjacencyMatrix;

template <typename V, typename E>
class GraphAdjacencyList;

// Vertex object
template <typename V>
class Vertex2 {
    public:
        typedef std::shared_ptr<Vertex2<V>> Ptr;

        explicit Vertex2(const V& elem) : element(elem) {}

        const V& getElement() const { return element; }

    private:
        V element;                                // Element stored in the vertex
        int position;  // Position in vertex sequence
        template <typename, typename> friend class GraphAdjacencyMatrix;
        template <typename, typename> friend class GraphAdjacencyList;
};

#endif // VERTEX_HPP
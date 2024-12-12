#ifndef EDGE_2_HPP
#define EDGE_2_HPP

#include "GraphAdjacencyList.hpp"
#include "GraphAdjacencyMatrix.hpp"

// Forward declarations
template <typename V, typename E>
class GraphAdjacencyMatrix;

template <typename V, typename E>
class GraphAdjacencyList;

template <typename V>
class Vertex2;  // Complete forward declaration of Vertex2

// Edge object
template <typename V, typename E = int>
class Edge2 {
public:
    typedef std::shared_ptr<Edge2<V, E>> Ptr;

    Edge2(typename Vertex2<V>::Ptr origin, typename Vertex2<V>::Ptr dest, const E& elem)
        : originVertex(origin), destVertex(dest), element(elem) {}

    const E& getElement() const { return element; }

    std::pair<typename Vertex2<V>::Ptr, typename Vertex2<V>::Ptr> endVertices() const {
        return std::make_pair(originVertex, destVertex);
    }

    typename Vertex2<V>::Ptr opposite(const typename Vertex2<V>::Ptr& v) const {
        return (v == originVertex) ? destVertex : originVertex;
    }

private:
    typename Vertex2<V>::Ptr originVertex;  // Origin vertex
    typename Vertex2<V>::Ptr destVertex;    // Destination vertex
    E element;                             // Element stored in the edge
    int position;                          // Position in edge sequence
    template <typename, typename> friend class GraphAdjacencyMatrix;
    template <typename, typename> friend class GraphAdjacencyList;
};

#endif // EDGE_2_HPP

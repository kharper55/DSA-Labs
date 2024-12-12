#ifndef EDGE_HPP
#define EDGE_HPP

#include "GraphEdgeLinked.hpp"

// Forward declarations
template <typename V, typename E>
class GraphEdgeLinked;

template <typename V>
class Vertex;

// Edge object
template <typename V, typename E = int>
class Edge {
    public:
        typedef std::shared_ptr<Edge<V, E>> Ptr;

        Edge(typename Vertex<V>::Ptr origin, typename Vertex<V>::Ptr dest, const E& elem)
            : originVertex(origin), destVertex(dest), element(elem) {}

        const E& getElement() const { return element; }

        std::pair<typename Vertex<V>::Ptr, typename Vertex<V>::Ptr> endVertices() const {
            return std::make_pair(originVertex, destVertex);
        }

        typename Vertex<V>::Ptr opposite(const typename Vertex<V>::Ptr& v) const {
            return (v == originVertex) ? destVertex : originVertex;
        }

    private:
        typename Vertex<V>::Ptr originVertex;  // Origin vertex
        typename Vertex<V>::Ptr destVertex;    // Destination vertex
        E element;                             // Element stored in the edge
        typename std::list<Ptr>::iterator position;  // Position in edge sequence
        template <typename, typename> friend class GraphEdgeLinked;  // Grant access to Graph
};

#endif // EDGE_HPP
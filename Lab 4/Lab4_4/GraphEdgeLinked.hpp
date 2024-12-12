#ifndef GRAPH_EDGE_LINKED_HPP
#define GRAPH_EDGE_LINKED_HPP

#include "Vertex.hpp"
#include "Edge.hpp"

template <typename V>
class Vertex;

template <typename V, typename E>
class Edge;

// Graph object
template <typename V, typename E = int>
class GraphEdgeLinked {
    public:
        typedef Vertex<V> Vertex;               // Expose the Vertex type
        typedef Edge<V, E> Edge;                // Expose the Edge type
        typedef typename Vertex::Ptr VertexPtr;
        typedef typename Edge::Ptr EdgePtr;

        // Insert a vertex
        VertexPtr insertVertex(const V& elem) {
            VertexPtr v = std::make_shared<Vertex>(elem);
            vertices.push_back(v);
            v->position = --vertices.end();
            return v;
        }

        // Insert an edge
        EdgePtr insertEdge(VertexPtr v, VertexPtr w, const E& elem) {
            EdgePtr e = std::make_shared<Edge>(v, w, elem);
            edges.push_back(e);
            e->position = --edges.end();
            return e;
        }

        // Erase a vertex
        void eraseVertex(VertexPtr v) {
            // Remove all incident edges first
            edges.remove_if([v](const EdgePtr& e) {
                return e->endVertices().first == v || e->endVertices().second == v;
            });

            // Remove vertex from the vertex list
            vertices.erase(v->position);
        }

        // Erase an edge
        void eraseEdge(EdgePtr e) {
            edges.erase(e->position);
        }

        // Get a list of all vertices
        std::list<VertexPtr> getVertices() const {
            return vertices;
        }

        // Get a list of all edges
        std::list<EdgePtr> getEdges() const {
            return edges;
        }

        // Get incident edges of a vertex 
        std::list<EdgePtr> incidentEdges(VertexPtr v) const {
            std::list<EdgePtr> result;
            typename std::list<EdgePtr>::const_iterator it;
            for (it = edges.begin(); it != edges.end(); ++it) {
                EdgePtr e = *it;
                if (e->endVertices().first == v || e->endVertices().second == v) {
                    result.push_back(e);
                }
            }
            return result;
        }

        // Check if two vertices are adjacent
        bool isAdjacent(VertexPtr u, VertexPtr v) const {
            typename std::list<EdgePtr>::const_iterator it;
            for (it = edges.begin(); it != edges.end(); ++it) {
                EdgePtr e = *it;
                if ((e->endVertices().first == u && e->endVertices().second == v) ||
                    (e->endVertices().first == v && e->endVertices().second == u)) {
                    return true;
                }
            }
            return false;
        }
        typename GraphEdgeLinked<V, E>::VertexPtr opposite(VertexPtr v, typename GraphEdgeLinked<V, E>::EdgePtr e) const {
            auto endpoints = e->endVertices();
            return (endpoints.first == v) ? endpoints.second : endpoints.first;
        }
        //template <typename G>
        //friend class DFS<G<V, E>>;

    private:
        std::list<VertexPtr> vertices;  // Sequence of vertex objects
        std::list<EdgePtr> edges;      // Sequence of edge objects
};


#endif // GRAPH_EDGE_LINKED_HPP
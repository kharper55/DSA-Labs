#ifndef GRAPH_ADJACENCY_LIST_HPP
#define GRAPH_ADJACENCY_LIST_HPP

#include "Vertex2.hpp"
#include "Edge2.hpp"
#include <vector>
#include <memory>
#include <list>

template <typename V>
class Vertex2;

template <typename V, typename E>
class Edge2;

template <typename V, typename E = int>
class GraphAdjacencyList {
public:
    typedef Vertex2<V> Vertex;               // Expose the Vertex type
    typedef Edge2<V, E> Edge;                // Expose the Edge type
    typedef typename Vertex::Ptr VertexPtr;
    typedef typename Edge::Ptr EdgePtr;

    GraphAdjacencyList() {}

    // Insert a vertex
    VertexPtr insertVertex(const V& elem) {
        VertexPtr v = std::make_shared<Vertex>(elem);
        v->position = vertices.size(); // Assign position
        vertices.push_back(v);
        adjacencyList.emplace_back(); // Add an empty edge list for the new vertex
        return v;
    }

    // Insert an edge
    EdgePtr insertEdge(VertexPtr v, VertexPtr w, const E& elem) {
        EdgePtr e = std::make_shared<Edge>(v, w, elem);
        e->position = edges.size(); // Assign position
        edges.push_back(e);

        adjacencyList[v->position].push_back(e);
        adjacencyList[w->position].push_back(e);
        return e;
    }

    // Erase a vertex
    void eraseVertex(VertexPtr v) {
        // Remove all incident edges
        for (auto& edge : adjacencyList[v->position]) {
            eraseEdge(edge);
        }

        // Remove vertex from the vertex list
        vertices.erase(vertices.begin() + v->position);

        // Adjust positions of remaining vertices
        for (size_t i = v->position; i < vertices.size(); ++i) {
            vertices[i]->position = i;
        }

        // Remove the vertex's adjacency list
        adjacencyList.erase(adjacencyList.begin() + v->position);
    }

    // Erase an edge
    void eraseEdge(EdgePtr e) {
        // Remove edge from adjacency lists
        auto endpoints = e->endVertices();
        adjacencyList[endpoints.first->position].remove(e);
        adjacencyList[endpoints.second->position].remove(e);

        // Remove edge from the edges list
        edges.erase(edges.begin() + e->position);

        // Adjust positions of remaining edges
        for (size_t i = e->position; i < edges.size(); ++i) {
            edges[i]->position = i;
        }
    }

    // Get a list of all vertices
    std::vector<VertexPtr> getVertices() const {
        return vertices;
    }

    // Get a list of all edges
    std::vector<EdgePtr> getEdges() const {
        return edges;
    }

    // Get incident edges of a vertex
    std::list<EdgePtr> incidentEdges(VertexPtr v) const {
        return adjacencyList[v->position];
    }

    // Check if two vertices are adjacent
    bool isAdjacent(VertexPtr u, VertexPtr v) const {
        for (const auto& e : adjacencyList[u->position]) {
            if (e->endVertices().first == v || e->endVertices().second == v) {
                return true;
            }
        }
        return false;
    }

    typename GraphAdjacencyList<V, E>::VertexPtr opposite(VertexPtr v, typename GraphAdjacencyList<V, E>::EdgePtr e) const {
        auto endpoints = e->endVertices();
        return (endpoints.first == v) ? endpoints.second : endpoints.first;
    }

private:
    std::vector<VertexPtr> vertices;                // Sequence of vertex objects
    std::vector<EdgePtr> edges;                     // Sequence of edge objects
    std::vector<std::list<EdgePtr>> adjacencyList;  // Adjacency list for each vertex
};

#endif // GRAPH_ADJACENCY_LIST_HPP

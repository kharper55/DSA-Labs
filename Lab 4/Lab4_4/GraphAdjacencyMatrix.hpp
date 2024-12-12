#ifndef GRAPH_ADJACENCY_MATRIX_HPP
#define GRAPH_ADJACENCY_MATRIX_HPP

#include "Vertex2.hpp"
#include "Edge2.hpp"
#include <vector>
#include <memory>
#include <algorithm> // For std::find

template <typename V>
class Vertex2;

template <typename V, typename E>
class Edge2;

template <typename V, typename E = int>
class GraphAdjacencyMatrix {
public:
    typedef Vertex2<V> Vertex;               // Expose the Vertex type
    typedef Edge2<V, E> Edge;                // Expose the Edge type
    typedef typename Vertex::Ptr VertexPtr;
    typedef typename Edge::Ptr EdgePtr;

    // Constructor
    GraphAdjacencyMatrix() : numVertices(0) {}

    // Insert a vertex
    VertexPtr insertVertex(const V& elem) {
        VertexPtr v = std::make_shared<Vertex>(elem);
        vertices.push_back(v);
        v->position = vertices.size() - 1;

        // Expand the adjacency matrix
        for (auto& row : adjacencyMatrix) {
            row.push_back(nullptr); // Add a new column to each row
        }

        // Add a new row with the correct size
        adjacencyMatrix.push_back(std::vector<EdgePtr>(vertices.size(), nullptr));

        ++numVertices;
        return v;
    }

    // Insert an edge
    EdgePtr insertEdge(VertexPtr v, VertexPtr w, const E& elem) {
        // Check if the edge already exists between the vertices
        for (const auto& existingEdge : incidentEdges(v)) {
            auto endpoints = existingEdge->endVertices();
            if ((endpoints.first == v && endpoints.second == w) || (endpoints.second == v && endpoints.first == w)) {
                // Edge already exists, return the existing edge
                return existingEdge;
            }
        }

        // Create the new edge shared pointer
        EdgePtr e = std::make_shared<Edge>(v, w, elem);

        // Boundary check on vertex positions
        if (v->position >= adjacencyMatrix.size() || w->position >= adjacencyMatrix.size() ||
            v->position >= adjacencyMatrix[w->position].size() || w->position >= adjacencyMatrix[v->position].size()) {
            std::cerr << "Error: Vertex positions are out of bounds during edge insertion." << std::endl;
            return nullptr; // Return null to indicate failure
        }

        // Update adjacency matrix with edge pointers
        adjacencyMatrix[v->position][w->position] = e;
        adjacencyMatrix[w->position][v->position] = e;

        // Add the edge to the list of edges
        edges.push_back(e);

        return e;
    }


    // Erase a vertex
    void eraseVertex(VertexPtr v) {
        // Remove all incident edges first
        for (auto& edge : incidentEdges(v)) {
            eraseEdge(edge);
        }

        // Remove vertex from the vertices list
        vertices.erase(vertices.begin() + v->position);

        // Remove the row and column from the adjacency matrix
        adjacencyMatrix.erase(adjacencyMatrix.begin() + v->position);
        for (auto& row : adjacencyMatrix) {
            row.erase(row.begin() + v->position);
        }

        --numVertices;
    }

    // Erase an edge
    void eraseEdge(EdgePtr e) {
        auto endpoints = e->endVertices();
        adjacencyMatrix[endpoints.first->position][endpoints.second->position] = nullptr;
        adjacencyMatrix[endpoints.second->position][endpoints.first->position] = nullptr;

        auto it = std::find(edges.begin(), edges.end(), e);
        if (it != edges.end()) {
            edges.erase(it);
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
        std::list<EdgePtr> result;
        for (const auto& edge : adjacencyMatrix[v->position]) {
            if (edge) {
                result.push_back(edge);
            }
        }
        return result;
    }

    // Check if two vertices are adjacent
    bool isAdjacent(VertexPtr u, VertexPtr v) const {
        return adjacencyMatrix[u->position][v->position] != nullptr;
    }

    typename GraphAdjacencyMatrix<V, E>::VertexPtr opposite(VertexPtr v, typename GraphAdjacencyMatrix<V, E>::EdgePtr e) const {
        auto endpoints = e->endVertices();
        return (endpoints.first == v) ? endpoints.second : endpoints.first;
    }

private:
    size_t numVertices;                           // Current number of vertices
    std::vector<VertexPtr> vertices;               // List of vertex objects
    std::vector<EdgePtr> edges;                    // List of edge objects
    std::vector<std::vector<EdgePtr>> adjacencyMatrix; // Adjacency matrix storing edges as a vector of vectors
};

#endif // GRAPH_ADJACENCY_MATRIX_HPP

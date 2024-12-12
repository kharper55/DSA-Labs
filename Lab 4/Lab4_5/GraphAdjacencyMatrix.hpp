#ifndef GRAPH_ADJACENCY_MATRIX_HPP
#define GRAPH_ADJACENCY_MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

template <typename V, typename E = int>
class AdjacencyMatrixGraph {
public:
    using Vertex = V;
    using Edge = E;

    // Constructor: Initialize a graph with a given number of vertices
    AdjacencyMatrixGraph(int n) : nVertices(n) {
        adjMatrix.resize(n, std::vector<Edge>(n, 0)); // 0 means no edge
        vertices.resize(n);
    }

    // Set vertex label
    void setVertex(int index, const V& label) {
        if (index < 0 || index >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        vertices[index] = label;
    }

    // Get vertex label
    const V& getVertex(int index) const {
        if (index < 0 || index >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        return vertices[index];
    }

    // Add an edge between two vertices (undirected graph)
    void addEdge(int u, int v, const E& weight = 1) {
        if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;  // Since it's an undirected graph
    }

    // Remove an edge between two vertices
    void removeEdge(int u, int v) {
        if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
    }

    // Check if there is an edge between two vertices
    bool isEdge(int u, int v) const {
        if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        return adjMatrix[u][v] != 0;
    }

    // Get the weight of the edge between two vertices
    Edge getEdgeWeight(int u, int v) const {
        if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        return adjMatrix[u][v];
    }

    // Sum of all incident edges on a vertex u
    Edge sumIncidentWeights(int u) const {
        if (u < 0 || u >= nVertices) {
            throw std::out_of_range("Vertex index out of range.");
        }
        Edge totalTransfers = 0;
        for (int i = 0; i < nVertices; ++i) {
            totalTransfers += adjMatrix[u][i];
        }
        return totalTransfers;
    }

    // Print the adjacency matrix
    void printMatrix() const {
        for (int i = 0; i < nVertices; ++i) {
            for (int j = 0; j < nVertices; ++j) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Get the number of vertices in the graph
    int getNumberOfVertices() const {
        return nVertices;
    }

private:
    int nVertices;  // Number of vertices
    std::vector<std::vector<Edge>> adjMatrix;  // Adjacency matrix
    std::vector<Vertex> vertices;  // Labels for the vertices
};

#endif // GRAPH_ADJACENCY_MATRIX_HPP
#ifndef DFS_HPP
#define DFS_HPP

#include <map>
#include <list>
#include "Vertex.hpp"
#include "Edge.hpp"

template <typename G>
class DFS {
    protected:
        typedef typename G::Vertex Vertex;              // Vertex type
        typedef typename G::Vertex::Ptr VertexPtr;      // Shared pointer to Vertex
        typedef typename G::Edge Edge;                  // Edge type
        typedef typename G::Edge::Ptr EdgePtr;          // Shared pointer to Edge
        typedef std::list<EdgePtr> EdgeList;            // List of shared pointers to Edges
        typedef std::list<VertexPtr> VertexList;        // List of shared pointers to Vertices

        const G& graph;                                 // The graph
        VertexPtr start;                                // Start vertex
        std::map<VertexPtr, bool> vertexVisited;        // Map for vertex visit status
        std::map<EdgePtr, bool> edgeVisited;            // Map for edge visit status

    public:
        DFS(const G& g, VertexPtr startVertex) : graph(g), start(startVertex) {}

        void printGraph() { std::cout << "\nDFS Traversal ({back edge}, (discovery edge)):\n"; dfsTraversal(start); }

    protected:
        void initialize() {
            for (const auto& v : graph.getVertices()) {
                vertexVisited[v] = false;
            }
            for (const auto& e : graph.getEdges()) {
                edgeVisited[e] = false;
            }
        }
        
        void dfsTraversal(VertexPtr v) {
            // Start visiting the vertex
            startVisit(v);
            markVisited(v);
            std::cout << v->getElement() << "\n";

            // Get all incident edges
            EdgeList incident = graph.incidentEdges(v);

            for (const auto& e : incident) {
                if (!isVisited(e)) {  // If the edge is not visited
                    markVisited(e);   // Mark the edge as visited
                    auto endpoints = e->endVertices();

                    // Find the opposite vertex
                    VertexPtr w = e->opposite(v);

                    if (!isVisited(w)) {  // If the opposite vertex is unexplored
                        traverseDiscovery(e, v);
                        std::cout << "(" << endpoints.first->getElement()
                                << " -- " << endpoints.second->getElement() << ")\n";
                        dfsTraversal(w);  // Continue DFS from the opposite vertex
                    } else {
                        traverseBack(e, v);
                        std::cout << "{" << endpoints.second->getElement()
                                << " -- " << endpoints.first->getElement() << "}\n";
                    }
                }
            }

            finishVisit(v);  // Finish visiting the vertex
        }

        virtual void startVisit(VertexPtr v) {}         // Arrived at v
        virtual void traverseDiscovery(EdgePtr e, VertexPtr from) {}  // Discovery edge e
        virtual void traverseBack(EdgePtr e, VertexPtr from) {}       // Back edge e
        virtual void finishVisit(VertexPtr v) {}       // Finished with v
        virtual bool isDone() const { return false; }  // Finished?

        void markVisited(VertexPtr v) { vertexVisited[v] = true; }
        void markVisited(EdgePtr e) { edgeVisited[e] = true; }
        bool isVisited(VertexPtr v) const { return vertexVisited.count(v) && vertexVisited.at(v); }
        bool isVisited(EdgePtr e) const { return edgeVisited.count(e) && edgeVisited.at(e); }
};

#endif  // DFS_HPP

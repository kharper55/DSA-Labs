#ifndef BFS_HPP
#define BFS_HPP

#include <map>
#include <list>
#include <queue>
#include <iostream>
#include "Vertex.hpp"
#include "Edge.hpp"

template <typename G>
class BFS {
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
        BFS(const G& g, VertexPtr startVertex) : graph(g), start(startVertex) {}

        void printGraph() { std::cout << "\nBFS Traversal ({cross edge}, (discovery edge)):\n"; bfsTraversal(start); }

    protected:
        void initialize() {
            for (const auto& v : graph.getVertices()) {
                vertexVisited[v] = false;
            }
            for (const auto& e : graph.getEdges()) {
                edgeVisited[e] = false;
            }
        }
        
        void bfsTraversal(VertexPtr v) {
            std::queue<VertexPtr> q;

            // Process the starting vertex
            startVisit(v);
            markVisited(v);
            std::cout << v->getElement() << "\n";
            q.push(v);


            while (!q.empty()) {
                VertexPtr u = q.front();
                q.pop();

                EdgeList incident = graph.incidentEdges(u);

                for (const auto& e : incident) {
                    auto endpoints = e->endVertices();

                    // Find the opposite vertex
                    VertexPtr w = e->opposite(u);

                    if (!isVisited(e)) {  // If the edge is not visited
                        markVisited(e);

                        if (!isVisited(w)) {  // If the opposite vertex is unexplored
                            traverseDiscovery(e, u);
                            std::cout << "(" << endpoints.first->getElement()
                                    << " -- " << endpoints.second->getElement() << ")\n";
                            markVisited(w);  // Mark the vertex as visited when a discovery edge is traversed
                            std::cout << w->getElement() << "\n";
                            q.push(w);  // Add to queue for BFS
                        } else {
                            traverseCross(e, u);
                            std::cout << "{" << endpoints.first->getElement()
                                    << " -- " << endpoints.second->getElement() << "}\n";
                        }
                    }
                }
            }

            finishVisit(v);  // Finish visiting the vertex
        }

        virtual void startVisit(VertexPtr v) {}         // Arrived at v
        virtual void traverseDiscovery(EdgePtr e, VertexPtr from) {}  // Discovery edge e
        virtual void traverseCross(EdgePtr e, VertexPtr from) {}       // Cross edge e
        virtual void finishVisit(VertexPtr v) {}       // Finished with v
        virtual bool isDone() const { return false; }  // Finished?

        void markVisited(VertexPtr v) { vertexVisited[v] = true; }
        void markVisited(EdgePtr e) { edgeVisited[e] = true; }
        bool isVisited(VertexPtr v) const { return vertexVisited.count(v) && vertexVisited.at(v); }
        bool isVisited(EdgePtr e) const { return edgeVisited.count(e) && edgeVisited.at(e); }
};

#endif  // BFS_HPP

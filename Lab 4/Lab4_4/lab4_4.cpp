/* ============================================================================
lab1_5.cpp

This program demonstrates concatenation for various list data structures.

Desc:   Lab 1 for datastructures and algorithms (CSCI2226)
Author: Kevin Harper
Date:   10/20/2024

NOTE: IN VSCODE, IF GDB IS THROWING ERROR 0xC0000139 DESPITE THE PROGRAM 
      SUCCESSFULLY BUILDING, YOU MUST GO TO SETTINGS AND CHANGE THE TERMINAL. 
      IN THE TERMINAL WINDOW, NAVIGATE TO THE "+" ICON WITH THE DROPDOWN ARROW,
      THEN SELECT CONFIGURE TERMINAL SETTINGS, NAVIGATE TO C:\msys64\ucrt64.exe 
      (FOR DEFAULT MSYS2 INSTALL SETTINGS) AND USE THIS EXECUTABLE PATH IN THE 
      SETTINGS WINDOW. THEN USE THE BUTTON ON THE BOTTOM OF THE VSCODE SCREEN
      "C/C++: g++.exe build and debug active file (PROJ_NAME)" TO BUILD AND
      DEBUG THE FILE IN THE NATIVE VSCODE TERMINAL.

============================================================================ */

// Library includes
#include <iostream>      // For console interaction
#include <cstring>       // For stringlen
#include <list>
#include <string>
#include <memory>
#include <utility>

// Header includes
#include "GraphEdgeLinked.hpp"
#include "GraphAdjacencyList.hpp"
#include "GraphAdjacencyMatrix.hpp"
#include "DFS.hpp"
#include "BFS.hpp"

// Prototypes
void printCenteredTitle(const char * title, const char buffChar, const int col_width);

// Globals

using namespace std;

#define COL_WIDTH       65

/*
Assume the input as the complete graph with 5 vertices (K5). Store K5 using each
representation of Graphs as listed below. The output is a list of vertices of K5 in the order
visited first by DFS traversal and then by BFS traversal, starting from the same vertex and
assuming increasing order preference. Compare the order of vertices ordered by each of
the traversals. Submit a writeup, screenshots of the results, and code files in a zip file.
a. edge-linked graph representation
b. adjacency list graph representation
c. adjacency matrix graph representation
*/

// Test the Graph
int main() {

    cout << "Welcome to Graph Traversal Demo!\n";

    GraphEdgeLinked<std::string, int> graph;
    GraphAdjacencyMatrix<std::string, int> graph2;
    GraphAdjacencyList<std::string, int> graph3;

    // Create edge-linked complete graph
    auto v1 = graph.insertVertex("A");
    auto v2 = graph.insertVertex("B");
    auto v3 = graph.insertVertex("C");
    auto v4 = graph.insertVertex("D");
    auto v5 = graph.insertVertex("E");
    graph.insertEdge(v1, v2, 1);
    graph.insertEdge(v1, v3, 1);
    graph.insertEdge(v1, v4, 1);
    graph.insertEdge(v1, v5, 1);
    graph.insertEdge(v2, v3, 1);
    graph.insertEdge(v2, v4, 1);
    graph.insertEdge(v2, v5, 1);
    graph.insertEdge(v3, v4, 1);
    graph.insertEdge(v3, v5, 1);
    graph.insertEdge(v4, v5, 1);

    // Create adjacency matrix complete graph
    auto v12 = graph2.insertVertex("A");
    auto v22 = graph2.insertVertex("B");
    auto v32 = graph2.insertVertex("C");
    auto v42 = graph2.insertVertex("D");
    auto v52 = graph2.insertVertex("E");
    graph2.insertEdge(v12, v22, 1);
    graph2.insertEdge(v12, v32, 1);
    graph2.insertEdge(v12, v42, 1);
    graph2.insertEdge(v12, v52, 1); //
    graph2.insertEdge(v22, v32, 1);
    graph2.insertEdge(v22, v42, 1);
    graph2.insertEdge(v22, v52, 1); //
    graph2.insertEdge(v32, v42, 1);
    graph2.insertEdge(v32, v52, 1); //
    graph2.insertEdge(v42, v52, 1); //
    
    // Create adjacency list complete graph
    auto v13 = graph3.insertVertex("A");
    auto v23 = graph3.insertVertex("B");
    auto v33 = graph3.insertVertex("C");
    auto v43 = graph3.insertVertex("D");
    auto v53 = graph3.insertVertex("E");
    graph3.insertEdge(v13, v23, 1);
    graph3.insertEdge(v13, v33, 1);
    graph3.insertEdge(v13, v43, 1);
    graph3.insertEdge(v13, v53, 1);
    graph3.insertEdge(v23, v33, 1);
    graph3.insertEdge(v23, v43, 1);
    graph3.insertEdge(v23, v53, 1);
    graph3.insertEdge(v33, v43, 1);
    graph3.insertEdge(v33, v53, 1);
    graph3.insertEdge(v43, v53, 1);
    

    printCenteredTitle(" Edge-linked ", '=', COL_WIDTH);
    DFS<GraphEdgeLinked<std::string, int>> dfsSearch(graph, v1);
    dfsSearch.printGraph();

    /*
    Expected output for complete graph of 5 vertices A-E
    DFS Traversal ({back edge}, (discovery edge)):
    A
    (A -- B)
    B
    (B -- C)
    C
    {C -- A}
    (C -- D)
    D
    {D -- A}
    {D -- B}
    (D -- E)
    E
    {E -- A}
    {E -- B}
    {E -- C}
    */
    
    BFS<GraphEdgeLinked<std::string, int>> bfsSearch(graph, v1);
    bfsSearch.printGraph();

    /*
    Expected output for complete graph of 5 vertices A-E
    BFS Traversal ({cross edge}, (discovery edge)):
    A
    (A -- B)
    B
    (A -- C)
    C
    (A -- D)
    D
    (A -- E)
    E
    {B -- C}
    {B -- D}
    {B -- E}
    {C -- D}
    {C -- E}
    {D -- E}
    */

    printCenteredTitle(" Adjacency Matrix ", '=', COL_WIDTH);
    DFS<GraphAdjacencyMatrix<std::string, int>> dfsSearch2(graph2, v12);
    dfsSearch2.printGraph();
    BFS<GraphAdjacencyMatrix<std::string, int>> bfsSearch2(graph2, v12);
    bfsSearch2.printGraph();
    
    printCenteredTitle(" Adjacency List ", '=', COL_WIDTH);
    DFS<GraphAdjacencyList<std::string, int>> dfsSearch3(graph3, v13);
    dfsSearch3.printGraph();
    BFS<GraphAdjacencyList<std::string, int>> bfsSearch3(graph3, v13);
    bfsSearch3.printGraph();

    return 0;
}

/* ============================================================================
Print an indicative title for a console menu to the console and center the title
string.
============================================================================ */
void printCenteredTitle(const char * title, const char buffChar, const int col_width) {
    const int size = strlen(title);

    // Calculate padding on both sides
    int total_padding = col_width - size;
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding; // Make sure right padding balances any leftover

    cout << "\n";

    for (int i = 0; i < left_padding; i++) {
        cout << buffChar;
    }

    cout << title;

    for (int i = 0; i < right_padding; i++) {
        cout << buffChar;
    }

    cout << "\n";
}

/* ============================================================================
                                  END FILE
============================================================================ */
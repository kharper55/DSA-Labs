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
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>      // For console interaction
#include <cstring>       // For stringlen
#include <string>        // for string class
#include <set>
#include <queue>

// Header includes
#include "LinkedTree.hpp"

using namespace std;

// Prototypes
void processFile(const string& filename, vector<string>& nodeValues, vector<int>& numChildrenPerNode);
void printCenteredTitle(const char * title, const char buffChar, const int col_width);

#define COL_WIDTH       65
#define FILE_NAME       "tree.txt"

/* ============================================================================
main()
============================================================================ */
int main() {
    
    cout << "\nWelcome to general tree postorder traversal demo!\n\n";
    LinkedTree<string> myTree;

    // make a function to search file line by line, add unique nodes to a set and append to vector on first encounter
    // use these to build the level order traversal equivalent vector nodeValues
    
    // count number of entries on each line past the parent (the first whitespace delimited string) up to and excluding the empty child char "#"
    // use this count to build the numChildrenPerNode vector

    //vector<std::string> nodeValues = {"Paper", "Title", "Abstract", "1", "2", "3", "References", "1.1", "1.2", "2.1", "2.2", "2.3", "3.1", "3.2"};
    //vector<int> numChildrenPerNode = {6, 0, 0, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0};

    vector<string> nodeValues;
    vector<int> numChildrenPerNode;
    processFile(FILE_NAME, nodeValues, numChildrenPerNode);

    /*
    cout << "nodeValues: \n";
    for (int i = 0; i < nodeValues.size(); i++) {
        cout << nodeValues[i] << "\n";
    }

    cout << "numChildrenPerNode: \n";
    for (int i = 0; i < numChildrenPerNode.size(); i++) {
        cout << numChildrenPerNode[i] << "\n";
    }*/

    // Add root
    myTree.addRoot(nodeValues[0]);
    auto rootPos = myTree.root();

    // Populate the tree
    int nodeIndex = 1;  // Start from the first child (index 1)
    queue<LinkedTree<string>::Position> parentQueue;  // Queue for managing parents
    parentQueue.push(rootPos);  // Enqueue the root position

    int currentParentIndex = 0;  // Tracks the parent in numChildrenPerNode

    while (!parentQueue.empty() && nodeIndex < nodeValues.size()) {
        // Get the current parent node
        auto currentParent = parentQueue.front();
        parentQueue.pop();  // Remove from the queue after processing

        int numChildren = numChildrenPerNode[currentParentIndex++];  // Get number of children for the current parent

        if (numChildren > 0) {
            vector<string> children;

            // Collect the correct number of children for the current parent
            for (int i = 0; i < numChildren && nodeIndex < nodeValues.size(); i++) {
                children.push_back(nodeValues[nodeIndex++]);
            }

            // Add children to the tree
            myTree.addChildren(currentParent, children);

            // Enqueue each child position for future processing
            for (int i = 0; i < numChildren; i++) {
                parentQueue.push(currentParent.child(i));
            }
        }
    }

    // Preorder check
    cout << "Linked Decision Tree (Preorder Traversal):\n";
    auto positions = myTree.positions(true);
    for (LinkedTree<string>::Position pos : positions) {
        cout << *pos << "\n";
    }

    // Postorder check
    cout << "\nLinked Decision Tree (Postorder Traversal):\n";
    positions = myTree.positions(false);
    for (LinkedTree<string>::Position pos : positions) {
        cout << *pos << "\n";
    }

	return 0;
}

/* ============================================================================
Process an input file according to the recommended format (parent children #)
============================================================================ */

void processFile(const string& filename, vector<string>& nodeValues, vector<int>& numChildrenPerNode) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Error opening file: " + filename);
    }

    set<string> uniqueNodes; // Set to track unique nodes
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string parent;
        iss >> parent; // Read parent node

        // Add parent to nodeValues only if it's new
        if (uniqueNodes.insert(parent).second) {
            nodeValues.push_back(parent);
            numChildrenPerNode.push_back(0); // Initialize child count for new parent
        }

        // Find the index of the parent in nodeValues
        int parentIndex = -1;
        for (int i = 0; i < nodeValues.size(); ++i) {
            if (nodeValues[i] == parent) {
                parentIndex = i;
                break;
            }
        }
        // Count children for this parent
        int childCount = 0;
        string child;
        while (iss >> child) {
            if (child == "#") break; // Stop when encountering "#"

            // Add child to nodeValues only if it's new
            if (uniqueNodes.insert(child).second) {
                nodeValues.push_back(child);
                numChildrenPerNode.push_back(0); // Initialize child count for new child
            }
            ++childCount; // Increment child count
        }

        // Update the parent's child count
        numChildrenPerNode[parentIndex] = childCount;
    }
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

    cout << "\n\n";
}

/* ============================================================================
                                  END FILE
============================================================================ */
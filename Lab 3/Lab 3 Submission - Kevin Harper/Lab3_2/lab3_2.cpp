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
#include <fstream>
//#include <sstream>
#include <cstring>       // For stringlen
#include <string>        // for string class
//#include <queue>
#include <set>

// Header includes
#include "LinkedBinaryTree.hpp"
#include "ArrayBinaryTree.hpp"

using namespace std;

// Prototypes
void extractThreeStrings(const std::string& line, std::string& str1, std::string& str2, std::string& str3);
std::string getQuotedString(const std::string& line, size_t& start, const char emptyChar);
void appendNode(set<std::string>& uniqueNodes, std::vector<std::string>& nodes, std::string& node, const char emptyChar);
void printCenteredTitle(const char * title, const char buffChar, const int col_width);

#define COL_WIDTH       65
#define EMPTY_CHAR      '#'
#define FILE_NAME       "decisionTree.txt"

/* ============================================================================
main()
============================================================================ */
int main() {
    
    cout << "\nWelcome to decision tree demo!\n";
    LinkedBinaryTree<string> myLinkedDecisionTree;
    ArrayBinaryTree<string> myArrDecisionTree;
    const std::string no = "No";
    const std::string yes = "Yes";
    const std::string answers[4][2] = {{no, no}, {no, yes}, {yes, no}, {yes, yes}};

    // FAILED ATTEMPT - HARDCODED AND INELEGANT
    /*
    // line format... root, lchild, rchild
    ifstream file(FILE_NAME);
    if (!file) {
        cerr << "Error opening file: " << FILE_NAME << endl;
        //return;
    }   

    else {    
        std::string line;
        bool rootAdded = false; 
        bool subTreeDone = false;
        // Queue to manage positions for expansion
        std::queue<typename LinkedBinaryTree<std::string>::Position> nodeQueue;
        while (std::getline(file, line)) { // Read the file line by line
            auto pos = myDecisionTree.root();
            string parent, lChild, rChild;
            extractThreeStrings(line, parent, lChild, rChild);
            cout << "Parent: " << parent << " lChild: " << lChild << " rChild: " << rChild << endl;
            if (!rootAdded) {
                myDecisionTree.addRoot(parent);
                nodeQueue.push(myDecisionTree.root());
                rootAdded = true;
            }
            pos = nodeQueue.front();
            nodeQueue.pop();
            if (lChild != "#") {
                // advance node
                myDecisionTree.expandExternal(pos);
                auto lChildNode = pos.left();
                *lChildNode = lChild;
                nodeQueue.push(lChildNode);
                if (rChild != "#") {
                    auto rChildNode = pos.right();
                    *rChildNode = rChild;
                    nodeQueue.push(rChildNode);
                }
            }
            else if (subTreeDone) {
                // left subtree is done, move to right
                while(!nodeQueue.empty()) {
                    nodeQueue.pop();
                }
                nodeQueue.push(myDecisionTree.root().right());
            }
            else {
                subTreeDone = true;
            }
        }
    }
    file.close();*/

    // line format... root, lchild, rchild
    ifstream file(FILE_NAME);
    if (!file) {
        cerr << "Error opening file: " << FILE_NAME << endl;
        return -1;
    }   
    else {
        std::string line;
        std::vector<std::string> nodes;
        set<std::string> uniqueNodes;
        std::string parent, lChild, rChild;
        // Read the file line by line
        while (std::getline(file, line)) {
            extractThreeStrings(line, parent, lChild, rChild);
            //cout << "Parent: " << parent << ", lChild: " << lChild << ", rChild: " << rChild << endl;
            appendNode(uniqueNodes, nodes, parent, EMPTY_CHAR);
            appendNode(uniqueNodes, nodes, lChild, EMPTY_CHAR);
            appendNode(uniqueNodes, nodes, rChild, EMPTY_CHAR);
        }
        // Nodes will be at vector indices consistent with Vector-Based Representation of Binary Trees (lecture 9)
        file.close();

        // Build the binary tree
        // Calls a recursive method which assumes a complete binary tree
        myLinkedDecisionTree.constructTree(nodes);
        myArrDecisionTree.constructTree(nodes);
    }

    // Preorder check
    cout << "\nLinked Decision Tree (Preorder Traversal):\n";
    auto positions = myLinkedDecisionTree.positions();
    for (auto pos : positions) {
        cout << *pos << "\n";
    }

    cout << "\nArray Decision Tree (Preorder Traversal):\n";
    auto positions2 = myArrDecisionTree.positions();
    for (auto pos : positions2) {
        cout << *pos << "\n";
    }

    // Traverse the linked decision tree
    printCenteredTitle(" Demonstration of linked binary decision tree ", '*', 60);
    for (int i = 0; i < sizeof(answers) / sizeof(answers[0]); i++) {
        std::string title = " Answers Version " + to_string(i + 1) + " ";
        printCenteredTitle(title.c_str(), '=', 60);
        auto pos = myLinkedDecisionTree.root();
        for (int j = 0; j < sizeof(answers[0]) / sizeof(answers[0][0]); j++) {
            cout << "Question: " << *pos << "\n";
            cout << "Answer: " << answers[i][j] << "\n";
            pos = (answers[i][j] == yes) ? (pos.left()) : (pos.right());
            //if (answers[i][j] == yes) pos = pos.left();
            //else pos = pos.right();
        }
        cout << "Decision: " << *pos << "\n";
    }

    // Traverse the array decision tree
    printCenteredTitle(" Demonstration of array binary decision tree ", '*', 60);
    for (int i = 0; i < sizeof(answers) / sizeof(answers[0]); i++) {
        std::string title = " Answers Version " + to_string(i + 1) + " ";
        printCenteredTitle(title.c_str(), '=', 60);
        auto pos = myArrDecisionTree.root();
        for (int j = 0; j < sizeof(answers[0]) / sizeof(answers[0][0]); j++) {
            cout << "Question: " << *pos << "\n";
            cout << "Answer: " << answers[i][j] << "\n";
            pos = (answers[i][j] == yes) ? (pos.left()) : (pos.right());
            //if (answers[i][j] == yes) pos = pos.left();
            //else pos = pos.right();
        }
        cout << "Decision: " << *pos << "\n";
    }

    cout << "\nPhew. I'm glad that's over.\n\n";
    
	return 0;
}

/* ============================================================================
Appends a node to the list of nodes prior to beginning binary tree construction
============================================================================ */
void appendNode(set<std::string>& uniqueNodes, std::vector<std::string>& nodes, std::string& node, const char emptyChar) {
    // Check if node DNE in the set
    const std::string EMPTY_STR(1, EMPTY_CHAR);
    if (uniqueNodes.find(node) == uniqueNodes.end() && node != EMPTY_STR) {
        nodes.push_back(node);
        uniqueNodes.insert(node); // add it to the set of unique nodes
    }
}

/* ============================================================================
Helper function to extract a quoted string or handle emptyChar
============================================================================ */
std::string getQuotedString(const std::string& line, size_t& start, const char emptyChar) {
    // Find the opening quote or emptyChar
    size_t start2 = start;
    start = line.find('"', start);
    if (start == std::string::npos) { // No quote found
        start = line.find(emptyChar, start2);
        if (start == std::string::npos) {
            throw std::runtime_error("Invalid formatting: Expected a quote or emptyChar.");
        } else {
            // Move past the emptyChar
            ++start;
            //std::cout << "# found... No entry for this child\n";
            return std::string(1, emptyChar); // Return emptyChar as a string
        }
    }

    // Find the closing quote
    size_t end = line.find('"', start + 1);
    if (end == std::string::npos) {
        throw std::runtime_error("Unmatched quotation mark.");
    }

    // Extract the quoted string
    std::string quotedString = line.substr(start + 1, end - start - 1);

    // Update the start position for the next search
    start = end + 1;

    return quotedString;
}

/* ============================================================================
Function to extract up to 3 strings from a line of text in a file
============================================================================ */
void extractThreeStrings(const std::string& line, std::string& str1, std::string& str2, std::string& str3) {
    size_t start = 0;

    // Use the helper function to extract each string
    str1 = getQuotedString(line, start, EMPTY_CHAR);
    str2 = getQuotedString(line, start, EMPTY_CHAR);
    str3 = getQuotedString(line, start, EMPTY_CHAR);

    // Ensure no extra text remains after the third quoted string
    if (line.find_first_not_of(" \t", start) != std::string::npos) {
        throw std::runtime_error("Unexpected extra text after the third quoted string.");
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
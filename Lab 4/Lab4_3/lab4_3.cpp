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
#include <string>        // For cpp string class
#include <fstream>       // For filestream object(s)

// Header includes
//#include "BinarySearchTree.hpp"
#include "Tree23.hpp"

using namespace std;

// Prototypes
void printCenteredTitle(const char * title, const char buffChar, const int col_width);
bool isOnlyAlphabetical(const string& str);
void toLowerCase(string& str); 
void skipLines(ifstream& file, int linesToSkip);
int countLines(ifstream& file);
void readLines(ifstream& file, vector<string>& entries, const int numLines);
void printConsoleMenu(char quitChar, const string OPTIONS_LIST[], int numOptions);

#define NUM_OPTIONS 3

// Globals
const string OPTIONS_LIST[] = {
    "Search for word",
    "Insert word",
    "Print dictionary"
};

#define COL_WIDTH       65
#define FILE_NAME       "words_alpha-4.txt"
#define NUM_NODES       200
#define QUIT_CHAR       'x'

/* ============================================================================
Main application
============================================================================ */
int main() {
    //SearchTree<Entry<std::string, std::string>> myTree;
    //AVLTree<AVLEntry<Entry<string, string>>> myTree;
    TwoThreeTree<Entry23<Entry<string, string>>> myTree;
    vector<string> words;
    bool userQuit = false;
    string userChoice;

    cout << "Welcome to (2, 3) Tree dictionary demo!\n";

    std::ifstream dictFile(FILE_NAME);
    if (!dictFile) {
        std::cerr << "Error opening file: " << FILE_NAME << std::endl;
        return -1;
    }

    // Go to the middle of the file less 1/2 the number of words desired
    int fileLength = countLines(dictFile);
    skipLines(dictFile, ((fileLength / 2) - (NUM_NODES / 2)));

    // Read in NUM_NODES words into the words vector
    readLines(dictFile, words, NUM_NODES);

    // Close the file
    dictFile.close();

    // Take advantage of sorted words vector to construct the BST
    myTree.createBalancedBST(words, words, 0, words.size() - 1);

    while(!userQuit) {
        printCenteredTitle(" Options ", '=', COL_WIDTH);
        printConsoleMenu('x', OPTIONS_LIST, NUM_OPTIONS);
        getline(cin, userChoice);
        if (userChoice.length() != 1) {cout << "\nEnter a single character.\n"; continue;}
        else if (userChoice[0] == QUIT_CHAR || userChoice[0] == QUIT_CHAR - 0x20) {userQuit = true; break;}
        else {
            switch(userChoice[0]) {
                case('A'):
                case('a'): // Search for a word
                    while(true) {
                        cout << "\nEnter a word to search for: ";
                        getline(cin, userChoice);
                        if (!(isOnlyAlphabetical(userChoice))) {cout << "\nContains non-alphabetical characters.\n"; continue;}
                        else {
                            toLowerCase(userChoice);
                            cout << "\n\"" << userChoice <<  "\" is" << ((myTree.find(userChoice) == myTree.end()) ? " not in " : " in ") << "the dictionary.\n"; 
                            break;
                        }
                    }
                    break;
                case('B'):
                case('b'): // Insert a word
                    while(true) {
                        cout << "\nEnter a word to insert: ";
                        getline(cin, userChoice);
                        if (!(isOnlyAlphabetical(userChoice))) {cout << "\nContains non-alphabetical characters.\n"; continue;}
                        else {
                            toLowerCase(userChoice);
                            if (!(myTree.find(userChoice) == myTree.end())) {
                                cout << "\n\"" << userChoice << "\" is already in the dictionary.\n";
                            }
                            else {
                                cout << "\nAdding " << userChoice << " to dictionary.\n";
                                myTree.insert(userChoice, userChoice);
                            }
                            break;
                        }
                    }
                    break;
                case('C'):
                case('c'): // Print the dictionary
                    myTree.printTree();
                    break;
                default:
                    cout << "\nInvalid selection.\n";
            }

        }
    }

    return 0;
}

/* ============================================================================
Function to check if a string is strictly alphabetical characters
============================================================================ */
bool isOnlyAlphabetical(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false; // Found a non-alphabetical character
        }
    }
    return true; // All characters are alphabetical
}

/* ============================================================================
Function to force a string to be all lowercase
============================================================================ */
void toLowerCase(std::string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

/* ============================================================================
Function to skip 'n' lines from the beginning of a file
============================================================================ */
void skipLines(ifstream& file, int linesToSkip) {
    string line;
    for (int i = 0; i < linesToSkip; ++i) {
        getline(file, line);  // Skip the line
    }
}

/* ============================================================================
Function to count a lines in a file
============================================================================ */
int countLines(ifstream& file) {
    int lineCount = 0;
    string line;
    
    while (getline(file, line)) {
        ++lineCount;  // Increment for each line
    }
    file.clear();  // Clear the EOF flag
    file.seekg(0, ios::beg);  // Reset file pointer to the beginning
    return lineCount;
}

/* ============================================================================
Function to read a specified number of lines from the file
============================================================================ */
void readLines(ifstream& file, vector<string>& entries, const int numLines) {
    string line;
    for (int i = 0; i < numLines; i++) {
        getline(file, line);
        entries.push_back(line);
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
Print the main menu for this programs implementation to the console.
============================================================================ */
void printConsoleMenu(char quitChar, const string OPTIONS_LIST[], int numOptions) {

    for (int i = 0; i < numOptions; i++) { 
        cout << static_cast<char>(0x61 + i) << ") " << OPTIONS_LIST[i] << "\n";
    }

    cout << "\nSelect an option from the list (use '" << quitChar << "' to quit): ";
} 

/* ============================================================================
                                  END FILE
============================================================================ */
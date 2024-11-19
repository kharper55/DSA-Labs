/* ============================================================================
lab1.cpp

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
#include <iostream>                 // For console interaction
#include <string>                   // For stoi
#include <cstring>                  // For strlen
#include <stack>                    // For STL stack

// Header includes
#include "ArrayStack.hpp"
#include "LinkedStack.hpp"

// Constants
const string DS_OPTIONS[3] = {
    "STL stack",
    "Array-based stack",
    "Linked list-based stack",
};

const char QUIT_CHAR = 'x';

enum {
    STL_STACK,
    ARRAY_STACK,
    LINKED_STACK
};

// Function prototypes
bool parenMatchSTLStack(const string& s);
bool parenMatchArrayStack(const string& s);
bool parenMatchLinkedStack(const string& s);
void printCenteredTitle(const char * title, const int col_width);

using namespace std;

/* ============================================================================
main()
============================================================================ */
int main() {

    //const string demoString = "(( ))(( )){([( )])}";   // valid
    //const string demoString = "(( ))(( )){([( )])";    // invalid  
    const string demoString = "({[ ])}";               // invalid
    //const string demoString = "({[ ]})";               // valid
    //const string demoString = "";                      // valid

    cout << "\nWelcome to parenthesis matching demo!\n";
    char userChoice;
    bool userQuit = false;

    while(!userQuit) {
        printCenteredTitle(" Data structure selection ", 40);
        for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
            cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
        }
        printCenteredTitle(" Input ", 40);
        cout << "Input: " << demoString << ".\n";
        cout << "\nSelect a data structure for parenthesis\nmatch (use '" << QUIT_CHAR << "' to quit): ";
        cin >> userChoice;
        if (userChoice != QUIT_CHAR) {
            int ds = static_cast<int>(userChoice - 0x61);
            switch(ds) {
                case(STL_STACK): // Array 
                {   
                    printCenteredTitle(" STL Stack ", 40);
                    cout << demoString << " is " << (parenMatchSTLStack(demoString) ? "a match." : "not a match.") << "\n";
                    break;
                }
                case(ARRAY_STACK): // Singly linked list
                {   
                    printCenteredTitle(" Array-based Stack ", 40);
                    cout << demoString << " is " << (parenMatchArrayStack(demoString) ? "a match." : "not a match.")<< "\n"; 
                    break;
                }
                case(LINKED_STACK): // Doubly linked list
                {
                    printCenteredTitle(" Linked List-based Stack ", 40);
                    cout << demoString << " is " << (parenMatchLinkedStack(demoString) ? "a match." : "not a match.")<< "\n";
                    break;
                }
                default:
                    cout << "\n'" << static_cast<char>(ds + 0x61) << "' is not a valid option.\n";
                    break;
            }
        }
        else userQuit = true;
    }

	return 0;
}

/* ============================================================================
parenMatchArrayStack()
============================================================================ */
bool parenMatchArrayStack(const string& s) {
    ArrayStack<char> ss;
    for (int i = 0; i < s.length(); i++) {
        // Opening paren
        if (s[i] == '[' || s[i] == '(' ||  s[i] == '{') ss.push(s[i]);
        
        // Closing paren
        if (s[i] == ']') {
            if (ss.top() == '[') ss.pop();
            else return false;
        }
        if (s[i] == ')') {
            if (ss.top() == '(') ss.pop();
            else return false;
        }
        if (s[i] == '}') {
            if (ss.top() == '{') ss.pop();
            else return false;
        }
    }
    return ss.empty();
}

/* ============================================================================
parenMatchSTLStack()
============================================================================ */
bool parenMatchSTLStack(const string& s) {
    stack<char> ss;
    for (int i = 0; i < s.length(); i++) {
        // Opening paren
        if (s[i] == '[' || s[i] == '(' ||  s[i] == '{') ss.push(s[i]);
        
        // Closing paren
        if (s[i] == ']') {
            if (ss.top() == '[') ss.pop();
            else return false;
        }
        if (s[i] == ')') {
            if (ss.top() == '(') ss.pop();
            else return false;
        }
        if (s[i] == '}') {
            if (ss.top() == '{') ss.pop();
            else return false;
        }
    }
    return ss.empty();
}

/* ============================================================================
parenMatchLinkedStack()
============================================================================ */
bool parenMatchLinkedStack(const string& s) {
    LinkedStack<char> ss;
    for (int i = 0; i < s.length(); i++) {
        // Opening paren
        if (s[i] == '[' || s[i] == '(' ||  s[i] == '{') ss.push(s[i]);
        
        // Closing paren
        if (s[i] == ']') {
            if (ss.top() == '[') ss.pop();
            else return false;
        }
        if (s[i] == ')') {
            if (ss.top() == '(') ss.pop();
            else return false;
        }
        if (s[i] == '}') {
            if (ss.top() == '{') ss.pop();
            else return false;
        }
    }
    return ss.empty();
}

/* ============================================================================
Print an indicative title for a console menu to the console and center the title
string.
============================================================================ */
void printCenteredTitle(const char * title, const int col_width) {
    const int size = strlen(title);

    // Calculate padding on both sides
    int total_padding = col_width - size;
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding; // Make sure right padding balances any leftover

    cout << "\n";

    for (int i = 0; i < left_padding; i++) {
        cout << "=";
    }

    cout << title;

    for (int i = 0; i < right_padding; i++) {
        cout << "=";
    }

    cout << "\n\n";
}

/* ============================================================================
                                  END FILE
============================================================================ */
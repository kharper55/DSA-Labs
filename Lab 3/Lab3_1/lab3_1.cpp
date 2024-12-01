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

// Header includes
#include "TextEditor.hpp"

// Prototypes

// Globals

using namespace std;

#define COL_WIDTH       65

/* ============================================================================
main()
============================================================================ */
int main() {
    
    const string testStrErr = "Hello Wprld!";
    const string testStrTarget = "Hello World!";
    TextEditor<char> editor;

    cout << "\nWelcome to text editor demo!\n\n";

    for (int i = 0; i < testStrErr.size(); i++) {
        editor.insertChar(testStrErr[i]);
    }

    editor.displayText(); // Output: Hello|

    cout << "Curse these aging fingers!\n";

    // Determine the first point of difference
    int diffIndex = 0;
    while (diffIndex < testStrErr.size() && diffIndex < testStrTarget.size() &&
           testStrErr[diffIndex] == testStrTarget[diffIndex]) {
        diffIndex++;
    }

    // Move the cursor to the position of the first difference
    int cursorMovesRequired = testStrErr.size() - diffIndex;
    for (int i = 0; i < cursorMovesRequired; i++) {
        editor.moveCursorLeft();
    }

    editor.displayText(); // Show new cursor position

    // Fix the error by inserting the missing character ('o') and deleting the extra ('r')
    editor.deleteChar();
    editor.insertChar(testStrTarget[diffIndex]); // Insert the missing character
    editor.displayText();   // Output: Hello World!

    // Return cursor to end of the line
    for (int i = 0; i < cursorMovesRequired; i++) {
        editor.moveCursorRight();
    }
    editor.deleteChar();        // Do nothing at the end
    editor.displayText();

    // Return cursor to beginning of the line
    for (int i = testStrTarget.size(); i >= 0; i--) {
        editor.moveCursorLeft();
    }
    
    // Display the final state of the text editor
    editor.displayText(); 

	return 0;
}

/* ============================================================================
                                  END FILE
============================================================================ */
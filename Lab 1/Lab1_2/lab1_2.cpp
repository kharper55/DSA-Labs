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
#include <iomanip>                  // For setprecision()
#include <chrono>                   // for high_resolution_clock
#include <string>                   // For stoi

// Header includes
#include "arrayStack.hpp"

using namespace std;

void towerOfHanoi(int numDisks, ArrayStack<int>& source, ArrayStack<int>& dest, ArrayStack<int>& aux);

/* ============================================================================
main()

1:


5:
0.0000009000
0.0000015000
0.0000018000
0.0000005000
0.0000012000

25:
0.2655389000
0.2798653000
0.2683323000
0.2784276000
0.2620541000

125:
============================================================================ */
int main() {
    ArrayStack<int> src;
    ArrayStack<int> aux;
    ArrayStack<int> dst;
    const int numDisks = 5;

    auto start = chrono::high_resolution_clock::now();
    auto stop = start;
    auto duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
    double timeElapsed = duration.count();

    cout << "\nWelcome to Towers of Hanoi demo!\n\n";

    // Create a stack where elements increase in value from bottom to top
    for (int i = numDisks; i >= 1; i--) {
        src.push(i);
    }

    cout << "Performing Towers of Hanoi with " << numDisks << " disks.\n\n";
    cout << "Source address: " << &src << "\n";
    cout << "Destination address: " << &dst << "\n";
    cout << "Auxilliary address: " << &aux << "\n\n";
    //src.printStack();

    start = chrono::high_resolution_clock::now();
    towerOfHanoi(numDisks, src, dst, aux);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::duration<double>>(stop - start);
    timeElapsed = duration.count();
    cout << "\nDone.\n\nTime elapsed: " << fixed << setprecision(10) << timeElapsed << "s.\n";

    //dst.printStack();

	return 0;
}

/* ============================================================================
isPalindrome()
============================================================================ */
void towerOfHanoi(int numDisks, ArrayStack<int>& source, ArrayStack<int>& dest, ArrayStack<int>& aux) {

    if (numDisks == 1) {
        cout << "Moving disk 1 from " << &source << " to " << &dest << ".\n";
        dest.push(source.top());
        source.pop();
        return;
    }
    
    // Move top n-1 disks from source to auxiliary
    towerOfHanoi(numDisks - 1, source, aux, dest);
    
    // Move the nth disk from source to destination
    cout << "Moving disk " << numDisks << " from " << &source << " to " << &dest << ".\n";
    dest.push(source.top());
    source.pop();
    
    // Move n-1 disks from auxiliary to destination
    towerOfHanoi(numDisks - 1, aux, dest, source);
}

/* ============================================================================
                                  END FILE
============================================================================ */
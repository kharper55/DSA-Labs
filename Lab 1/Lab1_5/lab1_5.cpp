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
#include <string>        // For string type
#include <cstring>       // For stringlen

// Header includes
#include "CLinkedList.hpp"
//#include "CNode.hpp"
#include "DLinkedList.hpp"
//#include "DNode.hpp"
#include "SLinkedList.hpp"
//#include "SNode.hpp"

// Prototypes
//void printConsoleMenu(const char choice, const int ds);
void printCenteredTitle(const char * title, int col_width);
void concatCircularLists(CircleList<int>& L1, CircleList<int>& L2);
void concatDLinkedLists(DLinkedList<int>& L1, DLinkedList<int>& L2);
void concatSLinkedLists(SLinkedList<int>& L1, SLinkedList<int>& L2);
void concatArrays(int * L1, int L1size, int * L2, int L2size, int * L3, int L3size);
void printIntArray(/*const char * arrLabel,*/ int arr[], int arrLen, int maxColWidth);

// Conversion functions
void arrToDLinkedList(DLinkedList<int>& list, const int arr[], const int size);
void DLinkedListToArr(const DLinkedList<int>& list, int arr[], const int size);
void SLinkedListToDLinkedList(DLinkedList<int>& L1, const SLinkedList<int>& L2);
void DLinkedListToSLinkedList(const DLinkedList<int>& L1, SLinkedList<int>& L2);
void CircularListToDLinkedList(DLinkedList<int>& L1, const CircleList<int>& L2);
void DLinkedListToCircularList(const DLinkedList<int>& L1, CircleList<int>& L2);
void arrToCircularList(CircleList<int>& list, const int arr[], const int size);
void CircularListToArr(const CircleList<int>& list, int arr[], const int size);
void SLinkedListToCircularList(CircleList<int>& L1, const SLinkedList<int>& L2);
void CircularListToSLinkedList(const CircleList<int>& L1, SLinkedList<int>& L2);

// Constants
const string DS_OPTIONS[4] = {
    "Array",
    "Singly linked list",
    "Doubly linked list",
    "Circularly linked list"
};

const char QUIT_CHAR = 'x';

enum {
    ARRAY,
    SING_LL,
    DOUB_LL,
    CIRC_LL
};

#define DEMO_ARR1_SIZE 4
#define DEMO_ARR2_SIZE 6

using namespace std;

/* ============================================================================
main()
============================================================================ */
int main() {

    // two arrays for testing
    int demoArr1[DEMO_ARR1_SIZE] = {1, 2, 3, 4};
    int demoArr2[DEMO_ARR2_SIZE] = {5, 6, 7, 8, 9, 10};

    // equivalent alternative data structures with nodes corresponding to array elements
    CircleList<int> demoCList1;
    CircleList<int> demoCList2;
    SLinkedList<int> demoSList1;
    SLinkedList<int> demoSList2;
    DLinkedList<int> demoDList1;
    DLinkedList<int> demoDList2;
    arrToCircularList(demoCList1, demoArr1, 4);
    arrToCircularList(demoCList2, demoArr2, 6);
    CircularListToSLinkedList(demoCList1, demoSList1);
    CircularListToSLinkedList(demoCList2, demoSList2);
    CircularListToDLinkedList(demoDList1, demoCList1);
    CircularListToDLinkedList(demoDList2, demoCList2);

    cout << "\nWelcome to list concatenation demo!\n";
    char userChoice;
    bool userQuit = false;

    while(!userQuit) {
        printCenteredTitle(" Data structure selection ", 40);
        for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
            cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
        }
        printCenteredTitle(" Inputs ", 40);
        cout << "L1: ";
        demoCList1.printList();
        cout << "L2: ";
        demoCList2.printList();
        cout << "\nSelect a data structure that you wish to\nconcatenate (use '" << QUIT_CHAR << "' to quit): ";
        cin >> userChoice;
        if (userChoice != QUIT_CHAR) {
            int ds = static_cast<int>(userChoice - 0x61);
            switch(ds) {
                case(ARRAY): // Array 
                {   
                    printCenteredTitle(" Concatenated arrays ", 40);
                    int * result = new int[DEMO_ARR1_SIZE + DEMO_ARR2_SIZE];
                    concatArrays(demoArr1, DEMO_ARR1_SIZE, demoArr2, DEMO_ARR2_SIZE, result, DEMO_ARR1_SIZE + DEMO_ARR2_SIZE);
                    printIntArray(result, 10, 10);       // Print the result
                    delete result;
                    break;
                }
                case(SING_LL): // Singly linked list
                {   
                    printCenteredTitle(" Concatenated singly linked lists ", 40);
                    SLinkedList<int> * result = new SLinkedList<int>;
                    *result = demoSList1;                     // Invoke copy constructor and operator= overload. concatSLinkedLists builds on top of first list arg
                    concatSLinkedLists(*result, demoSList2);
                    result->printList();                      // Print the result
                    delete result;
                    break;
                }
                case(DOUB_LL): // Doubly linked list
                {
                    printCenteredTitle(" Concatenated doubly linked lists ", 40);
                    DLinkedList<int> * result = new DLinkedList<int>;
                    *result = demoDList1;                     // Invoke copy constructor and operator= overload. concatDLinkedLists builds on top of first list arg
                    concatDLinkedLists(*result, demoDList2);  // Perform concatenation
                    result->printList();                      // Print the result
                    delete result;
                    break;
                }
                case(CIRC_LL): // Circular linked list
                {   
                    printCenteredTitle(" Concatenated circular linked lists ", 40);
                    CircleList<int> * result = new CircleList<int>;
                    *result = demoCList1;                           // Invoke copy constructor and operator= overload. concatCircularLists builds on top of first list arg 
                    concatCircularLists(*result, demoCList2);       // Perfom concatenation
                    result->printList();                            // Print the results
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
Copy array into a doubly linked list
============================================================================ */
void arrToDLinkedList(DLinkedList<int>& list, const int arr[], const int size) {
    for (int i = 0; i < size; i++) {
        list.addBack(arr[i]);
    }
}

/* ============================================================================
Copy doubly linked list into a preallocated array
============================================================================ */
void DLinkedListToArr(const DLinkedList<int>& list, int arr[], const int size) {
    if (list.empty()) return;
    if (size != list.getSize()) return;
    DLinkedList<int> listCopy = list;
    for (int i = 0; i < size; i++) {
        arr[i] == listCopy.front();
        listCopy.removeFront();
    }
}

/* ============================================================================
Copy singly linked list into a doubly linked list
============================================================================ */
void SLinkedListToDLinkedList(DLinkedList<int>& L1, const SLinkedList<int>& L2) {
    if (L2.empty()) return;
    SLinkedList<int> L2copy = L2;
    for (int i = 0; i < L2.getSize(); i++) {
        L1.addBack(L2copy.front());
        L2copy.removeFront();
    }
}

/* ============================================================================
Copy doubly linked list into a singly linked list
============================================================================ */
void DLinkedListToSLinkedList(const DLinkedList<int>& L1, SLinkedList<int>& L2) {
    if (L1.empty()) return;
    DLinkedList<int> L1copy = L1;
    for (int i = 0; i < L1.getSize(); i++) {
        L2.addBack(L1copy.front());
        L1copy.removeFront();
    }
}

/* ============================================================================
Copy circular linked list into a doubly linked list
============================================================================ */
void CircularListToDLinkedList(DLinkedList<int>& L1, const CircleList<int>& L2) {
    if (L2.empty()) return; // If the circular list is empty, do nothing
    CircleList<int> L2copy = L2;
    for (int i = 0; i < L2.getSize(); i++) {
        L2copy.advance();
        L1.addBack(L2copy.front());
        //L2copy.advance();
    }
}

/* ============================================================================
Copy doubly linked list into a circular linked list
============================================================================ */
void DLinkedListToCircularList(const DLinkedList<int>& L1, CircleList<int>& L2) {
    if (L1.empty()) return;
    DLinkedList<int> L1copy = L1;
    for (int i = 0; i < L1.getSize(); i++) {
        L2.addBack(L1copy.front());
        L1copy.removeFront();
    }
}

/* ============================================================================
Copy array into a circular linked list
============================================================================ */
void arrToCircularList(CircleList<int>& list, const int arr[], const int size) {
    for (int i = 0; i < size; i++) {
        list.addBack(arr[i]);
    }
}

/* ============================================================================
Copy circular linked list into a preallocated array
============================================================================ */
void CircularListToArr(const CircleList<int>& list, int arr[], const int size) {
    if (list.empty()) return;
    if (size != list.getSize()) return;
    CircleList<int> listCopy = list;
    for (int i = 0; i < size; i++) {
        listCopy.advance();
        arr[i] = listCopy.front(); // Use assignment, not equality check
    }
}

/* ============================================================================
Copy singly linked list into a circular linked list
============================================================================ */
void SLinkedListToCircularList(CircleList<int>& L1, const SLinkedList<int>& L2) {
    if (L2.empty()) return;

    SLinkedList<int> L2copy = L2;
    while (!L2copy.empty()) {
        L1.addBack(L2copy.front());
        L2copy.removeFront();
    }
}

/* ============================================================================
Copy circular linked list into a singly linked list
============================================================================ */
void CircularListToSLinkedList(const CircleList<int>& L1, SLinkedList<int>& L2) {
    if (L1.empty()) return;

    CircleList<int> L1copy = L1;
    for (int i = 0; i < L1.getSize(); i++) {
        L1copy.advance();
        L2.addBack(L1copy.front());
    }
}

/* ============================================================================
Concatenate two arrays L1, L2 and place the result in L3
============================================================================ */
void concatArrays(int * L1, int L1size, int * L2, int L2size, int * L3, int L3size) {
    if (L1size + L2size != L3size) {
        cout << "Preallocation for buffer array is insignificant\n";
        return; 
    }

    // Copy elements from L1 to L3
    for (int i = 0; i < L1size; i++) {
        //cout << "Adding " << L1[i] << " to L3\n";
        L3[i] = L1[i];
    }

    // Copy elements from L2 to L3
    for (int i = 0; i < L2size; i++) {
        //cout << "Adding " << L2[i] << " to L3\n";
        L3[i + L1size] = L2[i];
    }
}

/* ============================================================================
Concatenate two singly linked lists L1, L2 and place the result in L1
============================================================================ */
void concatSLinkedLists(SLinkedList<int>& L1, SLinkedList<int>& L2) {
    int oldFront;

    for (int i = 0; i < L2.getSize(); i++) {
        L1.addBack(L2.front()); // Add L2's front element to the back of L1
        oldFront = L2.front();  // Swap L2 front to L2 back
        L2.addBack(oldFront);
        L2.removeFront();

    }
}

/* ============================================================================
Concatenate two circular linked lists L1, L2 and place the result in L1
============================================================================ */
void concatCircularLists(CircleList<int>& L1, CircleList<int>& L2) {
    for (int i = 0; i < L2.getSize(); i++) {
        L1.addBack(L2.front()); // Add L2's front element to the back of L1
        L2.advance();           // Increment cursor position
    }
}

/* ============================================================================
Concatenate two doubly linked lists L1, L2 and place the result in L1
============================================================================ */
void concatDLinkedLists(DLinkedList<int>& L1, DLinkedList<int>& L2) {
    int oldFront;
    
    for (int i = 0; i < L2.getSize(); i++) {
        L1.addBack(L2.front()); // Add L2's front element to the back of L1
        oldFront = L2.front();  // Swap L2 front to L2 back
        L2.addBack(oldFront);
        L2.removeFront();
    }
}

/* ============================================================================
Print an indicative title for a console menu to the console and center the title
string.
============================================================================ */
void printCenteredTitle(const char * title, int col_width) {
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
Print an integer array to the console, with maxColWidth entries per line.
============================================================================ */
void printIntArray(/*const char * arrLabel,*/ int arr[], int arrLen, int maxColWidth) {
    //cout << "\nArray contents for " << arrLabel << ":\n{";
    const bool USE_COMMA = false;
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i];

        // Separate elements by a comma unless end of array is reached
        if (i != arrLen - 1) cout << ((USE_COMMA) ? ", " : " ");
        //else cout << "}";

        // Print a newline for every maxColWidth elements printed
        if (((i + 1) % maxColWidth == 0) && (i != 0) && (i != arrLen - 1)) cout << "\n ";
        else if (i == arrLen - 1) {
            cout << "\n";
        }
    }
}

/* ============================================================================
                                  END FILE
============================================================================ */
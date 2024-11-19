/* ============================================================================
lab1_4.cpp

This program demonstrates comparison for various list data structures in a wrap
around fashion such that two lists are considered equal if they contain the 
same elements despite potentially starting at different points. Lists are
assumed to be sorted in non-decreasing order, i.e. with no duplicate values.

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
#include <cstring>       // For strlen

// Header includes
#include "CLinkedList.hpp"
//#include "CNode.hpp"
#include "DLinkedList.hpp"
//#include "DNode.hpp"
#include "SLinkedList.hpp"
//#include "SNode.hpp"

// Prototypes
void printConsoleMenu(const char choice, const int ds);
void printCenteredTitle(const char * title, int col_width);
bool compareArrays(const int * L1, const int L1size, const int * L2, const int L2size);
bool compareSLinkedLists(const SLinkedList<int>& L1, const SLinkedList<int>& L2);
bool compareCircularLinkedLists(const CircleList<int>& L1, const CircleList<int>& L2);
bool compareDLinkedLists(const DLinkedList<int>& L1, const DLinkedList<int>& L2);

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
const string OPTIONS[2] = {
    "Enter data",
    "Select a data structure"
};

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

#define DEMO_ARR1_SIZE 10
#define DEMO_ARR2_SIZE DEMO_ARR1_SIZE

using namespace std;

/* ============================================================================
main()
============================================================================ */
int main() {
    
    // create two demo lists
    //int testArr1[DEMO_ARR1_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //int testArr2[DEMO_ARR2_SIZE] = {5, 6, 7, 8, 9, 0, 1, 2, 3, 4};

    int testArr1[DEMO_ARR1_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int testArr2[DEMO_ARR2_SIZE] = {5, 6, 7, 8, 10, 0, 1, 2, 3, 4};

    CircleList<int> testCList1;
    CircleList<int> testCList2;
    DLinkedList<int> testDList1;
    DLinkedList<int> testDList2;
    SLinkedList<int> testSList1;
    SLinkedList<int> testSList2;
    
    arrToDLinkedList(testDList1, testArr1, DEMO_ARR1_SIZE);
    arrToDLinkedList(testDList2, testArr2, DEMO_ARR2_SIZE);
    DLinkedListToCircularList(testDList1, testCList1);
    DLinkedListToCircularList(testDList2, testCList2);
    DLinkedListToSLinkedList(testDList1, testSList1);
    DLinkedListToSLinkedList(testDList2, testSList2);

    cout << "\nWelcome to list comparison demo!\n";
    char userChoice;
    bool userQuit = false;

    while(!userQuit) {
        printCenteredTitle(" Data structure selection ", 40);
        for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
            cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
        }
        printCenteredTitle(" Inputs ", 40);
        cout << "L1: ";
        testCList1.printList();
        cout << "L2: ";
        testCList2.printList();
        cout << "\nSelect a data structure that you wish to\ncompare (use '" << QUIT_CHAR << "' to quit): ";
        cin >> userChoice;
        if (userChoice != QUIT_CHAR) {
            int ds = static_cast<int>(userChoice - 0x61);
            switch(ds) {
                case(ARRAY): // Array 
                {   
                    printCenteredTitle(" Array comparison ", 40);
                    cout << "Arrays are ";
                    cout << ((compareArrays(testArr1, DEMO_ARR1_SIZE, testArr2, DEMO_ARR2_SIZE)) ? "identical" : "not identical") << ".\n";
                    break;
                }
                case(SING_LL): // Singly linked list
                {   
                    printCenteredTitle(" Singly linked list comparison ", 40);
                    cout << "Singly linked lists are ";
                    cout << ((compareSLinkedLists(testSList1, testSList2)) ? "identical" : "not identical") << ".\n";
                    break;
                }
                case(DOUB_LL): // Doubly linked list
                {
                    printCenteredTitle(" Doubly linked list comparison ", 40);
                    cout << "Doubly linked lists are ";
                    cout << ((compareDLinkedLists(testDList1, testDList2)) ? "identical" : "not identical") << ".\n";
                    break;
                }
                case(CIRC_LL): // Circular linked list
                {   
                    printCenteredTitle(" Circular linked list comparison ", 40);
                    cout << "Circular linked lists are ";
                    cout << ((compareCircularLinkedLists(testCList1, testCList2)) ? "identical" : "not identical") << ".\n";
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
Comparison of two arrays, using L1 as the reference. O(n), O(1) space.
============================================================================ */
bool compareArrays(const int * L1, const int L1size, const int * L2, const int L2size) {
    if (L1size != L2size) return false;
    int pivotIdx = 0;
    while(L1[0] != L2[pivotIdx] && pivotIdx < L2size) { // Find a matching element and stop if iterations meet or exceed size of L2
        pivotIdx++;
    }
    if (pivotIdx == L2size) return false;
    else {
        //cout << "Found matching value " << L2[pivotIdx] << " at L2 index " << pivotIdx << "\n";
    }
    
    int j = pivotIdx;
    // Compare values to the right of the pivot index in L2
    for (j; j < L2size - 1; j++) {
        //cout << "Comparing L1 index " << (j + 1) - pivotIdx << " with L2 index " << j + 1 << "\n";
        if (L1[(j + 1) - pivotIdx] != L2[j + 1]) return false;
        //cout << "Match!\n";
    }
    // Compare values to the left of the pivot index in L2
    for (int k = 0; k < pivotIdx; k++) {
        //cout << "Comparing L1 index " << (j + 1 - pivotIdx) + k << " with L2 index " << k << "\n";
        if (L1[(j + 1 - pivotIdx) + k] != L2[k]) return false;
        //cout << "Match!\n";
    }
    return true;
}

/* ============================================================================
Comparison of singly linked lists, using L1 as the reference. O(n) time, O(n) space.
============================================================================ */
bool compareSLinkedLists(const SLinkedList<int>& L1, const SLinkedList<int>& L2) {
    if (L1.getSize() != L2.getSize()) return false;

    bool ret = false;
    // create a copy of L2 and L1 since they will be altered otherwise
    SLinkedList<int> * tempL2 = new SLinkedList<int>;
    *tempL2 = L2; 
    SLinkedList<int> * tempL1 = new SLinkedList<int>;
    *tempL1 = L1; 
    int n = 0;

    // adjust L2's copy until the values at the front of L1 and L2 match
    while((L1.front() != tempL2->front()) && n < tempL2->getSize()) {
        int oldFront = tempL2->front();
        tempL2->removeFront();
        tempL2->addBack(oldFront);
        n++;
    }
    //cout << "Found matching value " << tempL2->front() << " at L2 index " << n << "\n";
    n = 0;
    // compare element by element until a mismatch is found or we've cycled through the entire list
    while((tempL1->front() == tempL2->front()) && n < tempL2->getSize()) {
        //cout << "tempL1: \n";
        //tempL1->printList();
        //cout << "tempL2: \n";
        //tempL2->printList();
        //cout << "Front values match! tempL1.front() = tempL2.front() = " << tempL1->front() << "\n";
        // move fronts to the end and keep comparing fronts
        int oldFront = tempL2->front();
        tempL2->removeFront();
        tempL2->addBack(oldFront);
        oldFront = tempL1->front();
        tempL1->removeFront();
        tempL1->addBack(oldFront);
        n++;
    }
    if (n == tempL2->getSize()) ret = true;

    delete tempL2;
    delete tempL1;
    return ret;
}

/* ============================================================================
Comparison of circular linked lists, using L1 as the reference. O(n) time, O(n) space.
============================================================================ */
bool compareCircularLinkedLists(const CircleList<int>& L1, const CircleList<int>& L2) {
    if (L1.getSize() != L2.getSize()) return false;
    
    bool ret = false;
    // create a copy of L2 and L1 since they will be altered otherwise
    CircleList<int> * tempL2 = new CircleList<int>;
    *tempL2 = L2; 
    CircleList<int> * tempL1 = new CircleList<int>;
    *tempL1 = L1;
    int n = 0;

    // advance list cursor until front items match
    while ((L1.front() != tempL2->front()) && n < tempL2->getSize()) {
        tempL2->advance();
        n++;
    }
    if (n == tempL2->getSize()) return false;
    //cout << "Found matching value " << tempL2->front() << " at L2 index " << n << "\n";
    n = 0;
    while((tempL1->front() == tempL2->front()) && n < tempL2->getSize()) {
        //cout << "tempL1: \n";
        //tempL1->printList();
        //cout << "tempL2: \n";
        //tempL2->printList();
        //cout << "Front values match! tempL1.front() = tempL2.front() = " << tempL1->front() << "\n";
        // advance cursor for each list for subsequent comparisons
        tempL1->advance();
        tempL2->advance();
        n++;
    }
    if (n == tempL2->getSize()) ret = true;

    delete tempL1;
    delete tempL2;
    return ret;
}

/* ============================================================================
Comparison of doubly linked lists, using L1 as the reference
============================================================================ */
bool compareDLinkedLists(const DLinkedList<int>& L1, const DLinkedList<int>& L2) {
    
    if (L1.getSize() != L2.getSize()) return false;

    // create a copy of L2 and L1 since they will be altered otherwise
    bool ret = false;
    // create a copy of L2 and L1 since they will be altered otherwise
    DLinkedList<int> * tempL2 = new DLinkedList<int>;
    *tempL2 = L2; 
    DLinkedList<int> * tempL1 = new DLinkedList<int>;
    *tempL1 = L1;
    int n = 0;

    // Find the point at which the two lists front elements match
    while (/*!tempL1->empty() && !tempL2->empty()*/(L1.front() != tempL2->front()) && n < tempL2->getSize()) {
        // Move L2 front to back
        if (tempL2->front() > tempL1->front()) {
            //cout << "Moving list front to back...\n";
            int oldFront = tempL2->front();
            tempL2->removeFront(); // Only affects the copy
            tempL2->addBack(oldFront);
        } 
        // Move L2 back to front
        else if (tempL2->front() < tempL1->front()) {
            //cout << "Moving list back to front...\n";
            int oldBack = tempL2->back();
            tempL2->removeBack(); // Only affects the copy
            tempL2->addFront(oldBack);
        } 
        n++;
    }

    //tempL2->printList();
    //cout << tempL2->getSize() << "\n";
    n = tempL2->getSize();
    // Compare element by element. Don't actually need to check the front here.
    while (n > 0 && (tempL1->front() == tempL2->front())) {
        //cout << tempL2->front() << "\n";
        //cout << tempL1->front() << "\n";
        tempL2->removeFront();  // Only affects the copy
        tempL1->removeFront();  // Only affects the copy
        n--;
    }
    //tempL1->printList();
    //tempL2->printList();
    // If both lists are empty theyre equivalent
    return (tempL2->empty() && tempL1->empty());
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
main()
============================================================================ */
void printConsoleMenu(const char choice, const int ds) {
    //cout << "Select an option\n";
    switch(choice) {
        case('a'):
            {
            printCenteredTitle(" Enter data ", 40);
            cout << "Enter an input size as an integer in the range [2, 10]: ";
            int size = 0;
            cin >> size;
            int * arr = new int[size];
            switch(ds) {
                case(ARRAY):
                    break;
                case(SING_LL):
                    break;
                case(DOUB_LL):
                    break;
                case(CIRC_LL):
                    break;
                default:
                    break;
            }
            break;
            }
        case('b'):
            printCenteredTitle(" Choose a data structure ", 40);
            for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
                cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
            }
            break;
        default:
            printCenteredTitle(" Select an option ", 40);
            for (int i = 0; i < sizeof(OPTIONS)/sizeof(OPTIONS[0]); i++) {
                cout << static_cast<char>(0x61 + i) << ") " << OPTIONS[i] << "\n";
            }
            break;
    }
    cout << "\n";
    cout << "Select an option (use '" << QUIT_CHAR << "' to quit): ";
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
                                  END FILE
============================================================================ */
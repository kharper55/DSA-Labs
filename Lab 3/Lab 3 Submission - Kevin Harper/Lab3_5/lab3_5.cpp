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
#include "HeapPriorityQueue.hpp"

// Prototypes
void buildMaxHeapFromArr(const int * arr, const int arrSize, HeapPriorityQueue<int>& maxHeap);
void heapSort(int * arr, const int arrSize, HeapPriorityQueue<int>& maxHeap);
void printIntArray(const char * arrLabel, int arr[], int arrLen, int maxColWidth);

using namespace std;

#define COL_WIDTH       65

/* ============================================================================
main()
============================================================================ */
int main() {
    const int arrSize = 8;
    int arr[arrSize] = {6, 7, 1, 2, 4, 13, 5, 9};
    
    HeapPriorityQueue<int> maxHeap;
    HeapPriorityQueue<int> maxHeap2;
    HeapPriorityQueue<int, std::less<int>> minHeap;

    cout << "\nWelcome to heapsort demo!\n\n";

    for (int i = 0; i < arrSize; i++) {
        minHeap.insert(arr[i]);
    }

    buildMaxHeapFromArr(arr, arrSize, maxHeap);

    for (int i = arrSize - 1; i >= 0; i--) {
        cout << "Max Heap Root: " << maxHeap.root() << "\t\tMin Heap Root: " << minHeap.root() << "\n";
        maxHeap.removeRoot();
        minHeap.removeRoot();
        //cout << "Max Heap Size: " << maxHeap.size() << "\n"; 
    }

    heapSort(arr, arrSize, maxHeap2);
    printIntArray("Heapsorted Array", arr, arrSize, COL_WIDTH);

	return 0;
}

/* ============================================================================
============================================================================ */
void buildMaxHeapFromArr(const int * arr, const int arrSize, HeapPriorityQueue<int>& maxHeap) {
    for (int i = 0; i < arrSize; i++) {
        maxHeap.insert(arr[i]);
    }
}

/* ============================================================================
============================================================================ */
void heapSort(int * arr, const int arrSize, HeapPriorityQueue<int>& maxHeap) {
    int tempSize = arrSize - 1;
    buildMaxHeapFromArr(arr, arrSize, maxHeap);
    while(tempSize >= 0) {
        arr[tempSize--] = maxHeap.root();
        maxHeap.removeRoot();
    }
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
Print an integer array to the console, with maxColWidth entries per line.
============================================================================ */
void printIntArray(const char * arrLabel, int arr[], int arrLen, int maxColWidth) {
    cout << "\nArray contents for " << arrLabel << ":\n{";
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i];

        // Separate elements by a comma unless end of array is reached
        if (i != arrLen - 1) cout << ", ";
        else cout << "}";

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
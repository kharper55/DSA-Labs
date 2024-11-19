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
#include <cstring>                  // For strlen
#include <queue>                    // For STL queue

// Header includes
#include "CircularQueue.hpp"
#include "ArrayQueue.hpp"
#include "Computer.hpp"

using namespace std;

// Constants
const string DS_OPTIONS[3] = {
    "STL queue",
    "Array-based queue",
    "Circular linked list-based queue",
};

const char QUIT_CHAR = 'x';

enum {
    STL_QUEUE,
    ARRAY_QUEUE,
    LINKED_QUEUE
};

#define NUM_COMPUTERS 8

// Function prototypes
void servicePrintQueueSTL(queue<Computer>& printerQueue, const string& printerNetwork);
void servicePrintQueueArray(ArrayQueue<Computer>& printerQueue, const string& printerNetwork);
void servicePrintQueueLinked(CircularQueue<Computer>& printerQueue, const string& printerNetwork);
void printCenteredTitle(const char * title, const int col_width);

/* ============================================================================
main()
============================================================================ */
int main() {
      
     queue<Computer> queueSTL;             // STL queue
     ArrayQueue<Computer> queueArray;      // Array-based queue
     CircularQueue<Computer> queueLinked;  // Circular linked list-based queue
     queue<Computer> queueSTLCopy;         // Copies for modification are repopulated on each iteration
     ArrayQueue<Computer> queueArrayCopy;
     CircularQueue<Computer> queueLinkedCopy;
     Computer dissatisfiedBrowser;         // User who will leave the printerNetwork
     const string printerNetwork = "Library WiFi 5GHz";
     const string alternativeNetwork = "Mobile Hotspot";
     char userChoice;    // Should make this a string and accept only the first char, discarding remainder
     bool userQuit = false;
     
     const string computerNames[NUM_COMPUTERS] = {
        "Kevin's PC", "Kyle's PC", "Brian's PC", "Keith's PC",
        "Andrew's PC", "Jonathan's PC", "David's PC", "Joseph's PC"
     };

     // Populate the queues
     for (int i = 0; i < NUM_COMPUTERS; i++) {
          Computer pc(computerNames[i], printerNetwork);
          queueSTL.push(pc);
          queueArray.enqueue(pc);
          queueLinked.enqueue(pc);
     }

     cout << "\nWelcome to printer queue demo!\n";

     while(!userQuit) {
          printCenteredTitle(" Data structure selection ", 40);
          for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
               cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
          }
          printCenteredTitle(" Input ", 40);
          cout << "Select an implementation for printer\nqueue (use '" << QUIT_CHAR << "' to quit): ";
          cin >> userChoice;
          if (userChoice != QUIT_CHAR) {
               int ds = static_cast<int>(userChoice - 0x61);
               switch(ds) {
                    case(STL_QUEUE): // STL queue 
                    {   
                         printCenteredTitle(" STL Queue ", 40);
                         queueSTLCopy = queueSTL; // invoke copy constructor/operator overload
                         // Network change for front member
                         dissatisfiedBrowser = queueSTLCopy.front();
                         cout << dissatisfiedBrowser.getName() << " is leaving the printer network...\n\n";
                         queueSTLCopy.front().changeNetwork("Mobile Hotspot");
                         // Service users in order of requests 
                         servicePrintQueueSTL(queueSTLCopy, printerNetwork);
                         break;
                    }
                    // Note: should probably define a copy constructor here
                    //       also changed front() to return a modifiable node
                    case(ARRAY_QUEUE): // Array based queue
                    {   
                         printCenteredTitle(" Array-based Queue ", 40);
                         queueArrayCopy = queueArray; // invoke copy constructor/operator overload
                         // Network change for front member
                         dissatisfiedBrowser = queueArrayCopy.front();
                         cout << dissatisfiedBrowser.getName() << " is leaving the printer network...\n\n";
                         queueArrayCopy.front().changeNetwork("Mobile Hotspot");
                         // Service users in order of requests 
                         servicePrintQueueArray(queueArrayCopy, printerNetwork);
                         break;
                    }
                    // Note: should probably define a copy constructor here
                    //       also changed front() to return a modifiable node
                    case(LINKED_QUEUE): // Circular linked list queue
                    {
                         printCenteredTitle(" Circular linked list-based Queue ", 40);
                         queueLinkedCopy = queueLinked; // invoke copy constructor/operator overload
                         // Network change for front member
                         dissatisfiedBrowser = queueLinkedCopy.front();
                         cout << dissatisfiedBrowser.getName() << " is leaving the printer network...\n\n";
                         queueLinkedCopy.front().changeNetwork("Mobile Hotspot");
                         // Service users in order of requests 
                         servicePrintQueueLinked(queueLinkedCopy, printerNetwork);
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
servicePrintQueue()
============================================================================ */
void servicePrintQueueSTL(queue<Computer>& printerQueue, const string& printerNetwork) {
     while(!printerQueue.empty()) {
          if (printerQueue.front().getNetwork() == printerNetwork) {
               cout << "Servicing " << printerQueue.front().getName() << "...\n";
               // Perform print job for user
          }
          else cout << printerQueue.front().getName() << " is no longer discoverable.\n";
          printerQueue.pop();
     }
     cout << "\nAll member's serviced.\n";
}

/* ============================================================================
servicePrintQueue()
============================================================================ */
void servicePrintQueueArray(ArrayQueue<Computer>& printerQueue, const string& printerNetwork) {
     while(!printerQueue.empty()) {
          if (printerQueue.front().getNetwork() == printerNetwork) {
               cout << "Servicing " << printerQueue.front().getName() << "...\n";
               // Perform print job for user
          }
          else cout << printerQueue.front().getName() << " is no longer discoverable.\n";
          printerQueue.dequeue();
     }
     cout << "\nAll member's serviced.\n";
}

/* ============================================================================
servicePrintQueue()
============================================================================ */
void servicePrintQueueLinked(CircularQueue<Computer>& printerQueue, const string& printerNetwork) {
     while(!printerQueue.empty()) {
          if (printerQueue.front().getNetwork() == printerNetwork) {
               cout << "Servicing " << printerQueue.front().getName() << "...\n";
               // Perform print job for user
          }
          else cout << printerQueue.front().getName() << " is no longer discoverable.\n";
          printerQueue.dequeue();
     }
     cout << "\nAll member's serviced.\n";
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
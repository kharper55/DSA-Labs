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
#include <sstream>
#include <cstring>       // For stringlen
#include <string>        // for string class
#include <random>        // For random device and mersenne twister implementation
#include <set>           // For checking uniqueness of random integers

// Header includes
#include "Scheduler.hpp"

using namespace std;

// Prototypes

#define COL_WIDTH       65
#define QUIT_CHAR       'x'

/* ============================================================================
main()
============================================================================ */
int main() {
    
    Scheduler scheduler;
    bool userQuit = false;
    string userInput;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> priorities(-20, 19); 
    set<int> uniquePriorities;
    int priority;
    uniform_int_distribution<int> durations(1, 100); 
    int duration;
    int numJobs = 4;
    string jobName;

    cout << "\nWelcome to OS scheduler demo!\n\n";
    
    // Populate scheduler with random data
    for (int i = 0; i < numJobs; i++) {
        while(1) {
            priority = priorities(gen);
            if (uniquePriorities.find(priority) == uniquePriorities.end()) {
                break;
            }
        };
        duration = durations(gen);
        jobName = "Job" + std::to_string(i + 1);
        scheduler.addJob(jobName, duration, priority);
    }

    // List scheduler population
    scheduler.printJobs();

    while (!userQuit) {
        cout << "Add new job (y/n, use " << QUIT_CHAR << " to quit)?: ";
        getline(std::cin, userInput); // Read the entire line of input

        if (userInput.length() == 1) {
            char userChar = userInput[0];
            if (userChar == QUIT_CHAR || userChar == QUIT_CHAR + 0x20) {
                userQuit = true; // Quit the loop
            } 
            else if (userChar == 'y' || userChar == 'Y') {
                // Add a new job
                while (true) {
                    cout << "Enter the job's duration as an integer [1:100] (use x to quit)?: ";
                    getline(std::cin, userInput);
                    if (userInput == "x" || userInput == "X") {
                        userQuit = true;
                        break;
                    }

                    std::istringstream iss(userInput);
                    if (iss >> duration && duration >= 1 && duration <= 100) {
                        break; // Valid duration
                    } else {
                        cout << "Invalid input. Please enter an integer between 1 and 100." << endl;
                    }
                }
                if (userQuit) continue;

                while (true) {
                    cout << "Enter the job's priority as an integer [-19:20] (use x to quit)?: ";
                    getline(std::cin, userInput);
                    if (userInput == "x" || userInput == "X") {
                        userQuit = true;
                        break;
                    }

                    std::istringstream iss(userInput);
                    if (iss >> priority && priority >= -19 && priority <= 20) {
                        break; // Valid priority
                    } else {
                        cout << "Invalid input. Please enter an integer between -19 and 20." << endl;
                    }
                }
                if (userQuit) continue;

                cout << "Processing command 'add job " << "Job" + to_string(++numJobs)
                    << " with length " << duration << " and priority " << priority << "'" << endl;
                scheduler.addJob("Job" + to_string(numJobs), duration, priority);
            } 
            else if (userChar == 'n' || userChar == 'N') {
                cout << "Processing command 'No new job this slice'" << endl;
            }
            else {
                cout << "Invalid input. Please enter a single character ('y', 'n', or 'x')." << endl;
                continue;
            }
        } 
        else if (userInput.length() == 0) {
            // Interpret empty string as 'n'
            cout << "Processing command 'No new job this slice'" << endl;
        } 
        else {
            cout << "Invalid input. Please enter a single character ('y', 'n', or 'x')." << endl;
            continue; // dont run the time slice on an invalid input
        }

        scheduler.runTimeSlice();
    }

	return 0;
}

/* ============================================================================
                                  END FILE
============================================================================ */
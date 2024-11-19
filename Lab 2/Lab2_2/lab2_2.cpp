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
#include "Team.hpp"

// Function prototypes
void printCenteredTitle(const char * title, const int col_width);

#define TEAM_SIZE 8

using namespace std;

/* ============================================================================
main()
============================================================================ */
int main() {

    const string teamMemberNames[TEAM_SIZE] = {
        "Kevin", "Kyle", "Brian", "Keith",
        "Andrew", "Jonathan", "David", "Joseph"
    };

    Team myTeam(TEAM_SIZE, "Trojans");

    for (int i = 0; i < TEAM_SIZE; i++) {
        if (i < TEAM_SIZE/2) myTeam.vPush(teamMemberNames[i]);
        else myTeam.jvPush(teamMemberNames[i]);
    }

    printCenteredTitle(" At the start of the season ", 50);
    cout << "Team Size: " << myTeam.getTeamSize() << "\n\n";
    myTeam.printTeam();

    // The team member who last joined both the varisty and JV squad has been cut
    // due to budget constraints

    printCenteredTitle(" After budget cuts ", 50);
    myTeam.jvPop();
    myTeam.vPop();
    cout << "Team Size: " << myTeam.getTeamSize() << "\n\n";
    myTeam.printTeam();

	return 0;
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
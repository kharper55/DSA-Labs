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
#include <ctime>
#include <vector>
#include <string>

// Header includes
#include "GraphAdjacencyMatrix.hpp"

// Prototypes
void printCenteredTitle(const char * title, const char buffChar, const int col_width);

// Helper function to check if the input string is a number
bool isNumber(const std::string& str) {
    // Check if the string is empty
    if (str.empty()) return false;

    // Check if all characters are digits
    for (char ch : str) {
        if (!isdigit(ch)) return false;
    }
    return true;
}

// Globals

using namespace std;

#define COL_WIDTH       65
#define QUIT_CHAR       'x'

/* ============================================================================
main()
============================================================================ */
int main() {
      
      cout << "Welcome to team transfer demo!\n" << endl;

      // List of NFL teams
      vector<string> nflTeams = {
            "Arizona Cardinals", "Atlanta Falcons", "Baltimore Ravens", "Buffalo Bills",
            "Carolina Panthers", "Chicago Bears", "Cincinnati Bengals", "Cleveland Browns",
            "Dallas Cowboys", "Denver Broncos", "Detroit Lions", "Green Bay Packers",
            "Houston Texans", "Indianapolis Colts", "Jacksonville Jaguars", "Kansas City Chiefs",
            "Las Vegas Raiders", "Los Angeles Chargers", "Los Angeles Rams", "Miami Dolphins",
            "Minnesota Vikings", "New England Patriots", "New Orleans Saints", "New York Giants",
            "New York Jets", "Philadelphia Eagles", "Pittsburgh Steelers", "San Francisco 49ers",
            "Seattle Seahawks", "Tampa Bay Buccaneers", "Tennessee Titans", "Washington Commanders"
      };

      int numTeams = nflTeams.size();

      // Create a graph with the number of teams
      AdjacencyMatrixGraph<string, int> graph(numTeams);

      // Set team names as vertices in the graph
      for (int i = 0; i < numTeams; ++i) {
            graph.setVertex(i, nflTeams[i]);
      }

      // Seed the random number generator
      srand(time(0));

      // Randomly generate player transfers (edges) between all pairs of teams
      for (int i = 0; i < numTeams; ++i) {
            for (int j = i + 1; j < numTeams; ++j) {
                  int transfers = rand() % 10;  // Random number between 0 and 9
                  graph.addEdge(i, j, transfers);
            }
      }

      // Print the adjacency matrix with player transfers
      cout << "Adjacency Matrix (Player Transfers):\n";
      graph.printMatrix();

      // Optionally, display the teams' names with their corresponding vertex index
      cout << "\nTeams and their corresponding indices:\n";
      for (int i = 0; i < numTeams; ++i) {
            cout << i << ": " << nflTeams[i] << endl;
      }

      string userInput;
      char choice;

      do {
            // Display options to the user
            printCenteredTitle(" Choose an option ", '=', COL_WIDTH);
            cout << "1. Total transfers for a team\n";
            cout << "2. Transfers between two teams\n";
            cout << "\nEnter your choice (or 'x' to quit): ";
            getline(cin, userInput);

            // Check if the input is to quit
            if (userInput == "x" || userInput == "X") {
                  break;
            }

            // Check if the input is a valid number for the choice
            if (isNumber(userInput)) {
                  choice = userInput[0];  // Only take the first character as the choice
            } 
            else {
                  cout << "\nInvalid choice. Please enter a valid option.\n";
                  continue;
            }

            switch (choice) {
                  case '1': {
                        // Get total transfers for a team
                        cout << "\nEnter the team number (0 to 31): ";
                        getline(cin, userInput);

                        // Check if input is valid
                        if (userInput == "x" || userInput == "X") break;
                        if (!isNumber(userInput)) {
                              cout << "\nInvalid input! Please enter a valid team number.\n";
                              continue;
                        }

                        int teamNumber = stoi(userInput);
                        if (teamNumber < 0 || teamNumber >= 32) {
                              cout << "\nInvalid team number!\n";
                        } else {
                              cout << "\nTotal transfers for team " << nflTeams[teamNumber] << ": " << graph.sumIncidentWeights(teamNumber) << ".\n";
                        }
                        break;
                  }
                  case '2': {
                        // Get transfers between two teams
                        int teamNumber1, teamNumber2;
                        cout << "\nEnter the first team number (0 to 31): ";
                        getline(cin, userInput);

                        if (userInput == "x" || userInput == "X") break;
                        if (!isNumber(userInput)) {
                              cout << "\nInvalid input! Please enter a valid team number.\n";
                              continue;
                        }
                        teamNumber1 = stoi(userInput);

                        cout << "\nEnter the second team number (0 to 31): ";
                        getline(cin, userInput);

                        if (userInput == "x" || userInput == "X") break;
                        if (!isNumber(userInput)) {
                              cout << "\nInvalid input! Please enter a valid team number.\n";
                              continue;
                        }
                        teamNumber2 = stoi(userInput);

                        if (teamNumber1 < 0 || teamNumber1 >= 32 || teamNumber2 < 0 || teamNumber2 >= 32) {
                              cout << "\nInvalid team number(s)!\n";
                        } 
                        else {
                              cout << "\nTransfers between teams " << nflTeams[teamNumber1] << " and " << nflTeams[teamNumber2] << ": " << graph.getEdgeWeight(teamNumber1, teamNumber2) << ".\n";
                        }
                        break;
                  }
                  default:
                        cout << "\nInvalid choice! Please enter a valid option.\n";
                  break;
            }
      } 
      while (true);

    return 0;
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
                                  END FILE
============================================================================ */
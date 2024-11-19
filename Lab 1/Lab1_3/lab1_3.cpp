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
#include <fstream>                  // For file IO
#include <cstring>                  // For strlen
#include <random>                   // For random device and mersenne twister implementation
#include <string>

// Header includes
#include "ticTacToe.hpp"

using namespace std;

// defined in ticTacToe.cpp
extern const int X, O, EMPTY;		// possible marks
extern int board[3][3];				// playing board
extern int currentPlayer;

// Function Prototypes
void printCenteredTitle(const char * title, int col_width);

#define QUIT_CHAR 'x'
#define BACK_CHAR 'b'

/* ============================================================================
main()
============================================================================ */
int main() {
    
    bool userXQuit = false;
    bool userOQuit = false;
    bool userBack = false;
    bool invalidEntry = true;
    int row = 0;
    int col = 0;
    string rowBuff = "";
    string colBuff = "";
    int winner = EMPTY;

    cout << "\nWelcome to Tic-Tac-Toe!\n";
    
    while (!(userXQuit || userOQuit)) {
        char startGame = 'n';

        random_device rd;
        mt19937 gen(rd());

        // Produces random integer values i, uniformly distributed on the closed interval [a,b] (inclusive of endpoints)
        // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        uniform_int_distribution<int> dis(0, 1);

        currentPlayer = 2 * dis(gen) - 1; // Player with first turn has an advantage in tic tac toe - randomize who goes first

        cout << "\nWould you like to start a new game? (y/n): ";
        cin >> startGame;

        if (startGame == 'y' || startGame == 'Y') {
            clearBoard();
            bool gameOver = false;
            int turn = 1;
            while(!(userXQuit || userOQuit) && !gameOver) {
                
                if (!userBack) { // Only print out the board given user did not go back to change their row selection
                    printCenteredTitle(((currentPlayer == X) ? " X's turn " : " O's turn "), CONSOLE_WIDTH);
                    printBoard();
                    cout << "\n";
                }
            
                // User chooses a row
                while(true) {   
                    if (userBack) userBack = false; // reset
                    cout << "\nEnter a row (use '" << QUIT_CHAR << "' to quit): ";
                    cin >> rowBuff;
                    if (rowBuff[0] == QUIT_CHAR) { // User quit
                        userXQuit = (currentPlayer == X);
                        userOQuit = !userXQuit;
                        break;
                    }
                    if (rowBuff.length() == 1) {
                        row = static_cast<int>(rowBuff[0] - 0x30);
                        if (row >= ROW_MIN && row <= ROW_MAX) break;
                        else cout << "\nInvalid entry.\n";
                    }
                    else cout << "\nInvalid entry.\n";
                }

                // User chooses a column
                while(true && !(userXQuit || userOQuit)) {   
                    cout << "\nEnter a column (use '" << QUIT_CHAR << "' to quit or '" 
                         << BACK_CHAR << "' to go back): ";
                    cin >> colBuff;
                    if (colBuff[0] == QUIT_CHAR) { // User quit
                        userXQuit = (currentPlayer == X);
                        userOQuit = !userXQuit;
                        break;
                    }
                    else if (colBuff[0] == BACK_CHAR) { // User wants to change row
                        userBack = true;
                        break;
                    }
                    if (colBuff.length() == 1) {
                        col = static_cast<int>(colBuff[0] - 0x30);
                        if (col >= COL_MIN && col <= COL_MAX) break;
                        else cout << "\nInvalid entry.\n";
                    }
                    else cout << "\nInvalid entry.\n";
                }

                // Returns false if mark already exists in chosen spot. putMark handles player switching
                if (!userBack && !(userXQuit || userOQuit) && putMark(row, col)) {
                    // putMark swaps player, hence opposite logic in ternary
                    cout << "\n" << ((currentPlayer == X) ? "O " : "X ") << "played (row, col): (" << row << ", " << col << ").\n";
                    if (turn >= 5) { // Minimum turns required for a win is 5
                        winner = getWinner(); // EMPTY means a tie has occurred.
                        if (winner != EMPTY) {
                            cout << "\nGame over. " << (winner == X ? 'X' : 'O') << " wins!\n";
                            gameOver = true;
                        }
                        // Tie is certain to occur when the board is full and winner != EMPTY
                        // An improvement to the program could be an early termination if a tie is certain to occur
                        else if (turn > 8) {
                            cout << "\nGame over. Result is a tie.\n";
                            gameOver = true;
                        }
                    }
                    turn++;
                }
            }
            if (!gameOver) { // If gameOver is not true at this point, somebody quit
                cout << ((userXQuit) ? "\nX forfeited. " : "\nO forfeited. ") << "Shame on them!\n";
            }
            else {
                printCenteredTitle(" Final Board ", CONSOLE_WIDTH);
                printBoard();
                cout << "\n";
            }
        }
        else userXQuit = true;
        cout << "\n";
    } 

	return 0;
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
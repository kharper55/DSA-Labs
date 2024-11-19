
#include <cstdlib>				// system definitions
#include <iostream>				// I/O definitions
#include "ticTacToe.hpp"
using namespace std;			// make std:: accessible

const int X = 1, O = -1, EMPTY = 0;		// possible marks
int board[ROW_MAX + 1][COL_MAX + 1];    // playing board
int currentPlayer;				        // current player (X or O)

void clearBoard() {				        // clear the board
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = EMPTY;	    // every cell is empty
    //currentPlayer = X;				// handled elsewhere
}

bool putMark(int i, int j) {			// mark row i column j
    // row, col validity checked elsewhere
    if(!markExists(i, j)/*(i >= ROW_MIN && i <= ROW_MAX) && (j >= COL_MIN && j <= COL_MAX)*/) {
        board[i][j] = currentPlayer;		// mark with current player
        currentPlayer = -currentPlayer;		// switch players
        return true;
    }
    cout << "\nA mark already exists here.\n";
    return false;
}

bool markExists(int i , int j) { // check if spot is already populated
    if (board[i][j] != EMPTY) return true;
    else return false;
}

bool isWin(int mark) {			// is mark the winner?
    int win = 3*mark;		    // +3 for X and -3 for O
    return ((board[0][0] + board[0][1] + board[0][2] == win)	// row 0
	 || (board[1][0] + board[1][1] + board[1][2] == win)	    // row 1
	 || (board[2][0] + board[2][1] + board[2][2] == win)	    // row 2
	 || (board[0][0] + board[1][0] + board[2][0] == win)	    // column 0
	 || (board[0][1] + board[1][1] + board[2][1] == win)	    // column 1
	 || (board[0][2] + board[1][2] + board[2][2] == win)	    // column 2
	 || (board[0][0] + board[1][1] + board[2][2] == win)	    // diagonal
	 || (board[2][0] + board[1][1] + board[0][2] == win));	    // diagonal
}

int getWinner() {				// who wins? (EMPTY means tie)
    if (isWin(X)) return X;
    else if (isWin(O)) return O;
    else return EMPTY;
}

void printBoard() {				// print the board
    for (int i = ROW_MIN; i <= ROW_MAX; i++) {
        for (int k = CONSOLE_WIDTH/2 - (5/2 + 1); k > 0; k--) {
            cout << " ";
        }
        for (int j = COL_MIN; j <= COL_MAX; j++) {
            
            switch (board[i][j]) {
                case X:		cout << "X"; break;
                case O:		cout << "O"; break;
                case EMPTY:	cout << " "; break;
            }
            if (j < COL_MAX) cout << "|";			// column boundary
        }
        if (i < ROW_MAX) {
            cout << "\n";
            for (int k = CONSOLE_WIDTH/2 - (5/2 + 1); k > 0; k--) {
                cout << " ";
            }
            cout << "-+-+-\n";		// row boundary
        }
    }
}
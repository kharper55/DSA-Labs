#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#define ROW_MAX 2
#define COL_MAX ROW_MAX
#define ROW_MIN 0
#define COL_MIN ROW_MIN

#define CONSOLE_WIDTH 60

extern const int X, O, EMPTY;		// possible marks
extern int board[ROW_MAX + 1][COL_MAX + 1];				// playing board
extern int currentPlayer;

void clearBoard();
bool putMark(int i, int j);
bool isWin(int mark);
int getWinner();
bool markExists(int i , int j);
void printBoard();

#endif // TIC_TAC_TOE_HPP
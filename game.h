#ifndef GAME_H
#define GAME_H

// Function prototypes
void initializeBoard(int* board, int size);
void printBoard(int* board, int size, int* score, int* bestScore);
void mergeRight(int* row, int size, int* score);
void mergeLeft(int* row, int size, int* score);
void addRandomNumber(int* board, int size);
void showMenu();
void getUserInputAndMove(int* board, int size, int* gameStarted, int* gameExit,int* score, int* bestScore );
void playGame(int* board, int size, int scoreToWin, int* bestScore);
int noMoreMoves(int* board, int size);

#endif // GAME_H


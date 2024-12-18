#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "move.h"


#define BreakVal '|'
#define BorderVal '-'


// Function to initialize the game board
void initializeBoard(int* board, int size) {
    for (int i = 0; i < size * size; i++) {
        board[i] = 0;
    }
}

int noMoreMoves(int* board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int current = board[i * size + j];

            // Check if the current cell is empty
            if (current == 0) {
                return 0;
            }

            // Check adjacent cells for possible merges
            if (i > 0 && current == board[(i - 1) * size + j]) {
                return 0; // Check above
            }
            if (i < size - 1 && current == board[(i + 1) * size + j]) {
                return 0; // Check below
            }
            if (j > 0 && current == board[i * size + (j - 1)]) {
                return 0; // Check left
            }
            if (j < size - 1 && current == board[i * size + (j + 1)]) {
                return 0; // Check right
            }
        }
    }
    return 1; // No empty cells or mergeable adjacent tiles
}

// Function to print the game board
void printBoard(int* board, int size, int* score, int* bestScore) {
	printf("\tScore : %4d, \tBest Score : %4d\n", *score, *bestScore);
	printf("   ------------------------------------------\n\n");
	for (int i = 0 ; i <= size*7 ; i ++)
		printf("%c", BorderVal);
    printf("\n");
    for (int i = 0; i < size; i++) {
    	printf("%c",BreakVal);
    	
        for (int j = 0; j < size; j++) {
            printf("%5d |", board[i * size + j]);
        }
		printf("\n");
		for (int i = 0 ; i <= size*7 ; i ++)
			printf("%c", BorderVal);
		printf("\n");
        printf("\n");
    }
}

// Function to add a random number (2 or 4) to the board
void addRandomNumber(int* board, int size) {
    int emptyCells[size * size];
    int emptyCount = 0;

    // Find all empty cells
    for (int i = 0; i < size * size; i++) {
        if (board[i] == 0) {
            emptyCells[emptyCount++] = i;
        }
    }

    // If there are empty cells, add a random number to a random cell
    if (emptyCount > 0) {
        int randomIndex = emptyCells[rand() % emptyCount];
        board[randomIndex] = (rand() % 10 < 7) ? 2 : 4; // 70% chance for 2, 30% for 4
    }
}

// Function to merge a row to the left
void mergeLeft(int* row, int size, int* score) {
    for (int i = 0; i < size - 1; i++) {
        if (row[i] == row[i + 1] && row[i] != 0) {
            row[i] *= 2;  // Merge the tiles
            *score += row[i];
            row[i + 1] = 0;  // Set the merged tile to 0
        }
    }
}

// Function to merge a row to the right
void mergeRight(int* row, int size, int* score) {
    for (int i = size - 1; i > 0; i--) {
        if (row[i] == row[i - 1] && row[i] != 0) {
            row[i] *= 2;  // Merge the tiles
            *score += row[i];
            row[i - 1] = 0;  // Set the merged tile to 0
        }
    }
}

void showMenu() {
    printf("\nPlease choose one of the following options:\n");
    printf("N/n - New Game\n");
    printf("R/r - Move Right\n");
    printf("L/l - Move Left\n");
    printf("U/u - Move Up\n");
    printf("D/d - Move Down\n");
    printf("E/e - Exit\n");
}

// Function to get user input for move direction
void getUserInputAndMove(int* board, int size, int* gameStarted, int* gameExit,int* score, int* bestScore ) {
    char direction;

    if (*gameStarted == 0) {
        printf("Need to start game first.\n");
        return;  // If game hasn't started, don't process any movement
    }

    showMenu();  // Show the menu options after every move

    while (1) {
        direction = getchar();  // Read a single character
        getchar();
        if (direction == '\n') continue;  // Ignore newline characters
        
        switch (direction) {
            case 'R':
            case 'r':
                moveRight(board, size, score);  // Move tiles right
                addRandomNumber(board, size);  // Add a random number after every move
                break;
            case 'L':
            case 'l':
                moveLeft(board, size, score);  // Move tiles left
                addRandomNumber(board, size);  // Add a random number after every move
                break;
            case 'U':
            case 'u':
                moveUp(board, size, score);  // Move tiles up
                addRandomNumber(board, size);  // Add a random number after every move
                break;
            case 'D':
            case 'd':
                moveDown(board, size, score);  // Move tiles down
                addRandomNumber(board, size);  // Add a random number after every move
                break;
            case 'E':
            case 'e':
                *gameExit = 1;  // Set the gameExit flag to 1 to stop the game
                printf("Exiting the game.\n");
                return;
            default:
                printf("Invalid input. Please enter one of the following: R/r, L/l, U/u, D/d, E/e.\n");
        }

	if(*score > *bestScore)
		*bestScore = *score;
        printBoard(board, size,score , bestScore);  // Print the board after each move
        return;  // End after one movement and print the board
    }
}


// Main game loop
void playGame(int* board, int size, int scoreToWin, int* bestScore) {
    int gameStarted = 0;  // Flag to track if the game has started
    int gameExit = 0;  // Flag to track if the user chose to exit the game
    int score = 0;
    while (!gameExit) {  // Continue until gameExit is set to 1
        // Show the menu if the game has not started
        if (gameStarted == 0) {
        	initializeBoard(board, size);  // Initialize the game board
        	printBoard(board, size, &score, bestScore);
            showMenu();  // Show the menu options
            char menuChoice;
            menuChoice = getchar();
            getchar();  // Consume the newline character after input
            
            switch (menuChoice) {
                case 'n':
                case 'N':
                    printf("Starting a new game.\n\n");
                    printf("------------ STARTING A GAME -----------\n");
                    printf("\tHighest tile for a win %d\t\n",scoreToWin);
                    printf("-----------------------------------------\n");
                    gameStarted = 1;  // Mark the game as started
                    addRandomNumber(board, size);  // Add random numbers
                    addRandomNumber(board, size);
                    printBoard(board, size , &score, bestScore);  // Print the board after starting the game
                    break;

                case 'r':
                case 'R':
                case 'l':
                case 'L':
                case 'u':
                case 'U':
                case 'd':
                case 'D':
                    printf("Need to start game first.\n");
                    break;

                case 'e':
                case 'E':
                    printf("Ending previous game  - your score %4d best score %4d.\n", score, *bestScore);
                    printf("Bye bye\n");
                    gameExit = 1;  // Exit the loop
                    break;

                default:
                    printf("Invalid option. Please try again.\n");
            }
        } else {
            getUserInputAndMove(board, size, &gameStarted, &gameExit, &score, bestScore);  // Perform movement
            if (gameExit) {
                break;  // Exit the loop if gameExit is set
            }

            // Check for the winning condition
            int gameOver = 0;
            for (int i = 0; i < size * size; i++) {
                if (board[i] == scoreToWin) {
                    printf("You won! Reached score: %d\n", scoreToWin);
                    gameOver = 1;
                    break;
                }
            }
                if (noMoreMoves(board, size)) {
                printf("Game Over! No more moves left.\n");
                printf("your score is %3d\n", score);
                gameOver = 1;
                break;
            }

            if (gameOver) {
            	gameExit =1;
                break;  // Exit the loop if the game is over
            }
            

        }
    }
}

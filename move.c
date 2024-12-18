#include "game.h"


// Function to shift tiles to the left (move tiles)
void moveLeft(int* board, int size, int* score) {
    for (int i = 0; i < size; i++) {
        int temp[size];
        for (int j = 0; j < size; j++) {
            temp[j] = board[i * size + j];  // Copy the row to a temporary array
        }

        int newRow[size];
        int newIndex = 0;  // Start from the leftmost side

        // Move all non-zero values to the left
        for (int j = 0; j < size; j++) {
            if (temp[j] != 0) {
                newRow[newIndex++] = temp[j];
            }
        }

        // Merge the values
        mergeLeft(newRow, size, score);

        // Fill the remaining spots with 0s
        for (int j = newIndex; j < size; j++) {
            newRow[j] = 0;
        }

        // Copy the merged row back to the board
        for (int j = 0; j < size; j++) {
            board[i * size + j] = newRow[j];
        }
    }
}


// Function to shift tiles to the right (move tiles)
void moveRight(int* board, int size, int* score) {
    for (int i = 0; i < size; i++) {
        int temp[size];
        for (int j = 0; j < size; j++) {
            temp[j] = board[i * size + j];  // Copy the row to a temporary array
        }

        int newRow[size];
        int newIndex = size - 1;  // Start from the rightmost side

        // Move all non-zero values to the right
        for (int j = size - 1; j >= 0; j--) {
            if (temp[j] != 0) {
                newRow[newIndex--] = temp[j];
            }
        }

        // Merge the values
        mergeRight(newRow, size, score);

        // Fill the remaining spots with 0s
        for (int j = newIndex; j >= 0; j--) {
            newRow[j] = 0;
        }

        // Copy the merged row back to the board
        for (int j = 0; j < size; j++) {
            board[i * size + j] = newRow[j];
        }
    }
}

// Function to shift tiles upwards (move tiles)
void moveUp(int* board, int size, int* score) {
    for (int j = 0; j < size; j++) {
        int temp[size];
        for (int i = 0; i < size; i++) {
            temp[i] = board[i * size + j];  // Copy the column to a temporary array
        }

        int newColumn[size];
        int newIndex = 0;  // Start from the topmost side

        // Move all non-zero values to the top
        for (int i = 0; i < size; i++) {
            if (temp[i] != 0) {
                newColumn[newIndex++] = temp[i];
            }
        }

        // Merge the values
        for (int i = 0; i < size - 1; i++) {
            if (newColumn[i] == newColumn[i + 1] && newColumn[i] != 0) {
                newColumn[i] *= 2;
                *score += newColumn[i];
                newColumn[i + 1] = 0;
                i++;  // Skip the next element to avoid merging twice
            }
        }

        // Fill the remaining spots with 0s
        for (int i = newIndex; i < size; i++) {
            newColumn[i] = 0;
        }

        // Copy the merged column back to the board
        for (int i = 0; i < size; i++) {
            board[i * size + j] = newColumn[i];
        }
    }
}

// Function to shift tiles downwards (move tiles)
void moveDown(int* board, int size, int* score) {
    for (int j = 0; j < size; j++) {
        int temp[size];
        for (int i = 0; i < size; i++) {
            temp[i] = board[i * size + j];  // Copy the column to a temporary array
        }

        int newColumn[size];
        int newIndex = size - 1;  // Start from the bottom-most side

        // Move all non-zero values to the bottom
        for (int i = size - 1; i >= 0; i--) {
            if (temp[i] != 0) {
                newColumn[newIndex--] = temp[i];
            }
        }

        // Merge the values
        for (int i = size - 1; i > 0; i--) {
            if (newColumn[i] == newColumn[i - 1] && newColumn[i] != 0) {
                newColumn[i] *= 2;
                *score += newColumn[i];
                newColumn[i - 1] = 0;
                i--;  // Skip the next element to avoid merging twice
            }
        }

        // Fill the remaining spots with 0s
        for (int i = newIndex; i >= 0; i--) {
            newColumn[i] = 0;
        }

        // Copy the merged column back to the board
        for (int i = 0; i < size; i++) {
            board[i * size + j] = newColumn[i];
        }
    }
}






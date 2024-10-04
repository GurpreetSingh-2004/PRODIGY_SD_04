#include <iostream>
#define N 9  // Size of the Sudoku grid (9x9)

using namespace std;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is already in the row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }

    // Check if the number is already in the column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }

    // Check if the number is in the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    // If the number is safe to place
    return true;
}

// Function to find an empty location in the grid
bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there is no empty space, the puzzle is solved
    if (!findEmptyLocation(grid, row, col))
        return true;

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        // Check if placing num in grid[row][col] is valid
        if (isSafe(grid, row, col, num)) {
            // Place the number
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If placing num doesn't lead to a solution, undo the assignment (backtrack)
            grid[row][col] = 0;
        }
    }

    // Trigger backtracking if no number is valid
    return false;
}

int main() {
    // Input grid for the Sudoku puzzle (0 represents an empty cell)
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Try to solve the Sudoku puzzle
    if (solveSudoku(grid))
        printGrid(grid);
    else
        cout << "No solution exists for the given Sudoku puzzle." << endl;

    return 0;
}

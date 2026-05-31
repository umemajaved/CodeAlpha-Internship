#include <iostream>
using namespace std;

#define N 9

// Print Sudoku grid
void printGrid(int grid[N][N]) {
    cout << "\nSolved Sudoku:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if safe to place number
bool isSafe(int grid[N][N], int row, int col, int num) {
    int x, y;

    // Row check
    for (x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }

    // Column check
    for (x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }

    // 3x3 box check
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            if (grid[startRow + x][startCol + y] == num)
                return false;
        }
    }

    return true;
}

// Solve Sudoku using Backtracking
bool solveSudoku(int grid[N][N]) {
    int row = -1, col = -1;
    bool empty = false;

    // Find empty cell
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                empty = true;
                break;
            }
        }
        if (empty)
            break;
    }

    // No empty cell ? solved
    if (!empty)
        return true;

    // Try numbers 1–9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {

            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int grid[N][N] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    cout << "Solving Sudoku...\n";

    if (solveSudoku(grid))
        printGrid(grid);
    else
        cout << "No solution exists!\n";

    return 0;
}

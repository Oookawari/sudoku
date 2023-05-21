#include "sudoku.h"
#include <stdlib.h>
#include <time.h>

Sudoku::Sudoku(bool no_blanks, bool ans_unique = false) {
    // Initialize board and masks
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            board[i][j] = 0;
            masks[i][j] = false;
        }
    }

    generateBoard(0, 0);
    //已经完成了生成，现在你需要挖空或者生成唯一解
    //TODO 
}

bool Sudoku::generateBoard(int row, int col) {
    if (row == ROW_NUM) {
        return true;
    }

    int nextRow = (col == COL_NUM - 1) ? row + 1 : row;
    int nextCol = (col + 1) % COL_NUM;
    //增加随机过程
    int randomization = rand() % 9;
    for (int num = 1; num <= ROW_NUM; num++) {
        if (isValid(row, col, num)) {
            board[row][col] = (num + randomization) % 9;
            if (generateBoard(nextRow, nextCol)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

bool Sudoku::isValid(int row, int col, int num) {
    // Check row
    for (int i = 0; i < COL_NUM; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < ROW_NUM; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Check subgrid
    int subgridRowStart = (row / 3) * 3;
    int subgridColStart = (col / 3) * 3;
    for (int i = subgridRowStart; i < subgridRowStart + 3; i++) {
        for (int j = subgridColStart; j < subgridColStart + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}
#include "sudoku.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
Sudoku::Sudoku(bool no_blanks, bool ans_unique) {
    // Initialize board and masks
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            board[i][j] = 0;
            masks[i][j] = true;
        }
    }

    generateBoard(0, 0);
    //已经完成了生成，现在你需要挖空或者生成唯一解
    //TODO 
    if (no_blanks) {
        
    }
}

bool Sudoku::generateBoard(int row, int col) {
    if (row == ROW_NUM) {
        return true;
    }

    int nextRow = (col == COL_NUM - 1) ? row + 1 : row;
    int nextCol = (col + 1) % COL_NUM;
    //增加随机过程
    int randomization = rand();
    for (int num = 0; num <= ROW_NUM; num++) {
        if (isValid(row, col, (num + randomization) % (ROW_NUM + 1))) {
            board[row][col] = (num + randomization) % (ROW_NUM + 1);
            
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

void Sudoku::writeBoardToFile(std::string file_path)
{
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cout << "Error: could not open file : " << file_path << std::endl;
        return;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (masks[i][j])
                file << board[i][j] << ' ';
            else
                file << '_' << ' ';
        }
        file << '\n';
    }

    file.close();
}

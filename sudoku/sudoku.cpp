#include "sudoku.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <random>


int Sudoku::lower_bound_blanks = 20;
int Sudoku::upper_bound_blanks = 25;

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
    if (no_blanks) {
        return;
    }
    else {
        Random_leave_blank();
    }
    if (ans_unique) {
        int i = 0;
        Random_leave_blank(); 
        solveSudoku(0, 0);
        while (solutions >= 2) {
            for (int i = 0; i < ROW_NUM; i++) {
                for (int j = 0; j < COL_NUM; j++) {
                    board[i][j] = 0;
                    masks[i][j] = true;
                }
            }
            generateBoard(0, 0);
            Random_leave_blank();
            solutions = 0;
            solveSudoku(0, 0);
            i++;
        }
        std::cout << "重复了" << i << "次" << std::endl;

    }
}

Sudoku::Sudoku(std::string file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        for (int col = 0; col < COL_NUM; col++) {
            char c = line[col];
            if (c == '_') {
                board[row][col] = 0;
                masks[row][col] = false;
            }
            else {
                board[row][col] = c - '0';
                masks[row][col] = true;
            }
        }
        row++;
        if (row == ROW_NUM) break;
    }

    file.close();
}

void Sudoku::set_level(int l) {
    switch (l)
    {
    case LEVEL_EASY:
        lower_bound_blanks = 20;
        upper_bound_blanks = 25;
        return;
    case LEVEL_MEDIUM:
        lower_bound_blanks = 30;
        upper_bound_blanks = 35;
        return;
    case LEVEL_HARD:
        lower_bound_blanks = 40;
        upper_bound_blanks = 45;
        return;
    default:
        break;
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
        if (masks[row][i] == true && board[row][i] == num) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < ROW_NUM; i++) {
        if (masks[i][col] == true && board[i][col] == num) {
            return false;
        }
    }

    // Check subgrid
    int subgridRowStart = (row / 3) * 3;
    int subgridColStart = (col / 3) * 3;
    for (int i = subgridRowStart; i < subgridRowStart + 3; i++) {
        for (int j = subgridColStart; j < subgridColStart + 3; j++) {
            if (masks[i][j] == true && board[i][j] == num) {
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

void Sudoku::Random_leave_blank()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int num = (rand() % (upper_bound_blanks - lower_bound_blanks + 1)) + lower_bound_blanks;

    bool tempArray[ROW_NUM * COL_NUM];
    std::fill(tempArray, tempArray + num, false);
    std::fill(tempArray + num, tempArray + ROW_NUM * COL_NUM, true);
    std::shuffle(tempArray, tempArray + ROW_NUM * COL_NUM, gen);

    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            masks[i][j] = tempArray[i * COL_NUM + j];
        }
    }
}

bool Sudoku::solveSudoku(int row, int col) {
    if (row == ROW_NUM - 1 && col == COL_NUM) {
        solutions++;
        if (solutions >= 2)
            return true;
        return false;
    }
    if (col == COL_NUM) {
        row++;
        col = 0;
    }
    if (masks[row][col])
        return solveSudoku(row, col + 1);
    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            board[row][col] = num;
            masks[row][col] = true;
            if (solveSudoku(row, col + 1))
                return true;
            board[row][col] = 0;
            masks[row][col] = false;
        }
    }
    return false;
}

#pragma once
#ifndef SUDOKU
#define SUDOKU
#define UNKNOWN -1
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <random>
const int ROW_NUM = 9;
const int COL_NUM = 9;

class Sudoku {
private:

    static int lower_bound_blanks;
    static int upper_bound_blanks;
    int board[ROW_NUM][COL_NUM];
    bool masks[ROW_NUM][COL_NUM];
    bool has_a_solution = false;
    int solutions = 0;
public:
    static enum
    {
        LEVEL_NONE, LEVEL_EASY, LEVEL_MEDIUM, LEVEL_HARD
    };
    static void set_lower_blanks(int b) {
        Sudoku::lower_bound_blanks = b;
    }
    static void set_upper_blanks(int b) {
        Sudoku::upper_bound_blanks = b;
    }
    static void set_level(int l);
    Sudoku(bool no_blanks, bool ans_unique = false);
    Sudoku(const char* file_name);
    bool generateBoard(int row, int col);
    bool isValid(int row, int col, int num);
    void writeBoardToFile(std::string file_path);
    void Random_leave_blank();
    bool solveSudoku(int row, int col);
    bool validBoard();
    bool validPos(int row, int col);
    int* get_board();
    void invalid();
    void multiSol();
    int get_sol_num() { return solutions; };
    void show();
};


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
        // std::cout << "重复了" << i << "次" << std::endl;

    }
}

Sudoku::Sudoku(const char* file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        for (int col = 0; col < COL_NUM; col++) {
            char c = line[col * 2];
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


bool Sudoku::validBoard() {
    bool valid = true;

    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            if (!validPos(i, j)) {
                valid = false;
                break;
            }
        }
    }

    return valid;
}

bool Sudoku::validPos(int row, int col) {
    // Check row
    for (int i = 0; i < COL_NUM; i++) {
        if (!masks[row][i]) continue;
        if (i == col) continue;
        if (board[row][i] == board[row][col]) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < ROW_NUM; i++) {
        if (!masks[i][col]) continue;
        if (i == row) continue;
        if (board[i][col] == board[row][col]) {
            return false;
        }
    }

    // Check subgrid
    int subgridRowStart = (row / 3) * 3;
    int subgridColStart = (col / 3) * 3;
    for (int i = subgridRowStart; i < subgridRowStart + 3; i++) {
        for (int j = subgridColStart; j < subgridColStart + 3; j++) {
            if (!masks[i][j]) continue;
            if (i == row && j == col) continue;
            if (board[i][j] == board[row][col]) {
                return false;
            }
        }
    }

    return true;
}

int* Sudoku::get_board() {
    int* a = new int[COL_NUM];
    for (int i = 0; i < COL_NUM; i++) {
        a[i] = board[0][i];
    }
    return a;
}

void Sudoku::invalid() {
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            board[i][j] = 1;
        }
    }
}

void Sudoku::multiSol() {
    int i = 0;
    solveSudoku(0, 0);
    while (solutions < 2) {
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
    // std::cout << "重复了" << i << "次" << std::endl;
}

void Sudoku::show() {
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            masks[i][j] = true;
        }
    }
}

#endif
#pragma once
#ifndef SUDOKU
#define SUDOKU
#define UNKNOWN -1
#include <string>
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
    Sudoku(std::string file_name);
    bool generateBoard(int row, int col);
    bool isValid(int row, int col, int num);
    void writeBoardToFile(std::string file_path);
    void Random_leave_blank();
    bool solveSudoku(int row, int col);
};

#endif
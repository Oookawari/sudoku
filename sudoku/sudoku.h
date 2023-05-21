#pragma once
#ifndef SUDOKU
#define SUDOKU
#define UNKNOWN -1
const int ROW_NUM = 9;
const int COL_NUM = 9;

class Sudoku {
private:
    static int blanks;
    int board[ROW_NUM][COL_NUM];
    bool masks[ROW_NUM][COL_NUM];
public:
    void set_blanks(int b) {
        Sudoku::blanks = b;
    }
    Sudoku(bool no_blanks, bool ans_unique = false);
    /* Generate a valid Sudoku board
     * This can be done using a backtracking algorithm
     * to fill in the board one cell at a time
     */
    bool generateBoard(int row, int col);
    bool isValid(int row, int col, int num);
};

#endif
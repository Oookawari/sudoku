#ifndef SUDOKU_SOLVE
#define SUDOKU_SOLVE
#include <iostream>
#include <fstream>
#include <string>

class SudokuSolve {
private:
    static const int ROW_NUM = 9;
    static const int COL_NUM = 9;
    int board[ROW_NUM][COL_NUM];
    
    bool masks[ROW_NUM][COL_NUM];

    bool isSafe(int row, int col, int num);
    
    

public:
    void readFromFile(std::ifstream& file);

    void writeToFile(std::ofstream& file);
    
    bool solve(int row, int col);
    
    void solve() {
        solve(0, 0);
    }
};

void solveSudokuFile(const std::string inputFilePath, const std::string outputFilePath);
#endif // !SUDOKU_SOLVE


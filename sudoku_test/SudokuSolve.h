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

void SudokuSolve::writeToFile(std::ofstream& file)
{
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            file << board[i][j] << " ";
        }
        file << std::endl;
    }
    file << std::endl;
}

bool SudokuSolve::isSafe(int row, int col, int num)
{
    // 检查行
    for (int i = 0; i < COL_NUM; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // 检查列
    for (int i = 0; i < ROW_NUM; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // 检查3x3子方格
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuSolve::solve(int row, int col)
{
    if (row == ROW_NUM) {
        return true;
    }

    if (col == COL_NUM) {
        return solve(row + 1, 0);
    }

    if (masks[row][col]) {
        return solve(row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            board[row][col] = num;
            if (solve(row, col + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

void SudokuSolve::readFromFile(std::ifstream& file)
{
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
}

void solveSudokuFile(const std::string inputFilePath, const std::string outputFilePath)
{
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        inputFile.close();
        return;
    }

    SudokuSolve sudoku;
    while (!inputFile.eof()) {
        sudoku.readFromFile(inputFile);

        if (sudoku.solve(0, 0))
            sudoku.writeToFile(outputFile);
        else {
            outputFile << "无解\n";
        }
    }

    inputFile.close();
    outputFile.close();
}


#endif // !SUDOKU_SOLVE


// Copyright (C) 2023 NKU-LYC/LYH.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#ifndef SUDOKU_SOLVE
#define SUDOKU_SOLVE
#include <fstream>
#include <iostream>
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

  void solve() { solve(0, 0); }
};

void solveSudokuFile(const std::string inputFilePath,
                     const std::string outputFilePath);
#endif  // !SUDOKU_SOLVE

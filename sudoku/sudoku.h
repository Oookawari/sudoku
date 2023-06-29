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
  static enum { LEVEL_NONE, LEVEL_EASY, LEVEL_MEDIUM, LEVEL_HARD };
  static void set_lower_blanks(int b) { Sudoku::lower_bound_blanks = b; }
  static void set_upper_blanks(int b) { Sudoku::upper_bound_blanks = b; }
  static void set_level(int l);
  explicit Sudoku(bool no_blanks, bool ans_unique = false);
  explicit Sudoku(std::string file_name);
  bool generateBoard(int row, int col);
  bool isValid(int row, int col, int num);
  void writeBoardToFile(std::string file_path);
  void Random_leave_blank();
  bool solveSudoku(int row, int col);
};

#endif

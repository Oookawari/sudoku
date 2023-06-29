

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


#include <direct.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fstream>
#include <iostream>

#include "Assert.h"
#include "SudokuSolve.h"
#include "getopt.h"
#include "sudoku.h"


// 需要的数独终盘数量
bool opt_gen_final = false;
int final_num = 0;

// 需要的数独棋盘求解路径
bool opt_solve = false;
char solve_path[256] = "";

// 需要的游戏数量
bool opt_number = false;
int number_of_games = 0;

// 生成游戏的难度
bool opt_level = false;
int game_level = Sudoku::LEVEL_NONE;

// 生成挖空范围
bool opt_range = false;
const int MIN_SPACE = 20;
const int MAX_SPACE = 80;
unsigned int space_lower_bound = MIN_SPACE;
unsigned int space_upper_bound = MAX_SPACE;

// 生成唯一解
bool opt_unique = false;

char opt_buffer[256];

void args_check();

int main(int argc, char* argv[]) {
  srand(time(nullptr));
  int opt;
  // 参数获取
  char getopt_arg[] = "c:s:n:m:r:u";
  while ((opt = getopt(argc, argv, getopt_arg)) != -1) {
    switch (opt) {
      case 'c':
        Assert(!opt_gen_final, "duplicated opt:c");
        opt_gen_final = true;
        snprintf(opt_buffer, sizeof(opt_buffer), "%s", optarg);
        final_num = atoi(opt_buffer);
        break;
      case 's':
        Assert(!opt_solve, "duplicated opt:s");
        opt_solve = true;
        snprintf(solve_path, sizeof(solve_path), "%s", optarg);
        break;
      case 'n':
        Assert(!opt_number, "duplicated opt:n");
        opt_number = true;
        snprintf(opt_buffer, sizeof(opt_buffer), "%s", optarg);
        number_of_games = atoi(opt_buffer);
        break;
      case 'm':
        Assert(!opt_level, "duplicated opt:m");
        opt_level = true;
        snprintf(opt_buffer, sizeof(opt_buffer), "%s", optarg);
        game_level = atoi(opt_buffer);
        break;
      case 'r':
        Assert(!opt_range, "duplicated opt:r");
        opt_range = true;
        snprintf(opt_buffer, sizeof(opt_buffer), "%s", optarg);
        char* low_num;
        char* up_num;
        low_num = strtok(opt_buffer, "~");
        space_lower_bound = atoi(low_num);
        up_num = strtok(NULL, "~");
        space_upper_bound = atoi(up_num);
        break;
      case 'u':
        Assert(!opt_unique, "duplicated opt:u");
        opt_unique = true;
        break;
      default:
        char mess[256];
        snprintf(mess, sizeof(mess), "Invalid Args: %c\n", opt);
        Assert(0, mess);
        break;
    }
  }
  // 参数检查
  args_check();

  if (opt_gen_final) {
    if (_access("./final_tables", 00) == -1) _mkdir("./final_tables");
    std::string file_names = "./final_tables/final_table_";
    for (int i = 1; i <= final_num; i++) {
      Sudoku temp = Sudoku(true);
      temp.writeBoardToFile(file_names + std::to_string(i) + ".txt");
    }
  }
  if (opt_solve) {
    solveSudokuFile(solve_path, "sudoku.txt");
  }
  if (opt_number) {
    if (_access("./games", 00) == -1) _mkdir("./games");
    std::string file_names = "./games/games";
    if (opt_level) {
      Sudoku::set_level(game_level);
    }
    if (opt_range) {
      Sudoku::set_lower_blanks(space_lower_bound);
      Sudoku::set_upper_blanks(space_upper_bound);
    }
    if (opt_unique) {
      for (int i = 1; i <= number_of_games; i++) {
        Sudoku temp = Sudoku(false, true);
        temp.writeBoardToFile(file_names + std::to_string(i) + ".txt");
      }
    } else {
      for (int i = 1; i <= number_of_games; i++) {
        Sudoku temp = Sudoku(false);
        temp.writeBoardToFile(file_names + std::to_string(i) + ".txt");
      }
    }
  }
  return 0;
}

void args_check() {
  if (opt_gen_final) {
    Assert(final_num > 0, "游戏终局数量需要 > 0 !");
    Assert(final_num <= 1000000, "游戏终局数量需要 < 1000000 !");
  }
  if (opt_number) {
    Assert(number_of_games > 0, "游戏数量需要 > 0");
    Assert(number_of_games <= 10000, "游戏数量需要 < 10000");
  }

  if (opt_level) {
    Assert(opt_number, "opt-m 需要opt-n");
    Assert((game_level == Sudoku::LEVEL_EASY ||
            game_level == Sudoku::LEVEL_MEDIUM ||
            game_level == Sudoku::LEVEL_HARD),
           "游戏等级取值为 1,2,3 !");
  }

  if (opt_range) {
    Assert(opt_number, "opt-r 需要opt-n");
    Assert(space_lower_bound <= space_upper_bound, "挖空数量上下界错误");
    Assert(MIN_SPACE <= space_lower_bound, "挖空数量下界小于最小值20");
    Assert(MAX_SPACE >= space_upper_bound, "挖空数量下界大于最大值55");
  }

  if (opt_unique) {
    Assert(opt_number, "opt-u 需要opt-n");
  }
}

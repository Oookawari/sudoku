#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "getopt.h"
#include "Assert.h"

//需要的数独终盘数量
bool opt_gen_final = false;
int final_num = 0;

//需要的数独棋盘求解路径
bool opt_solve = false;
char solve_path[256] = "";

//需要的游戏数量
bool opt_number = false;
int number_of_games = 0;


//生成游戏的难度
bool opt_level = false;
enum { LEVEL_NONE, LEVEL_EASY, LEVEL_MEDIUM, LEVEL_HARD };
int game_level = LEVEL_NONE;

//生成挖空范围
bool opt_range = false;
const int MIN_SPACE = 20;
const int MAX_SPACE = 55;
unsigned int space_lower_bound = MIN_SPACE;
unsigned int space_upper_bound = MAX_SPACE;

//生成唯一解
bool opt_unique = false;

char opt_buffer[256];

void args_check();

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    int opt;
    //参数获取
    char getopt_arg[] = "c:s:n:m:r:u";
    while ((opt = getopt(argc, argv, getopt_arg)) != -1)
    {
        switch (opt)
        {
        case 'c':
            Assert(!opt_gen_final, "duplicated opt:c");
            opt_gen_final = true;
            strcpy(opt_buffer, optarg);
            final_num = atoi(opt_buffer);
            break;
        case 's':
            Assert(!opt_solve, "duplicated opt:s");
            opt_solve = true;
            strcpy(solve_path, optarg);
            break;
        case 'n':
            Assert(!opt_number, "duplicated opt:n");
            opt_number = true;
            strcpy(opt_buffer, optarg);
            number_of_games = atoi(opt_buffer);
            break;
        case 'm':
            Assert(!opt_level, "duplicated opt:m");
            opt_level = true;
            strcpy(opt_buffer, optarg);
            game_level = atoi(opt_buffer);
            break;
        case 'r':
            Assert(!opt_range, "duplicated opt:r");
            opt_range = true;
            strcpy(opt_buffer, optarg);
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
            char* mess;
            sprintf(mess, "Invalid Args: %c\n", opt);
            Assert(0, mess);
            break;
        }
    }
    //参数检查
    args_check();

    if (opt_gen_final) {
        //TODO
    }
    if (opt_solve) {
        //TODO
    }
    if (opt_number) {
        //TODO
    }
    return 0;
}

void args_check() {
    if (opt_gen_final)
        Assert(final_num > 0, "游戏终局数量需要 > 0 !");

    if (opt_number)
        Assert(number_of_games > 0, "游戏数量需要 > 0");

    if (opt_level) {
        Assert(opt_number, "opt-m 需要opt-n");
        Assert((game_level == LEVEL_EASY || game_level == LEVEL_MEDIUM || game_level == LEVEL_HARD), "游戏等级取值为 1,2,3 !");
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
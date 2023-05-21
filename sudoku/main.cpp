#include <iostream>
#include <string.h>
#include "getopt.h"
#include "Assert.h"

//��Ҫ��������������
bool opt_gen_final = false;
int final_num = 0;

//��Ҫ�������������·��
bool opt_solve = false;
char solve_path[256] = "";

//��Ҫ����Ϸ����
bool opt_number = false;
int number_of_games = 0;


//������Ϸ���Ѷ�
bool opt_level = false;
enum { LEVEL_NONE, LEVEL_EASY, LEVEL_MEDIUM, LEVEL_HARD };
int game_level = LEVEL_NONE;

//�����ڿշ�Χ
bool opt_range = false;
const int MIN_SPACE = 20;
const int MAX_SPACE = 55;
unsigned int space_lower_bound = MIN_SPACE;
unsigned int space_upper_bound = MAX_SPACE;

//����Ψһ��
bool opt_unique = false;

char opt_buffer[256];

void args_check();

int main(int argc, char* argv[])
{

    int opt;
    //������ȡ
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
    //�������
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
        Assert(final_num > 0, "��Ϸ�վ�������Ҫ > 0 !");

    if (opt_number)
        Assert(number_of_games > 0, "��Ϸ������Ҫ > 0");

    if (opt_level) {
        Assert(opt_number, "opt-m ��Ҫopt-n");
        Assert((game_level == LEVEL_EASY || game_level == LEVEL_MEDIUM || game_level == LEVEL_HARD), "��Ϸ�ȼ�ȡֵΪ 1,2,3 !");
    }

    if (opt_range) {
        Assert(opt_number, "opt-r ��Ҫopt-n");
        Assert(space_lower_bound <= space_upper_bound, "�ڿ��������½����");
        Assert(MIN_SPACE <= space_lower_bound, "�ڿ������½�С����Сֵ20");
        Assert(MAX_SPACE >= space_upper_bound, "�ڿ������½�������ֵ55");
    }

    if (opt_unique) {
        Assert(opt_number, "opt-u ��Ҫopt-n");
    }
}
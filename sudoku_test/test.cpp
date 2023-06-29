#include "pch.h"

#include "getopt.h"
#include "sudoku.h"
#include "SudokuSolve.h"


// 生成有效棋盘
TEST(GenBoard, case1) {
	Sudoku sdk = Sudoku(true);
	EXPECT_TRUE(sdk.validBoard());
}

// 不同棋盘
TEST(GenBoard, case2) {
	Sudoku sdk1 = Sudoku(true);
	Sudoku sdk2 = Sudoku(true);
	bool same = true;
	for (int i = 0; i < COL_NUM; i++) {
		if ((sdk1.get_board())[i] != (sdk2.get_board())[i]) {
			same = false;
			break;
		}
	}
	EXPECT_FALSE(same);
}

// 生成数读游戏
TEST(GenBoard, case3) {
	Sudoku sdk = Sudoku(false);
	EXPECT_TRUE(sdk.validBoard());
}

// 生成唯一解游戏
TEST(GenBoard, case4) {
	Sudoku sdk = Sudoku(false, true);
	EXPECT_TRUE(sdk.validBoard());
	EXPECT_LT(sdk.get_sol_num(), 2);
}

// 生成不唯一解游戏
TEST(GenBoard, case5) {
	Sudoku sdk = Sudoku(false);
	sdk.multiSol();
	EXPECT_TRUE(sdk.validBoard());
	EXPECT_LT(1, sdk.get_sol_num());
}

// 生成不同难度游戏
TEST(GenBoard, case6) {

	Sudoku::set_level(1);
	Sudoku sdk2 = Sudoku(false);
	EXPECT_TRUE(sdk2.validBoard());

	Sudoku::set_level(2);
	Sudoku sdk3 = Sudoku(false);
	EXPECT_TRUE(sdk3.validBoard());

	Sudoku::set_level(3);
	Sudoku sdk4 = Sudoku(false);
	EXPECT_TRUE(sdk4.validBoard());
}

// 测试从文件读入谜题
TEST(GenBoard, case7) {
	Sudoku sdk = Sudoku(false);
	EXPECT_TRUE(sdk.validBoard());
	sdk.writeBoardToFile("example.txt");

	Sudoku sdk1 = Sudoku("example.txt");

	sdk1.writeBoardToFile("example_output.txt");
	EXPECT_TRUE(sdk1.validBoard());
}

// Solve正确的问题
TEST(SolveProb, case1) {
	Sudoku sdk1 = Sudoku(false, true);
	EXPECT_TRUE(sdk1.validBoard());
	sdk1.writeBoardToFile("rightsudoku.txt");

	solveSudokuFile("rightsudoku.txt", "rightsudokuanswer.txt");

	Sudoku sdk = Sudoku("rightsudokuanswer.txt");
	EXPECT_TRUE(sdk.validBoard());
}

TEST(SolveProb, case2) {
	Sudoku::set_level(1);
	Sudoku sdk1 = Sudoku(false, true);
	EXPECT_TRUE(sdk1.validBoard());
	sdk1.writeBoardToFile("rightsudoku.txt");

	solveSudokuFile("rightsudoku.txt", "rightsudokuanswer.txt");

	Sudoku sdk = Sudoku("rightsudokuanswer.txt");
	EXPECT_TRUE(sdk.validBoard());
}

TEST(SolveProb, case3) {
	Sudoku::set_level(2);
	Sudoku sdk1 = Sudoku(false, true);
	EXPECT_TRUE(sdk1.validBoard());
	sdk1.writeBoardToFile("rightsudoku.txt");

	solveSudokuFile("rightsudoku.txt", "rightsudokuanswer.txt");

	Sudoku sdk = Sudoku("rightsudokuanswer.txt");
	EXPECT_TRUE(sdk.validBoard());
}

TEST(SolveProb, case4) {
	Sudoku::set_level(3);
	Sudoku sdk1 = Sudoku(false, true);
	EXPECT_TRUE(sdk1.validBoard());
	sdk1.writeBoardToFile("rightsudoku.txt");

	solveSudokuFile("rightsudoku.txt", "rightsudokuanswer.txt");

	Sudoku sdk = Sudoku("rightsudokuanswer.txt");
	EXPECT_TRUE(sdk.validBoard());
}

// Solve错误的问题
TEST(SolveProb, case5) {
	Sudoku sdk1 = Sudoku(false);
	sdk1.invalid();
	sdk1.writeBoardToFile("falsesudoku.txt");

	solveSudokuFile("falsesudoku.txt", "falsesudokuanswer.txt");

	Sudoku sdk = Sudoku("falsesudokuanswer.txt");

	EXPECT_FALSE(sdk.validBoard());
}

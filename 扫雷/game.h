#pragma once
#include <stdlib.h>
#include <time.h>
#define ROW 9
#define COL 9
#define ROWS 11
#define COLS 11
//展示数组用*表示
// 后面0表示雷1表示
//初始化棋盘
void initboard(char board[ROWS][COLS], int row, int col, char set);
//打印棋盘
void Displayboard(char board[ROWS][COLS], int row, int col);
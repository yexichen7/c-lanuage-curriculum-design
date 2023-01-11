#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"
void initboard(char board[ROWS][COLS], int row, int col, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			board[i][j] = set;
		}
	}
}
void Displayboard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= row; i++)
	{
		printf("%d", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d", i);
		for (j = 1; j <= col; j++)
		{
			printf("%C", board[i][j]);
		}
		printf("\n");
	}
}
char surround(char mine[ROW][COL], int a, int b)
{
	return mine[a - 1][b - 1] + mine[a - 1][b] + mine[a - 1][b + 1]
		+ mine[a][b - 1] + mine[a][b + 1] + mine[a + 1][b + 1] + mine[a + 1][b]
		+ mine[a + 1][b - 1] - 8 * '0';
}
void setmine(char mine[ROW][COL], int row, int col)
{
	int i = 0;
	while (i < 9)
	{
		int x = rand() % 9 + 1;
		int y = rand() % 9 + 1;
		mine[x][y] = '1';
	}
}
void playmove(char mine[ROW][COL],char show [ROW][COL], int row, int col)
{
	printf("请输入坐标\n");
	int count = 81;
	int x = 0;
	int y = 0;
	char i = '0';
	while (count<=10)
	{
		scanf("%d %d", &x, &y);
		count--;
		if (x >= 1 && x <= ROW && y >= 1 && y <= COL)
		{
			if (mine[x][y] == '0')
			{
				 i = surround(mine[ROW][COL],x, y);
				show[x][y] = i ;
				Displayboard(mine, ROW, COL);
			}
			else
				printf("很遗憾,你点到了地雷");
			    Displayboard(mine, ROW, COL);
		}
		else
			printf("坐标非法,请重新输入");
		     break;
	}
}
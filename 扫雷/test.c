#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"
void menu()
{
	printf("***********************************************\n");
	printf("****************   1.play    ******************\n");
	printf("****************   0.exit    ******************\n");
	printf("***********************************************\n");

}
void game()
{   
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	initboard(mine,ROWS,COLS,'0');
	initboard(show, ROWS, COLS, '*');
	Displayboard(mine, ROW, COL);
}
int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do {
		menu();
		printf("请选择\n");
		scanf("%d", &input);
		switch(input)
		{   
			case 1:
				printf("玩游戏\n");
				game();
				break;
			case 0:
				printf("退出\n");
				break;
			default:
				printf("输入错误,请重新选择\n");
				break;
		}
	} while (input);
	return 0;
}
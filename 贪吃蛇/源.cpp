#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <iostream>
//播放bgm
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
#define Maxsize 200//蛇的最大节数
 struct snake
{
	int size;//节数
	int dir;//方向
	int speed;//速度
	POINT coor[Maxsize];//蛇的坐标
}s;
 struct food
 {
	 int x;
	 int y;
	 bool flag;//表示是否被吃
	 int radious;//食物半径
	 DWORD color;//食物颜色
 }f;
void initsnake(snake &s,food&f)
{
	
	initgraph(640, 480);//初始化窗口
	srand(GetTickCount());//获取随机数种子，系统开机到现在经历的毫秒数
	mciSendString("open snakebgm.mp3 alias sbgm", NULL, 0, NULL);
	mciSendString("play sbgm repeat", NULL, 0, NULL);
	//初始化蛇
	s.size = 3;
	s.dir = 4;
	s.speed = 10;
	for (int i = 0; i <s.size; i++)
	{
		s.coor[i].x = 40-10*i;
		s.coor[i].y = 10;
	}
	//初始化食物
	f.x = rand() % 640;
	f.y = rand() % 480;
	f.radious = 10;
	f.color = RGB(rand()%256, rand()%256, rand()%256);
	f.flag = true;
}
void gamedraw(snake &s,food&f)
{//绘制背景
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));//设置背景颜色
	cleardevice();//用当前背景色清空绘图设备，把前点移动到(0,0)
	//绘制蛇
	setfillcolor(RED);
	int i = 0;
	cout << s.size << endl;
	for ( i = 0; i < s.size; i++)
	{
		solidcircle(s.coor[i].x, s.coor[i].y, 5);
	}
	if (f.flag)
	{
		setfillcolor(f.color);
		solidcircle(f.x, f.y, f.radious);
	}
	EndBatchDraw();
}
void move(snake &s)
{
	int i = 0;
	//身体移动
	for (i = s.size-1; i > 0; i--)
	{
		s.coor[i] = s.coor[i - 1];
	}
	switch (s.dir)
	{
	case 4:
		if (s.coor[0].x >= 635)
		{
			s.coor[0].x = 5;
		}
		s.coor[0].x += s.speed;
		break;
	case 3:
		if (s.coor[0].y >= 475)
		{
			s.coor[0].y = 5;
		}
		s.coor[0].y += s.speed;
		break;
	case 2:
		if (s.coor[0].x <= 5)
		{
			s.coor[0].x = 635;
		}
		s.coor[0].x -= s.speed;
		break;
	case 1:
		if (s.coor[0].y <= 5)
		{
			s.coor[0].y= 475;
		}
		s.coor[0].y -= s.speed;
		break;
	default:
		break;
	}
}
void keymove(snake &s)
{//72 80 75 77上下左右键值数字键盘
	if (_kbhit())//检测按键函数有返回真
	{
		switch (_getch())
		{
		default:
			break;
		case 'w':
		case 'W':
			if (s.dir != 3)
			{
				s.dir = 1;
			}
			break;
		case 'a':
		case 'A':
			if (s.dir != 4)
			{
				s.dir = 2;
			}
			break;
		case 's':
		case 'S':
			if (s.dir != 1)
			{
				s.dir = 3;
			}
			break;
		case 'D':
		case 'd':
			if (s.dir != 2)
			{
				s.dir = 4;
			}
			break;
		case ' '://游戏暂停
			while (1)
			{
				if (_getch() == ' ')
					return;
			}
			break;
		}
	 
	}
}
void eat(snake&s,food&f)
{
	mciSendString("open eats.mp3 alias eats", NULL, 0, NULL);
	if (f.flag&&s.coor[0].x +5>=f.x- f.radious && s.coor[0].x-5 <= f.x + f.radious &&s.coor[0].y+5 >=f.y-f.radious&&s.coor[0].y-5<=f.y+f.radious)
	{
		mciSendString("close eats", 0, 0, 0);
		s.size++;
		f.flag = false;
		mciSendString("open eats.mp3 alias eats", NULL, 0, NULL);
		mciSendString("play eats   ", 0, 0, 0);
	}
	if (f.flag == false)
	{
		f.x = rand() % 640;
		f.y = rand() % 480;
		f.radious = 10;
		f.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		f.flag = true;
	}
}
int main()
{
	initsnake(s,f);
	while (1)
	{
		gamedraw(s,f);
		move(s);
		keymove(s);
		eat(s,f);
		Sleep(200);
	}
	return 0;
}
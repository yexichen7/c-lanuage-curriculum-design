#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
IMAGE c0, c1, c2, c3, c4, c5, c6;
int num = 0;
HWND hwnd;
int map[8][8] = {
	1,1,1,1,1,1,1,1,
	1,2,0,0,0,0,2,1,
	1,1,3,0,0,3,1,1,
	1,0,0,4,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,3,0,0,3,1,1,
	1,2,0,0,0,0,2,1,
	1,1,1,1,1,1,1,1,
};
void loadpicture()
{
	loadimage(&c0, "0.bmp", 100, 100);
	loadimage(&c1, "1.bmp", 100, 100);
	loadimage(&c2, "2.bmp", 100, 100);
	loadimage(&c3, "3.bmp", 100, 100);
	loadimage(&c4, "4.bmp", 100, 100);
	loadimage(&c5, "5.bmp", 100, 100);
	loadimage(&c6, "6.bmp", 100, 100);
}
void putpicture()
{
	mciSendString("open bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", 0, 0, 0);
	int i = 0, j = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(j * 100, i * 100, &c0);
				break;
			case 1:
				putimage(j * 100, i * 100, &c1);
				break;
			case 2:
				putimage(j * 100, i * 100, &c2);
				num++;
				break;
			case 3:
				putimage(j * 100, i * 100, &c3);
				break;
			case 4:
				putimage(j * 100, i * 100, &c4);
				break;
			case 5:
				putimage(j * 100, i * 100, &c5);
				break;
			case 6:
				putimage(j * 100, i * 100, &c6);
				break;
			default:
				break;
			}
		}
	}
}
void keymove()
{
	mciSendString("open gan.mp3 alias gan", 0, 0, 0);
	int flag = 1;
	int i = 0, j = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (map[i][j] == 4)
			{
				goto that;
			}
		}
	}
that:
	if (_kbhit()&&i>0&&j>0)//检测按键函数有返回真
	{ 
		switch (_getch())
		{
		default:
			break;
		case 'w':
		case 'W':
			if (map[i-1][j] == 0 )
			{
				map[i-1][j] = 4;
				map[i][j] = 0;
			}
			if (map[i - 1][j] == 3&&map[i-2][j]==0)
			{
				map[i - 2][j] = 3;
				map[i - 1][j] = 4;
				map[i][j] = 0;
			}
			if (map[i - 1][j] == 3 && map[i - 2][j] == 2)
			{
				map[i - 2][j] = 6;
				map[i - 1][j] = 4;
				map[i][j] = 0;
			}
			if (map[i - 1][j] == 1)
			{
				flag++;
			}
			break;
		case 's':
		case 'S':
			if (map[i+1][j] == 0  )
			{
				map[i+1][j] = 4;
				map[i][j] = 0;
			}
			if (map[i + 1][j] == 3 && map[i + 2][j] == 0)
			{
				map[i + 2][j] = 3;
				map[i + 1][j] = 4;
				map[i][j] = 0;
			}
			if (map[i + 1][j] == 3 && map[i + 2][j] == 2)
			{
				map[i + 2][j] = 6;
				map[i + 1][j] = 4;
				map[i][j] = 0;
			}
			if (map[i + 1][j] == 1)
			{
				flag++;
			}
			break;
		case 'a':
		case 'A':
			if (map[i][j - 1] == 0  )
			{
				map[i][j-1] = 4;
				map[i][j] = 0;
			}
			if (map[i][j - 1] == 3 && map[i][j-2] == 0)
			{
				map[i][j - 2] = 3;
				map[i][j - 1] = 4;
				map[i][j] = 0;
			}
			if (map[i ][j-1] == 3 && map[i][j-2] == 2)
			{
				map[i ][j-2] = 6;
				map[i][j-1] = 4;
				map[i][j] = 0;
			}
			if (map[i][j-1] == 1)
			{
				flag++;
			}
			break;
		case 'D':
		case 'd':
			if (map[i][j+1] == 0  )
			{
				map[i][j+1] = 4;
				map[i][j] = 0;
			}
			if (map[i][j + 1] == 3 && map[i][j+2] == 0)
			{
				map[i][j + 2] = 3;
				map[i][j + 1] = 4;
				map[i][j] = 0;
			}
			if (map[i][j+1] == 3 && map[i][j+2] == 2)
			{
				map[i][j+2] = 6;
				map[i][j+1] = 4;
				map[i][j] = 0;
			}
			if (map[i][j+1] == 1)
			{
				flag++;
			}
			break;
		}
	}
	if (flag > 1)
	{
		mciSendString("close gan", 0, 0, 0);
		mciSendString("open gan.mp3 alias gan", 0, 0, 0);
		mciSendString("play gan", 0, 0, 0);
	}
}
int jungle()
{
	int i, j = 0;
	for (i=0;i<8;i++)
		for (j = 0; j < 8; j++)
		{
			if (map[i][j] == 2)
			{
				return 1;
			}
		}
	return 0;
}
int main()
{
	HWND hwnd=initgraph(800, 800);
	loadpicture();
	mciSendString("open li.mp3 alias li", 0, 0, 0);
	while (1)
	{
		keymove();
		putpicture();
		if (jungle()==0)
		{
			mciSendString("close gan", 0, 0, 0);
			mciSendString("close bgm", 0, 0, 0);
			mciSendString("play li", 0, 0, 0);
			MessageBox(hwnd, "游戏胜利与坤坤共舞吧", "提示框",MB_OK);
			mciSendString("close li", 0, 0, 0);
			break;
		}
	}
	return 0;
}

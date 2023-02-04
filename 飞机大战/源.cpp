#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib,"winmm.lib")
using namespace std;
IMAGE bk, PE_1, PE_2, ne_1, ne_2, bl1, bl2, ep1, ep2, em1, em2;
ExMessage msg;
int static count1 = 0;
int static count2 = 0;
int score=0;
typedef struct plane
{
	int x;
	int y;
	int hp;
	bool live;
}plane;
typedef struct bullet
{
	int x;
	int y;
	bool live;
	int flag;
}bullet;
bullet b[15];
typedef struct enemy
{
	int x;
	int y;
	int weight;
	int height;
	bool live;
	int flag;
	int hp;
	int speed;
}enemy;
enemy em[10];
HWND hd;
void go();
void emhp(int i)
{
	srand(GetTickCount());
	if (rand() % 5 == 0)
	{
		em[i].flag = 1;
		em[i].hp = 120;
		em[i].weight = 104;
		em[i].height = 148;
		em[i].speed = 3;
	}
	else
	{
		em[i].flag = 0;
		em[i].hp = 40;
		em[i].weight = 52;
		em[i].height = 39;
		em[i].speed = 1;
	}
}
void initplane(plane &p)
{
	mciSendString("open ./res/game_music.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	p.live = true;
	p.x = 261;
	p.y = 360;
	p.hp = 30;
	for (int i = 0; i < 15; i++)
	{
		b[i].live = false;
		b[i].x = 0;
		b[i].y = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		em[i].live = false;
		em[i].x = 0;
		em[i].y = 0;
		emhp(i);
	}
}
void load()
{
	loadimage(&bk, "./res/background.jpg", 640, 480);
	loadimage(&PE_1, "./res/planeExplode_1.jpg" );
	loadimage(&PE_2, "./res/planeExplode_2.jpg");
	loadimage(&ne_1, "./res/planeNormal_1.jpg");
	loadimage(&ne_2, "./res/planeNormal_2.jpg");
	loadimage(&em1, "./res/enemy_1.jpg");
	loadimage(&em2, "./res/enemy_2.jpg");
	loadimage(&bl1, "./res/bullet1.jpg");
	loadimage(&bl2, "./res/bullet2.jpg");
	loadimage(&ep1, "./res/enemyPlane1.jpg");
	loadimage(&ep2, "./res/enemyPlane2.jpg");
	
}
void destory(plane&p)
{
	p.live = true;
	for (int i = 0; i < 10; i++)
	{
		if (!em[i].live)
		{
			continue;
		}
		if (em[i].flag == 1)
		{
			if (p.x >= em[i].x && p.x <= em[i].x + em[i].weight && p.y <= em[i].y + em[i].height && p.y >= em[i].y)
			{
				p.x = 262;
				p.y = 360;
				em[i].x = 0;
				em[i].y = 0;
			}
		}
		if (em[i].flag == 0)
		{
			if (em[i].x >= p.x && em[i].x <= p.x + 117 && em[i].y >= p.y && em[i].y <= p.y + 120)
			{
				p.x = 262;
				p.y = 360;
				em[i].x = 0;
				em[i].y = 0;
			}
		}
	}
}
void end(plane& p);
void gamedraw(plane p)
{
	putimage(0, 0, &bk);
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, "楷体");
	settextcolor(WHITE);
	string x = "得分:";
	string a = to_string(score);
	x = x + a;
	outtextxy(0, 14, x.c_str());

	if (p.live)
	{
		putimage(p.x, p.y, &ne_1, NOTSRCERASE);
		putimage(p.x, p.y, &ne_2, SRCINVERT);
	}
	else
	{
		putimage(p.x, p.y, &PE_1, NOTSRCERASE);
		putimage(p.x, p.y, &PE_2, SRCINVERT);
		MessageBox(hd, "很遗憾，您输了", "提示框", MB_OK);
		end(p);
		cleardevice();
	}
	for (int i = 0; i < 15; i++)
	{
		if (b[i].live)
		{
			putimage(b[i].x, b[i].y, &bl1, NOTSRCERASE);
			putimage(b[i].x, b[i].y, &bl2, SRCINVERT);
		}
	}
	for (int i = 0; i < 15; i++)
	{
		if (em[i].live && em[i].x != 0)
		{
			if (em[i].flag == 0)
			{
				putimage(em[i].x, em[i].y, &em1, NOTSRCERASE);
				putimage(em[i].x, em[i].y, &em2, SRCINVERT);
			}
			else
			{
				putimage(em[i].x, em[i].y, &ep1, NOTSRCERASE);
				putimage(em[i].x, em[i].y, &ep2, SRCINVERT);
			}
		}
	}

}
void end(plane&p )
{
	//cleardevice();
	putimage(0, 0, &bk);
	score = 0;
	setbkmode(TRANSPARENT);
	settextstyle(15, 0, "楷体");
	setfillcolor(RED);
	fillroundrect(200, 120, 280, 180,10,10);
	settextcolor(BLACK);
	outtextxy(210, 140, "继续游戏");
	setfillcolor(RED);
	fillroundrect(200, 200, 280, 260,10,10);
	settextcolor(BLACK);
	outtextxy(220, 220, "退出");
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.x >= 200 && msg.x <= 280 && msg.y >= 120 && msg.y <= 180)
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					destory(p);
					go();
				}
			}
			if (msg.x >= 200 && msg.x <= 280 && msg.y >= 200 && msg.y <= 260)
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					PostMessage(hd, WM_CLOSE, 0, 0);
					break;
				}
			}
		}
	}
}
void creatbullet(plane p)
{
	int i = 0;
	for (i = 0; i < 15; i++)
	{
		if (!b[i].live)
		{
			b[i].x = p.x+50;
			b[i].y = p.y -30;
			b[i].live = true;
			break;
		}
	}
}
void bulletmove()
{
	for (int i = 0; i < 15; i++)
	{
		if (b[i].live)
		{
			b[i].y -= 3;
			if (b[i].y < 0)
			{
				b[i].live = false;
			}
		}
	}
}
void emmove()
{
	for (int i = 0; i < 15; i++)
	{
		if (em[i].live)
		{
			em[i].y += em[i].speed;
			if (em[i].y > 480)
			{
				em[i].live = false;
			}
		}
	}
}
void createnmy()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		if (!em[i].live)
		{
			em[i].live = true;
			em[i].x = rand() % (640 - em[i].weight);
			em[i].y = 0;
			emhp(i);
			break;
		}
	}
}
void keymove(plane&p)
{
	mciSendString("open ./res/f_gun.mp3 alias gun", NULL, 0, NULL);
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if (p.y >= 10)
		{
			p.y -= 4;
		}
	}
	if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (p.x >= 10)
		{
			p.x -= 4;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (p.y <= 350)
		{
			p.y += 4;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (p.x <= 523)
		{
			p.x += 4;
		}
	}
	if (peekmessage(&msg,EX_MOUSE))//peek非阻塞并且有延迟，子弹不连续
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			creatbullet(p);
			mciSendString("close gun", 0, 0, 0);
			mciSendString("open ./res/f_gun.mp3 alias gun", NULL, 0, NULL);
			mciSendString("play gun", 0, 0, 0);

		}
	}
	if (GetAsyncKeyState(VK_ESCAPE))//ESC退出
	{
		int isok = MessageBox(hd, "是否要退出", "提示框", MB_OKCANCEL);
		if (isok == IDOK)
		{
			PostMessage(hd, WM_CLOSE, 0, 0);
		}
	}
}
void die(plane&p)
{
	mciSendString("open ./res/roledie.mp3 alias dead", NULL, 0, NULL);
	for (int i = 0; i < 10; i++)
	{
		if (!em[i].live)
		{
			continue;
		}
		if (em[i].flag == 1)
		{
			if (p.x >= em[i].x && p.x <= em[i].x + em[i].weight && p.y <= em[i].y + em[i].height && p.y >= em[i].y)
			{
				mciSendString("close dead", NULL, 0, NULL);
				mciSendString("open ./res/roledie.mp3 alias dead", NULL, 0, NULL);
				mciSendString("play dead", 0, 0, 0);
				p.hp -= 20;
			}
		}
		if (em[i].flag == 0)
		{
			if (em[i].x>=p.x&&em[i].x<=p.x+117&&em[i].y>=p.y&&em[i].y<=p.y+120)
			{
				mciSendString("close dead", NULL, 0, NULL);
				mciSendString("open ./res/roledie.mp3 alias dead", NULL, 0, NULL);
				mciSendString("play dead", 0, 0, 0);
				p.hp -= 10;
			}
		}
		if (p.hp <= 0)
		{
			p.live = false;
		}
	}
}
void hit(plane p)
{
	for (int i = 0; i < 10; i++)
	{
		if (!em[i].live)
		{
			continue;
		}
		for (int k = 0; k < 15; k++)
		{
			if (!b[k].live)
			{
				continue;
			}
				if (b[k].x >= em[i].x && b[k].x <= em[i].x + em[i].weight && b[k].y <= em[i].y + em[i].height && b[k].y >= em[i].y)
				{
					em[i].hp -= 30;
					b[k].live = false;
				}
		}
		if (em[i].hp <= 0&&em[i].flag==0)
		{
			count1++;
			em[i].live = false;
			score += 2;
		}
		if (em[i].hp <= 0 && em[i].flag == 1)
		{
			count2++;
			em[i].live = false;
			score += 5;
		}
	}
}
void mp()
{
	mciSendString("open ./res/5.mp3 alias m5", NULL, 0, NULL);
	mciSendString("open ./res/10.mp3 alias m10", NULL, 0, NULL);

	if (count1 > 10)
	{
		mciSendString("close m5", 0, 0, 0);
		mciSendString("open ./res/5.mp3 alias m5", NULL, 0, NULL);
		mciSendString("play m5", 0, 0, 0);
		count1 = 0;
	}
	if (count2 > 5)
	{
		mciSendString("close m10", 0, 0, 0);
		mciSendString("open ./res/10.mp3 alias m10", NULL, 0, NULL);
		mciSendString("play m10", 0, 0, 0);
		count2 = 0;
	}
}
void go()
{
	hd = initgraph(640, 480);
	plane p = { 0,0,true };
	initplane(p);
	while (1)
	{
		load();
		gamedraw(p);
		bulletmove();
		keymove(p);
		static DWORD t1, t2;
		if (t2 - t1 > 500)
		{
			createnmy();
			t1 = t2;
		}
		t2 = clock();
		emmove();
		hit(p);
		die(p);
		mp();
	}
}
int main()
{
	hd = initgraph(640, 480);
	plane p = {0,0,true};
	initplane(p);
	while (1)
	{
		load();
		gamedraw(p);
		bulletmove();
		keymove(p);
		static DWORD t1, t2;
		if (t2 - t1 > 500)
		{
			createnmy();
			t1 = t2;
		}
		t2 = clock();
		emmove();
		hit(p);
		die(p);
		mp();
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int Booknum = 5;
int Num = 5;
typedef struct book
{
	char day[30];
	int price;
	int num;
	char id[30];
	char name[20];
	char actor[20];
	
}book;
typedef struct booknode
{
	book data;
	struct booknode* next;
}booknode;
typedef struct user
{
	char number[20];
	char password[20];
	int Flag;
}user;
typedef struct userstore
{
	user data;
}userstore;
void creat_u(userstore p[])
{
	FILE* fp = fopen("userinfo.txt", "r");//只读打开
	if (!fp)
	{
		printf("userinfo.txt文件打开失败\n");
	}
	int i = 0;
	fscanf(fp, "%d", &Num);
	for (i = 0; i < Num; i++)
	{
		fscanf(fp, "%s", p[i].data.number);
		fscanf(fp, "%s", p[i].data.password);
		fscanf(fp, "%d", &p[i].data.Flag);
	}
}
void up_u(userstore p[])
{
	FILE* fp = fopen("userinfo.txt", "w");//只读打开
	if (!fp)
	{
		printf("userinfo.txt文件打开失败\n");
	}
	int i = 0;
	fprintf(fp, "%d\n", Num);
	for (i = 0; i < Num; i++)
	{
		if (p[i].data.Flag > -1)
		{
			fprintf(fp, "%s ", p[i].data.number);
			fprintf(fp, "%s ", p[i].data.password);
			fprintf(fp, "%d ", p[i].data.Flag);
		}
		fprintf(fp, "\n");
	}
}
void creat(booknode* phead)
{
	booknode* r = (booknode*)malloc(sizeof(booknode));
	phead->next = NULL;
	r = phead;
	FILE* fp = fopen("bookinfo.txt", "r");//只读打开
	if (!fp)
	{
		printf("bookinfo.txt文件打开失败\n");
	}
	int i = 0;
	fscanf(fp, "%d", &Booknum);
	for (i = 0; i < Booknum; i++)
	{
		booknode* p = (booknode*)malloc(sizeof(booknode));
		fscanf(fp, "%s", p->data.id);
		fscanf(fp, "%s", p->data.name);
		fscanf(fp, "%s", p->data.actor);
		fscanf(fp, "%s", p->data.day);
		fscanf(fp, "%d", &p->data.price);
		fscanf(fp, "%d", &p->data.num);
		p->next = NULL;
		r->next = p;
		r = p;
	}
}
void updata(booknode* phead)
{
	booknode* p = (booknode*)malloc(sizeof(booknode));
	p = phead->next;
	FILE* fp = fopen("bookinfo.txt", "w");//写入文件
	if (!fp)
	{
		printf("bookinfo.txt文件打开失败\n");
	}
	char arr[30] = { '\0' };
	fprintf(fp, "%d\n", Booknum);
	while (p)
	{
		if (p->data.price > 0)
		{
			fprintf(fp, "%s ", p->data.id);
			fprintf(fp, "%s ", p->data.name);
			fprintf(fp, "%s ", p->data.actor);
			fprintf(fp, "%s ", p->data.day);
			fprintf(fp, "%d ", p->data.price);
			fprintf(fp, "%d", p->data.num);
			fprintf(fp, "\n");
		}
		p = p->next;
	}
}
void add(booknode* phead)
{
	booknode* s = (booknode*)malloc(sizeof(booknode));
	s = phead;
	booknode* p = (booknode*)malloc(sizeof(booknode));
	printf("请输入书的编号\n");
	scanf("%s", p->data.id);
	printf("请输入书的名字\n");
	scanf("%s", p->data.name);
	printf("请输入书的作者\n");
	scanf("%s", p->data.actor);
	printf("请输入书的出版日期,中间以.隔开\n");
	scanf("%s", p->data.day);
	printf("请输入书的价格\n");
	scanf("%d", &p->data.price);
	printf("请输入书的库存\n");
	scanf("%d", &p->data.num);
	p->next = s->next;
	s->next = p;
	Booknum++;
	printf("增加完成\n");
	updata(phead);
}
void delete(booknode* phead)
{
	booknode* p = (booknode*)malloc(sizeof(booknode));
	p = phead->next;
	int n = -1;
	int flag = 0;
	char arr[30] = { '\0' };
	while (n)
	{
		printf("请选择删除的根据\n");
		printf("1.编号\n");
		printf("2.出版时间批量删除\n");
		printf("0.退出保存\n");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("请输入书的编号\n");
			scanf("%s", arr);
			while (p)
			{
				if (strcmp(arr, p->next->data.id) == 0)
				{
					booknode* s = p->next;
					p->next = s->next;
					free(s);
					flag = 1;
					Booknum--;
					printf("删除完成\n");
					break;
				}
				p = p->next;
			}
			if (flag == 0)
			{
				printf("未找到相关图书\n");
			}
			break;
		case 2:
			printf("请输入书的出版日期\n");
			scanf("%s", arr);
			while (p)
			{
				if (strcmp(arr, p->data.day) == 0)
				{
					p->data.price = -1;
					Booknum--;
					flag = 1;
				}
				p = p->next;
			}
			if (flag == 0)
			{
				printf("未找到相关图书\n");
			}
			break;
		case 0:
			break;
		default:
			printf("选择错误请重新选择\n");
			break;
		}
	}
	updata(phead);
}
void change(booknode* phead)
{
	booknode* p = (booknode*)malloc(sizeof(booknode));
	p = phead->next;
	int n = -1;
	int flag = 0;
	char arr[30] = { '\0' };
	printf("请输入书的编号\n");
	scanf("%s", arr);
	while (p)
	{
		if (strcmp(arr, p->data.id) == 0)
		{
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf("未找到相关图书\n");
	}
	while (n)
	{
		printf("请选择修改的内容\n");
		printf("1.编号\n");
		printf("2.名字\n");
		printf("3.作者\n");
		printf("4.价格\n");
		printf("5.出版日期中间以.隔开\n");
		printf("6.库存\n");
		printf("0.退出保存\n");
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			break;
		case 1:
			printf("请输入修改后编号\n");
			scanf("%s", p->data.id);
			break;
		case 2:
			printf("请输入修改后书名\n");
			scanf("%s", p->data.name);
			break;

		case 3:
			printf("请输入修改后作者\n");
			scanf("%s", p->data.actor);
			break;

		case 4:
			printf("请输入修改后价格\n");
			scanf("%d", &p->data.price);
			break;

		case 5:
			printf("请输入修改后日期\n");
			scanf("%s", p->data.day);
			break;
		case 6:
			printf("请输入修改后的库存\n");
			scanf("%d", &p->data.num);
			break;
		default:
			printf("选择错误请重新选择\n");
			break;
		}
	}
	updata(phead);
}
void find(booknode* phead)
{
	booknode* p = phead->next;
	int n = -1;
	int flag = 0;
	char arr[30] = { '\0' };
	char brr[30] = { '\0' };
	while (n)
	{
		printf("1.书名查询\n");
		printf("2.作者查询\n");
		printf("3.书名和作者查询\n");
		printf("0.退出\n");
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			break;
		case 1:
			printf("请输入书名\n");
			scanf("%s", arr);
			p = phead->next;
			while (p)
			{
				if (strcmp(arr, p->data.name) == 0)
				{
					printf("书的编号为:");
					printf("%s\n", p->data.id);
					printf("书的名字为:");
					printf("%s\n", p->data.name);
					printf("书的作者为:");
					printf("%s\n", p->data.actor);
					printf("书的出版日期为:");
					printf("%s\n", p->data.day);
					printf("书的价格为:");
					printf("%d\n", p->data.price);
					printf("书的库存为:");
					printf("%d\n", p->data.num);
				}
				printf("\n");
				p = p->next;
			}
			break;
		case 2:
			printf("请输入作者名\n");
			scanf("%s", brr);
			p = phead->next;
			while (p)
			{
				if (strcmp(brr, p->data.actor) == 0)
				{
					printf("书的编号为:");
					printf("%s\n", p->data.id);
					printf("书的名字为:");
					printf("%s\n", p->data.name);
					printf("书的作者为:");
					printf("%s\n", p->data.actor);
					printf("书的出版日期为:");
					printf("%s\n", p->data.day);
					printf("书的价格为:");
					printf("%d\n", p->data.price);
					printf("书的库存为:");
					printf("%d\n", p->data.num);
				}
				printf("\n");
				p = p->next;
			}
			break;
		case 3:
			printf("请输入书名\n");
			scanf("%s", arr);
			getchar();
			printf("请输入作者名\n");
			scanf("%s", brr);
			p = phead->next;
			while (p)
			{
				if (strcmp(arr, p->data.name) == 0 && strcmp(brr, p->data.actor) == 0)
				{
					printf("书的编号为:");
					printf("%s\n", p->data.id);
					printf("书的名字为:");
					printf("%s\n", p->data.name);
					printf("书的作者为:");
					printf("%s\n", p->data.actor);
					printf("书的出版日期为:");
					printf("%s\n", p->data.day);
					printf("书的价格为:");
					printf("%d\n", p->data.price);
					printf("书的库存为:");
					printf("%d\n", p->data.num);
				}
				p = p->next;
			}
			break;
		default:
			printf("选择错误请重新选择\n");
			break;
		}
	}
}
void add_u(userstore p[])
{
	int m = 0;
	printf("请输入要创建账户的个数\n");
	scanf("%d", &m);
	int n = Num;
	Num = Num + m;
	int i = 0;
	for (i = n; i < Num; i++)
	{
		char arr[20] = { '\0' };
		printf("请输入账号\n");
		scanf("%s", p[i].data.number);
		char brr[20] = "12345";
		strcpy(p[i].data.password, brr);
		printf("输入权限0用户1管理员\n");
		scanf("%d", &p[i].data.Flag);
	}
	printf("增加完成\n");
	up_u(p);
}
void delete_u(userstore p[])
{
	int m = 0;
	printf("请输入要删除账户的个数\n");
	scanf("%d", &m);
	int n = Num;
	Num = Num - m;
	int i = 0;
	for (i = n; i > Num; i--)
	{
		p[i].data.Flag = -2;
	}
	printf("删除完成\n");
	up_u(p);
}
void change_u(userstore p[])
{
	printf("1.修改密码\n");
	printf("2.重置密码\n");
	int s = 0;
	scanf("%d", &s);
	getchar();
	char arr[20] = { '\0' };
	printf("请输入账号\n");
	scanf("%s", arr);
	getchar();
	int i = 0;
	if (s == 1)
	{
		for (i = 0; i < Num; i++)
		{
			if (strcmp(p[i].data.number, arr) == 0)
			{
				printf("请输入新密码\n");
				scanf("%s", p[i].data.password);
				printf("修改完成\n");
				break;
			}
		}
	}
	if (s == 2)
	{
		for (i = 0; i < Num; i++)
		{
			if (strcmp(p[i].data.number, arr) == 0)
			{
				memset(p[i].data.password, '\0', sizeof(p[i].data.password));
				char brr[20] = { "12345" };
				strcpy(p[i].data.password, brr);
				printf("重置完成\n");
				break;
			}
		}
	}
	up_u(p);
}
int find_u(userstore p[], char arr[20])
{
	int i = 0;
	int n = -1;
	for (i = 0; i < Num; i++)
	{
		if (strcmp(arr, p[i].data.number) == 0)
		{
			n = i;
		}
	}
	return n;
}
int secure(userstore p[], int m)
{
	char b[20] = { '\0' };
	printf("请输入密码\n");
	scanf("%s", b);
	int flag = 0;
	if (strcmp(p[m].data.password, b) == 0)
	{
		flag = 1;
	}
	return flag;
}
void menu()
{
	printf("1.增加图书信息\n");
	printf("2.删除图书信息\n");
	printf("3.修改图书信息\n");
	printf("4.查找图书信息\n");
	printf("5.录入成员账号信息\n");
	printf("6.删除成员账号信息\n");
	printf("7.修改密码\n");
	printf("0.退出\n");
}
int main()
{
	userstore people[20];
	booknode* p = (booknode*)malloc(sizeof(booknode));
	creat(p);
	creat_u(people);
	int choose = -1;
	int m = -1;
	char arr[20] = { '\0' };
	while (choose)
	{
		menu();
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("请输入账号\n");
			scanf("%s", arr);
			m = find_u(people, arr);
			if (m > -1)
			{
				if (secure(people, m) == 1 && people[m].data.Flag == 1)
				{
					add(p);
				}
				else
				{
					printf("密码错误或权限不够\n");
				}
			}
			else
			{
				printf("账号错误\n");
			}
			break;
		case 2:
			printf("请输入账号\n");
			scanf("%s", arr);
			m = find_u(people, arr);
			if (m > -1)
			{
				if (secure(people, m) == 1 && people[m].data.Flag == 1)
				{
					delete(p);
				}
				else
				{
					printf("密码错误或权限不够\n");
				}
			}
			else
			{
				printf("账号错误\n");
			}
			break;
		case 3:
			printf("请输入账号\n");
			scanf("%s", arr);
			m = find_u(people, arr);
			if (m > -1)
			{
				if (secure(people, m) == 1 && people[m].data.Flag == 1)
				{
					change(p);
				}
				else
				{
					printf("密码错误或权限不够\n");
				}
			}
			else
			{
				printf("账号错误\n");
			}
			break;
		case 4:
			printf("请输入账号\n");
			scanf("%s", arr);
			m = find_u(people, arr);
			if (m > -1)
			{
				if (secure(people, m) == 1)
				{
					find(p);
				}
				else
				{
					printf("密码错误不够\n");
				}
			}
			else
			{
				printf("账号错误\n");
			}
			break;
		case 5:
			printf("请输入账号\n");
			scanf("%s", arr);
			m = find_u(people, arr);
			if (m > -1)
			{
				if (secure(people, m) == 1 && people[m].data.Flag == 1)
				{
					add_u(people);
				}
				else
				{
					printf("密码错误或权限不够\n");
				}
			}
			else
			{
				printf("账号错误\n");
			}
			break;
		case 6:
			printf("请输入账号\n");
			scanf("%s", arr);
			m = find_u(people, arr);
			if (m > -1)
			{
				if (secure(people, m) == 1 && people[m].data.Flag == 1)
				{
					delete_u(people);
				}
				else
				{
					printf("密码错误或权限不够\n");
				}
			}
			else
			{
				printf("账号错误\n");
			}
			break;
		case 7:
			change_u(people);
			break;
		case 0:
			break;
		default:
			printf("选择错误请重新选择\n");
		}
	}
	return 0;
}
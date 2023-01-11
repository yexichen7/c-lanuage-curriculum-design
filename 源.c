#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void seach_s(char* s, char x)
{
	int i = 0;
	int m = strlen(s);
	int flag = 0;
	for (i = 0; *s != '\0'; i++)
	{
		if (*s == x)
		{
			flag = 1;
			break;
		}
		else
		{
			s++;
		}
	}
	int j = 0;
	if (flag == 1)
	{
		for (j = i; *s != '\0'; j++)
		{
			printf("%c", *s);
			s++;
		}
	}
	else
	{
		printf("Not found");
	}
}
int main()
{
	char a[80];
	gets(a);
	char c;
	scanf("%c", &c);
	seach_s(a, c);
	return 0;
}
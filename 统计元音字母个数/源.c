#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int vowel(char s[20])
{
    int i = 0; int sum = 0;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'a' || s[i] == 'A' || s[i] == 'O' || s[i] == 'o' || s[i] == 'E' || s[i] == 'e' || s[i] == 'I' || s[i] == 'i' || s[i] == 'u' || s[i] == 'U')
        {
            sum++;
        }

    }
    return sum;
}
int main()
{
    int i = 0;
    for (i = 4; i >= -1; i--)
    {
        printf("%d\n", i);
    }
    return 0;
}

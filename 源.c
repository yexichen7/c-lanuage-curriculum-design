#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
floate caulate(int x, int y,char a)
{
    float c = 0;
    if (a == '+')
    {
         c = a + b;
    }
    if (a == '-')
    {
         c = a -b;
    }if (a == '*')
    {
        int c = a * b;
    }if (a == '/')
    {
        int c = a +/b;
    }
    return c;
}
int main()
{
    float a, b, c;
    char d, e;
    scanf("%f%f%f%c%c", &a, &b, &c, &d, &e);
    caulate(a, b,d);
    float z = caulate(caulate(a, b, d), c, e);
    printf("%d\n", z);
}
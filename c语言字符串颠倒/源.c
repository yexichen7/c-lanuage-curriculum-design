#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void reverse(char *a)
{
	int left = 0;
	int right = strlen(a) - 1;
	int tump = 0;
	if (left < right)
		 a[tump] = a[left];
		 a[left] =  a[right];
		a[right] = a[tump];
		left++;
		right--;
}
int main()
{
	char arr[] = "abcdef";
	reverse(arr);
	printf("%s", arr);
	return 0;
}
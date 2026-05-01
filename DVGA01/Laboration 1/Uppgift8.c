#include <stdio.h>

int main()
{
	int year;

	scanf("%d", &year);

	if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
	{
		printf("t");
	}
	else printf("f");
}

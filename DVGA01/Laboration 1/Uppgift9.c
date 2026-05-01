#include <stdio.h>

int main()
{
	int n;

	int bigNum, smallNum;

	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &n);

		if (i == 0)
		{
			bigNum = n;
			smallNum = n;
		}

		if (n <= smallNum)
			smallNum = n;

		if (n >= bigNum)
			bigNum = n;
	}

	printf("%d %d", bigNum, smallNum);
}

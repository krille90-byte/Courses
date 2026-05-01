#include <stdio.h>

int main()
{
	int numbers[4];


	for (int i = 0; i < 5; i++)
	{
		scanf("%d", &numbers[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		if (numbers[i] % 2 == 0)
			printf("even\n");
		else
			printf("odd\n");

	}

	return 0;
}

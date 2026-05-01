#include <stdio.h>

int main()
{
	int num, lastNum = 0;

	while(1)
	{
		scanf("%d", &num);

		if (num == 0)
			break;
			

		lastNum = lastNum + num;

		printf("%d\n", lastNum);
	}

	return 0;
}

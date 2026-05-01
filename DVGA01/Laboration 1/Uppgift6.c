#include <stdio.h>

int main()
{
	int n;
	int sum = 0;
	int i;

	scanf("%d", &n);
	
	for (i = 0; sum < n; i++)
	{
		sum = sum + i;
	}

	printf("%d %d", sum, i-1);

	return 0;
}

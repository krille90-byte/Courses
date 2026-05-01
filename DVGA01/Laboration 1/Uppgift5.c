#include <stdio.h>

int main()
{
	char a;

	scanf("%s", &a);

	switch(a)
	{
		case 's':
		case 'S':
			printf("hej");
			break;

		case 'e':
		case 'E':
			printf("hello");
			break;

		case 't':
		case 'T':
			printf("hallo");
			break;
	}

	return 0;
}

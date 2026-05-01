#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float calc(float param1, float param2, char operator);

int main()
{
	//+, -, *, / och ^

	char _operator;

	float param1;
	float param2;

	scanf("%f %c %f", &param1, &_operator, &param2);

	printf("%g", calc(param1, param2, _operator));

	return 0;
}

float calc(float param1, float param2, char _operator)
{
	float results;

	switch (_operator)
	{
	case '+':
		return results = param1 + param2;

	case '-':
		return results = param1 - param2;

	case '*':
		return results = param1 * param2;

	case '^':
		return pow(param1, param2);

	case '/':
		if (param2 != 0)
			return results = param1 / param2;
		else break;
	}

	printf("NaN");

	exit(0);
}
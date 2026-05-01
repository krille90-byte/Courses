#include <stdio.h>

int main()
{
	int troskelvarde = 204000;
	int brutto;
	int netto;

	scanf("%d", &brutto);

	if (brutto <= troskelvarde)
		netto = brutto - brutto * 0.3;
	else
		netto = brutto - (troskelvarde * 0.3 + (brutto - troskelvarde) * 0.5);

	printf("%d", netto);

	return 0;
}

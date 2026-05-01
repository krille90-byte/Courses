#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

#define REG_FILE "register.txt"

void writeToFile(Cars cars[])
{
	FILE *fp;

	fp = fopen(REG_FILE, "w");

	for (int i = 0; i <= ARRAY_LEN; i++)
	{
		fprintf(fp, "%s %s %s %s %d\n", cars[i].carType,
										cars[i].brand,
										cars[i].licensePlate,
										cars[i].owner.name,
										cars[i].owner.age);
	}
	
	fclose(fp);
}

int readFromFile(Cars cars[])
{
	FILE* fp;
	
	
	fp = fopen(REG_FILE, "r");
	if (fp == NULL)
	{
		printf("File doesn't exist\nCreating file...\n");
		fp = fopen(REG_FILE, "w");
		fclose(fp);
		return 1;
	}

	for (int i = 0; i <= ARRAY_LEN; i++)
	{
		fscanf(fp, "%s %s %s %s %d\n",	cars[i].carType,
										cars[i].brand,
										cars[i].licensePlate,
										cars[i].owner.name,
										&cars[i].owner.age);
	}
	fclose(fp);
}
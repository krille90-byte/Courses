#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int binarySearch(int list[], int start, int end, int number)
{
	if (end >= start)
	{
		int mid = start + (end - start) / 2;
		if (list[mid] == number)
			return mid;
		if (list[mid] > number)
			return binarySearch(list, start, mid - 1, number);
		return binarySearch(list, mid + 1, end, number);
	} return -1;
}

int* bubbleSort(int list[], int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - i; j++)
		{
			if (list[j] > list[j + 1])
			{
				int swap = list[j];
				list[j] = list[j + 1];
				list[j + 1] = swap;
			}
		}
	} return list;
}

void printEmptyLines(int lineNumber)
{
	for (int i = 0; i < lineNumber; i++)
		printf("\n");
}

int addVehicle(Cars cars[])
{
	readFromFile(cars);

	char vechicleType[255];
	char brand[255];
	char licensePlate[255];
	char ownerName[255];
	int ownerAge;

	system("clear");
	printf("What kind of vehicle?\n>>");
	scanf("%s", vechicleType);

	system("clear");
	printf("What brand is the vehicle?\n>>");
	scanf("%s", brand);

	system("clear");
	printf("License plate?\n>>");
	scanf("%s", licensePlate);

	system("clear");
	printf("Owner?\n>>");
	scanf("%s", ownerName);

	system("clear");
	printf("Age?\n>>");
	scanf("%d", &ownerAge);

	for (int i = 0; i <= ARRAY_LEN; i++)
	{
		if (cars[i].owner.age == -1)
		{
			strcpy(cars[i].carType, vechicleType);
			strcpy(cars[i].brand, brand);
			strcpy(cars[i].licensePlate, licensePlate);
			strcpy(cars[i].owner.name, ownerName);
			cars[i].owner.age = ownerAge;

			break;
		}
		else if (i == 9)
				printf("LIST IS FULL, DICKHEAD\n"); //FILIP HULTBRAND 2021-12-06 23:17
													//FILIP TAR AVSTÅND FRÅN DETTA 2021-12-06 23:39
		
	}

	writeToFile(cars);

	//system("clear");
}

void removeVehicle(Cars cars[])
{
	readFromFile(cars);

	int index;

	printf("What vehicle should be removed?\n>>");
	scanf("%d", &index);

	index--;

	strcpy(cars[index].carType, ".");
	strcpy(cars[index].brand, ".");
	strcpy(cars[index].licensePlate, ".");
	strcpy(cars[index].owner.name, ".");
	cars[index].owner.age = -1;

	writeToFile(cars);
}

void resetFile(Cars cars[])
{
	for (int i = 0; i <= ARRAY_LEN; i++)
	{
		strcpy(cars[i].carType, ".");
		strcpy(cars[i].brand, ".");
		strcpy(cars[i].licensePlate, ".");
		strcpy(cars[i].owner.name, ".");
		cars[i].owner.age = -1;
	}
	writeToFile(cars);
}
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "Labb4.h"

void main()
{
	Cars cars[ARRAY_LEN];

	int b[10][10];

	int alternatives;	//1 = Add car
						//2 = Remove car
						//3 = Sort cars
						//4 = Print car specs
						//5 = Print whole register
						//6 = Exit

	readFromFile(cars);

	system("clear");

	while (1)
	{
		printf("The following alternatives are available:\n"
			"\n1: Add vehicle\n"
			"2: Remove vehicle\n"
			"3: Sort vehicles\n"
			"4: Print vehicle specs\n"
			"5: Print whole register\n"
			"6: Exit\n");

		printf("\nWhat do you want to do?\n>>");
		scanf("%d", &alternatives);

		switch (alternatives)
		{
		case 1:
			addVehicle(cars);
			break;

		case 2:
			removeVehicle(cars);
			break;

		case 3:
			break;

		case 4:
			system("clear");
			resetFile(cars);
			break;

		case 5:
			system("clear");
			for (int i = 0; i <= ARRAY_LEN; i++)
			{
				printf("%s %s %s %s %d\n",	cars[i].carType,
											cars[i].brand,
											cars[i].licensePlate,
											cars[i].owner.name,
											cars[i].owner.age);
			}

			break;

		case 6:
			system("clear");
			writeToFile(cars);
			exit(0);
			break;

		default:
			system("clear");
			printf("Alternative not available");
			break;
		}
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_LEN 99
#define ARRAY_MAX 900

#define RED_TEXT "\033[0;31m"
#define YELLOW_TEXT "\033[0;33m"
#define GREEN_TEXT "\033[0;32m"
#define BOLD_BLUE_TEXT "\033[1;34m"

int * generateNumbers(int list[]);
int * bubbleSort(int list[]);
void getMaxMin(int list[]);
int binarySearch(int list[], int start, int end, int number);
void printGraph(int list[]);
void printEmptyLines(int lineNumber);

void main()
{
	int numberList[ARRAY_LEN];

	int alternatives;	//1 = Generate random numbers
						//2 = Sort numbers, ascending order
						//3 = Get max, min, average and median values
						//4 = Search for a number
						//5 = Exit the program

	int haveRun = 0;	//0 = no cases have run
						//1 = case 1 has ran
						//2 = case 2 has ran

	system("clear");
	printEmptyLines(7);
	printf("%sGreen alternatives are executable, but red alternatives are\nnot executable until other "
			"alternatives have been executed\n", YELLOW_TEXT);
	printEmptyLines(7);

	while (1)
	{
		if (haveRun == 0)
		{
			printf("\n%sThe following alternatives are available:\n"
				"\n%s1: Generate random numbers into a list\n"
				"%s2: Sort numbers in the list, ascending order\n"
				"3: Get max, min, average and median values of the list\n"
				"4: Search for a number in the list\n"
				"%s5: Exit the program\n", BOLD_BLUE_TEXT, GREEN_TEXT, RED_TEXT, GREEN_TEXT);
		}
		else if (haveRun == 1)
		{
			printf("\n%sThe following alternatives are available:\n"
				"\n%s1: Generate random numbers into a list\n"
				"2: Sort numbers in the list, ascending order\n"
				"%s3: Get max, min, average and median values of the list\n"
				"4: Search for a number in the list\n"
				"%s5: Exit the program\n", BOLD_BLUE_TEXT, GREEN_TEXT, RED_TEXT, GREEN_TEXT);
		}
		else if (haveRun == 2)
		{
			printf("\n%sThe following alternatives are available:\n"
				"\n%s1: Generate random numbers into a list\n"
				"2: Sort numbers in the list, ascending order\n"
				"3: Get max, min, average and median values of the list\n"
				"4: Search for a number in the list\n"
				"5: Exit the program\n", BOLD_BLUE_TEXT, GREEN_TEXT);
		}

		printf("\033[0m>>");
		scanf("%d", &alternatives);

		switch (alternatives)
		{
		case 1:
			haveRun = 1;
			generateNumbers(numberList);
			system("clear");
			printGraph(numberList);
			printEmptyLines(5);
			break;

		case 2:
			if (haveRun != 0)
			{
				haveRun = 2;
				bubbleSort(numberList);
				system("clear");
				printGraph(numberList);
				printEmptyLines(5);
				break;
			}
			else
			{
				system("clear");
				printf("Alternative not available until alternative #1 has been executed\n");
				printEmptyLines(15);
				break;
			}

		case 3:
			if (haveRun == 2)
			{
				system("clear");
				printGraph(numberList);
				getMaxMin(numberList);
				break;
			}
			else
			{
				system("clear");
				printf("Alternative not available until alternative #2 has been executed\n");
				printEmptyLines(15);
				break;
			}

		case 4:                                                                                                                                                                                                                                                                                                                         ;
			if (haveRun == 2)
			{
				system("clear");
				int number;
				printGraph(numberList);
				printf("\nInput desired number: ");
				scanf("%d", &number);
				int results = binarySearch(numberList, 0, ARRAY_LEN, number);

				if (results == -1)
				{
					printf("\nNumber is not present in array\n");
				}
				else
				{
					int row = (results % 10) + 1;
					int column = (results / 10) + 1;
					printf("\nColumn: %d\nRow: %d", column, row);
				}				

				printEmptyLines(1);
				break;
			}
			else
			{
				system("clear");
				printf("Alternative not available until alternative #2 has been executed\n");
				printEmptyLines(10);
				break;
			}
		case 5:
			system("clear");
			exit(0);
			break;

		default:
			system("clear");
			printf("Alternative not available\n");
			printEmptyLines(10);
			break;
		}
	}
}

int* generateNumbers(int list[])
{
	srand(time(0));

	for (int i = 0; i <= ARRAY_LEN; i++)
		list[i] = rand() % 901;

	return list;
}

int* bubbleSort(int list[])
{
	for (int i = 0; i < ARRAY_LEN; i++)
	{		
		for (int j = 0; j < ARRAY_LEN - i; j++)
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

void getMaxMin(int list[])
{
	float listSum = 0;
	float mean;
	float median;

	for (int i = 0; i <= ARRAY_LEN; i++)
		listSum += list[i];

	mean = listSum / ARRAY_LEN;

	median = (list[49] + list[50]) / 2.0;

	printf("\nMin: %d\nMax: %d\nMean: %g\nMedian: %g\n", list[0], list[ARRAY_LEN], mean, median);
}

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

void printGraph(int list[])
{
	int rowPos = 0;
	int i = 0;

	printf("+———————————————————————————————————————————————————————————————————————————————+\n");
	while (i <= ARRAY_LEN)
	{
		printf("|  %d\t", list[i]);
		i += 10;

		if (i == 90 + rowPos)
		{
			printf("|  %d\t|\n", list[i]);

			rowPos++;
			i = rowPos;		
		}
		if (rowPos > 9)
			break;
	}
	printf("+———————————————————————————————————————————————————————————————————————————————+");
}

void printEmptyLines(int lineNumber)
{
	for (int i = 0; i < lineNumber; i++)
		printf("\n");
}
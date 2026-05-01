#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Labb4.h"

//functions.c
extern int binarySearch(int list[], int start, int end, int number);
extern int* bubbleSort(int list[], int length);
extern void printEmptyLines(int lineNumber);
extern int addVehicle(Cars _struct[]);
extern void removeVehicle(Cars cars[]);
extern void resetFile(Cars cars[]);

//fileManagement.c
extern void writeToFile(Cars _struct[]);
extern int readFromFile(Cars cars[]);



#endif
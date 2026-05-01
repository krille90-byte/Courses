#ifndef LABB4_H
#define LABB4_H

#define ARRAY_LEN 9

typedef struct
{
	char name[255];
	int age;
} Owners;

typedef struct
{
	char carType[255];
	char brand[255];
	char licensePlate[255];

	Owners owner;
} Cars;

#endif
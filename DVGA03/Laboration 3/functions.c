// innehåller funktioner för användarens val (1 -> 12)
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "list.h"

void clearTerm() {
	// printf("\e[1;1H\e[2J");
	system("clear");
}

int safeInput() {
	int input = 0;
	char* line = NULL;
	size_t len = 0;

	printf("> ");

	if(getline(&line, &len, stdin) == -1)
		exit(1);
	if(sscanf(line, "%d", &input) != 1) {
		printf("Inte en siffra.\n");
		input = safeInput(); // Rekursion
	}

	return input;
}

void printList(node *head) { // 1
	clearTerm();
	printf("+===== Hela Listan =====+\n| Position\tVärde   |\n+———————————————————————+\n");
	for(int i = 0; i < getListLen(head); i++)
		printf("| %d\t\t%d\t|\n", i+1, getNode(head, i)->data);
	if(getListLen(head) == 0)
		printf("|     Listan är tom     |\n");
	printf("+———————————————————————+\n");
}

void printListLen(node *head) { // 2
	clearTerm();
	printf("Listans längd: %d", getListLen(head));
}

void appendToList(node *head) { // 3
	clearTerm();
	printf("Vilken siffra vill du lägga till?\n");
    int data = safeInput();
	addNode(head, data, getListLen(head));
	clearTerm();
	printf("Okej, %d lades till.", data);
}

void addToList(node *head) { // 4
	clearTerm();
	printf("Vilken siffra vill du lägga till?\n");
    int data = safeInput();
	printf("Och vart?\n");
    int index = safeInput();
	if((index > getListLen(head) || index < 1) && index != 1) {
		printf("Segmentation fault");
		return;
	}
	addNode(head, data, index-1);
	clearTerm();
	printf("Okej, %d lades till.", data);
}

void printAddress(node *head) { // 12
	clearTerm();
	printf("Startadress: %p", head);
}

void clearList(node *head) { // 7
	clearTerm();
	int count = getListLen(head);
	for(int i = 0; i < count; i++)
		deleteNode(head, 0);
	printf("Listan tömdes.");
}

void reverseList(node **head) { // 8
	clearTerm();
	flipList(head);
	printf("Listan vändes.");
}

void moveList(node *head, int leftBool) { // 9 & 10
	clearTerm();
	if(getListLen(head) < 2) { printf("Listan hade ej förändrats av en skiftning."); return; }
	printf("Skiftar listan till ");
	leftBool ? printf("vänster..\n") : printf("höger..\n");
	shiftList(head, leftBool);
	printf("Listan skiftad.");
}

void orderList(node *head) { // 11
	clearTerm();
	sortList(head);
	printf("Listan sorterad.");
}

void deleteAllInstancesOf(node *head) { // 5
	clearTerm();
	printf("Vilken siffra vill du ta bort?\n");
    int data = safeInput();
	int amountToDelete = 0, instancesDeleted = 0;

	for(int i = 0; i < getListLen(head); i++) {
		if(getNode(head, i)->data == data) {
			amountToDelete++;
		}
	}

	int i = 0;
	while(amountToDelete > 0) {
		if(getNode(head, i)->data == data) {
			deleteNode(head, i);
			amountToDelete--;
			instancesDeleted++;
			i = 0;
			continue;
		}
		i++;
	}

	printf("%d instans(er) av värdet %d hittades", instancesDeleted, data);
	instancesDeleted != 0 ? printf(", och togs bort.") : printf(".");
}

void deleteInstanceAt(node *head) { // 6
	clearTerm();
	printf("Vilken position vill du ta bort?\n");
    int index = safeInput();
	if(index > getListLen(head) || index < 1) {	
		printf("Det värdet finns inte.");
		return;
	}
	deleteNode(head, index-1);
	printf("Länken på plats %d är borttagen.", index);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "main.h"
#include "functions.h"

int main() {
	node* headNode = (node*)malloc(sizeof(node)); // allokera minne för huvudnoden
	headNode->next = NULL; // huvudnodens nästa finns inte. (än)

	clearTerm();
	while(1) { // repetera datainmatning tills användaren avbryter programmet
		printf("\n%s%sFöljande alternativ är tillgängliga:%s\n"
			" 0: Avsluta,\n"
			" 1: Skriv ut listan,\n"
			" 2: Skriv ut listans storlek,\n"
			" 3: Lägg till ett heltal sist i listan,\n"
			" 4: Lägg till ett heltal (valfri plats),\n"
			" 5: Ta bort ett givet heltal,\n"
			" 6: Ta bort ett heltal (valfri plats),\n"
			" 7: Töm listan,\n"
			" 8: Vänd på listan,\n"
			" 9: Skifta listan ett steg till vänster (och lägg första heltalet sist),\n"
			"10: Skifta listan ett steg till höger (och lägg sista heltalet först),\n"
			"11: Sortera listan (lägsta heltalet först),\n"
			"12: Skriv ut startadress för listan.\n",
			BLUE_TEXT, BOLD_TEXT, RESET_TEXT);
		int opt = safeInput();

		switch(opt) {
			case 0: // exit program
				exit(0); break;
			case 1: // print list
				printList(headNode); break;
			case 2: // print list size
				printListLen(headNode); break;
			case 3: // append int to list
				appendToList(headNode); break;
			case 4: // add int to list (any position)
				addToList(headNode); break;
			case 5: // remove a given int
				deleteAllInstancesOf(headNode);
				break;
			case 6: // remove an int (any pos)
				deleteInstanceAt(headNode);
				break;
			case 7: // clear list
				clearList(headNode);
				break;
			case 8: // flip list
				reverseList(&headNode->next);
				break;
			case 9: // shift list to the left (first value becomes the last)
				moveList(headNode, 1); // 1 = bool, left
				break;
			case 10: // shift list to the right (last value becomes the first)
				moveList(headNode, 0); // 0 = bool, right
				break;
			case 11: // sort list (smallest int first)
				orderList(headNode);
				break;
			case 12: // print list's starting address
				printAddress(headNode);
				break;
			default: // korrekt nummerinmatning, men siffran finns inte som ett alternativ
                clearTerm();
				printf("Försök igen!.");
				break;
		}
	}
	return 0;
}
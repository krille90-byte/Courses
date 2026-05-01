#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"

/*
 * clearTerm tömmer text i terminalen.
 * INPUT: N/A; OUTPUT: N/A.
 */
extern void clearTerm();

/* 
 * safeInput ser till att användaren inte får mata in bokstäver
 * INPUT: N/A; OUTPUT: värdet användaren matar in (int).
 */
extern int safeInput();

/*
 * printList skriver ut hela listan i en tabell.
 * INPUT: N/A; OUTPUT: N/A.
 */
extern void printList();

/*
 * printListLen skriver ut längden på listan.
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void printListLen(node *list);

/*
 * appendToList lägger till ett tal sist i listan
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void appendToList(node *head);

/*
 * addToList frågar användaren om en position och data och lägger till datan på det indexet i listan.
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void addToList(node *head);

/*
 * printAddress skriver ut addressen för listans startposition (nodhuvudet).
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void printAddress(node *head);

/*
 * clearList tömmer listan, och frigör minnet
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void clearList(node *head);

/*
 * reverseList vänder listan (sist värde hamnar först).
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void reverseList(node **head);

/*
 * moveList skiftar listan höger eller vänster.
 * leftBool bör vara satt till 1 om listan ska skiftas till vänster, annars skiftas den till höger.
 * INPUT: nodhuvud (node), skift-riktning ("boolean", int 0/1); OUTPUT: N/A.
 */
extern void moveList(node *head, int leftBool);

/*
 * orderList sorterar listan med bubble-sortering
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void orderList(node *head);

/*
 * deleteAllInstancesOf tar bort alla instanser av ett värde (som funktionen ber användaren att ange) från listan
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void deleteAllInstancesOf(node *head);

/*
 * deleteAllInstancesOf tar bort alla instanser som användaren anger
 * INPUT: nodhuvud (node); OUTPUT: N/A.
 */
extern void deleteInstanceAt(node *head);

#endif /* FUNCTIONS_H */

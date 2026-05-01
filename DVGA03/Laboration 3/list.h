#ifndef LIST_H
#define LIST_H

#include "main.h"

/*
 * getNode returnerar den noden som finns på indexets position.
 * INPUT: nodhuvudet (pekare av typ node), index för noden som ska hämtas (typ int); OUTPUT: den begärda noden (typ node).
 */
extern node *getNode(node *head, int index);

/*
 * addNode lägger till en node i den länkade listan på en given plats.
 * INPUT: nodhuvudet (node, pekare), data som ska läggas till (int), index för position för datan (int); OUTPUT: N/A.
 */
extern void addNode(node *head, int data, int index);

/*
 * deleteNode tar bort noder ifrån den länkade listan.
 * INPUT: nodhuvudet (node, pekare), index som ska tas bort (int); OUTPUT: N/A.
 */
extern void deleteNode(node *head, int index);

/*
 * getListLen returnerar längen på listan.
 * INPUT: nodhuvudet (node, pekare); OUTPUT: längden på listan (int).
 */
extern int getListLen(node *head);

/*
 * sortList är funktion som sorterar listan. det är en bubble sort.
 * INPUT: nodhuvudet (node, pekare); OUTPUT: N/A.
 */
extern void sortList(node *head);

/*
 * flipList.
 * INPUT: nodhuvudet (node, pekare); OUTPUT: N/A.
 */
extern void flipList(node **head);

/*
 * shiftList skiftar listan till höger eller vänster, beronde på
 * en psuedo-boolean (en int) som säger det ska skiftas till vänster (annars höger).
 * INPUT: nodhuvudet (node, pekare), om den ska gå till vänster ("boolean", 0/1); OUTPUT: N/A.
 */
extern void shiftList(node *head, int leftDirection);

#endif

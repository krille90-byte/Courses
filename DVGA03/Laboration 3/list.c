#include <stdlib.h>
#include "list.h"

node *getNode(node *head, int index) {
    node *n = head;
    for (int i = 0; i <= index; i++) // iterera genom all noder tills destinationen hittas (nodhuvud exkluderat)
        n = n->next;
    return n;
}

void addNode(node *head, int data, int index) {
	node *n = getNode(head, index - 1); // get the node in the place before

    node *newNode = (node*)malloc(sizeof(node)); // allokera minne
    newNode->data = data; // ge den nya noden data..
    newNode->next = n->next; // ..och sätt dens följande nod
    n->next = newNode;
}

void deleteNode(node *head, int index) {
    void* address = getNode(head, index); // addressen som ska frigöras
    node *prev = getNode(head, index - 1); // hämtar noden innan den noden som ska tas bort
    node *next = prev->next->next; // hämtar noden som kommer efter den noden som ska tas bort

    prev->next = next; // ändrar pekare, tidigare pekar på noden som kommer efter den som togs bort
    free(address); // frigör addressen från minnet
}

int getListLen(node *head) {
    int len = 0;
    node *n = head;
    while(1) {
        if(n->next == NULL) // break:a om vi har träffat den sista noden.
            break;
        len++;
        n = n->next;
    }
    return len;
}

void flipList(node **head) {
    if(*head == NULL) { return; } // om listan är tom vill vi inte göra något
    node* last = NULL; 
    node* current = *head;
    node* next = NULL;
    while (current != NULL) {
        // byt plats på de närliggande nodernas next-värde. "flippar pilarna"
        next = current->next;
        current->next = last;
        last = current;
        current = next;
    }
    *head = last; // huvudet blir den sista (alltså den är vänd)
}

void sortList(node *head) {
    // bubbelsortering
    for (int i = 0; i < getListLen(head); i++) {
        for (int j = 0; j < getListLen(head) - i - 1; j++) {
            if (getNode(head, j)->data > getNode(head, j)->next->data) { // är datan större än nästa nods data?
                // byt plats på de närliggande nodernas data.
                int temp = getNode(head, j)->data; 
                getNode(head, j)->data = getNode(head, j)->next->data;
                getNode(head, j)->next->data = temp;
            }
        }
    }
}

void shiftList(node *head, int leftDirection) {
    node *lastNode = getNode(head, getListLen(head)-1);
    node *firstNode = getNode(head, 0); // första noden (huvudnoden räknas inte)
    if(leftDirection) {
        head->next = firstNode->next; // huvudet pekar dit den första pekade innan (den andra i listan)
        firstNode->next = NULL; // första noden (nu sist) ska peka på null
    } else {
        getNode(head, getListLen(head)-2)->next = NULL; // näst sista (nu sista) pekar nu på null
        head->next = lastNode; // huvudet pekar på sista noden (nu först)
    }
    lastNode->next = firstNode; // i båda fallen kommer den sista noden att behöva peka på den första
                                // (antingen hamnar den sista först, eller den första sist)
}

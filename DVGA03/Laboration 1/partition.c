#include <stdio.h>
#include <stdlib.h>

int antal = 10;
int vek[] = {4,5,2,2,1,6,7,9,5,10};

/* Funktion som grovsorterar arrayen (index a till b) */
int partition(int v[], int a, int b) {
   int pivot, lower, upper, temp;
   pivot = v[a];
   lower = a + 1;
   upper = b;
   do {
     while (v[lower] <= pivot && lower <= upper) {
        lower = lower + 1;
     } 
     while (v[upper] > pivot && lower <= upper) {
        upper = upper - 1;
        // printf("v[upper] = %d, pivot = %d\nlower = %d, upper = %d\n\n", v[upper], pivot, lower, upper);
     } 
     if (lower <= upper) {
        temp = v[lower];
        v[lower] = v[upper];
        
        v[upper] = temp;
        lower = lower + 1;
        upper = upper - 1;
     }
   }while (lower <= upper);
   temp = v[upper];
   v[upper] = v[a];
   v[a] = temp;

   return upper;
}

/* Rekursiv funktion som sorterar en array (index a till b) */
void quickSort(int v[], int a, int b) {
   int k;
   if (a < b) {
     k = partition(v, a, b);
     quickSort(v, a, k-1);
     quickSort(v, k+1, b);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
   }
}

/* Funktion som skriver ut elementen i en array */
void skriv(int v[], int size) {
   int i;
   printf("\n");
   for (i = 0; i < size; i++)
     printf("%d ", v[i]);
   printf("\n");
}

/* Huvudprogrammet */
int main() {
//    skriv(vek, antal);
   quickSort(vek, 0, antal-1);
//    skriv(vek, antal);
   return 0;
}
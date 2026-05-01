#include "analyze.h"
#include "algorithm.h"

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
//
// Private
//


static double runTimeSort(void (*runnableFunc)(int*, int), int* arr, int length) {
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
    runnableFunc(arr, length);
    clock_gettime(CLOCK_REALTIME, &stop);

    //Konverterar sekunder till nano sekunder.
    return (stop.tv_sec - start.tv_sec) + ((stop.tv_nsec - start.tv_nsec)*pow(10, -10));
}


static double runTimeSearch(bool (*runnableFunc)(const int*, int, int), int* arr, int length, int varde) {
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
    runnableFunc(arr, length, varde);
    clock_gettime(CLOCK_REALTIME, &stop);
    return (stop.tv_sec - start.tv_sec) + ((stop.tv_nsec - start.tv_nsec)*pow(10, -10));
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n){
        srand(time(0));

    double totalResults[ITERATIONS][n];
    for(int i = 0; i < ITERATIONS; i++) {
        for(int j = 0; j < n; j++) {
            buf[j].size = pow(2, j+9); // 2^(9 + n rad) för att starta vid 512.
            int placeHolderLista[buf[j].size];
            int varde = 0; // Används vid sökningen.
            if(c == 0) { // Bästa resultatet(Best case)
                if(a == quick_sort_t || a == linear_search_t) { // QuickSort och linear sökning har olika "Best case" algoritmer.
                    for(int k = 0; k < buf[j].size; k++){
                        placeHolderLista[k] = rand() % buf[j].size;
                        varde = placeHolderLista[(buf[j].size - 1) / 2];
                    }
                } else {
                    for(int k = 0; k < buf[j].size; k++){
                        placeHolderLista[k] = k;
                        varde = buf[j].size / 2;
                    }
                }
            } else if(c == 1) { // Värsta resultatet(Worst case)
                if(a == binary_search_t || a == linear_search_t)
                    varde = -1; // Kommer aldrig att vara närvarande i arrayen, så sökningen måste alltid gå igenom varje element i arrayen.
                for(int k = buf[j].size - 1; k >= 0; k--)
                    placeHolderLista[buf[j].size - 1 - k] = k;
            } else if(c == 2) { // Genomsnittliga resultatet(Average case)
                for(int k = 0; k < buf[j].size; k++){
                    placeHolderLista[k] = rand() % buf[j].size;
                    varde = placeHolderLista[(buf[j].size - 1) / 2];
                }
            }
            switch(a) {
                case bubble_sort_t:
                    totalResults[i][j] = runTimeSort(&bubble_sort, placeHolderLista, buf[j].size);
                    break;
                case insertion_sort_t:
                    totalResults[i][j] = runTimeSort(&insertion_sort, placeHolderLista, buf[j].size);
                    break;
                case quick_sort_t:
                    totalResults[i][j] = runTimeSort(&quick_sort, placeHolderLista, buf[j].size-1);
                    break;
                case linear_search_t:
                    totalResults[i][j] = runTimeSearch(&linear_search, placeHolderLista, buf[j].size, varde);
                    break;
                case binary_search_t:
                    quick_sort(placeHolderLista, buf[j].size); // binary search fungerar enbart på en sorterad array.
                    totalResults[i][j] = runTimeSearch(&binary_search, placeHolderLista, buf[j].size, varde);
                    break;
                default:
                return;
            }
        }
    }

    // Kalkylerar genomsnittliga körningen per rad.
    for(int i = 0; i < n; i++) {
        double tidSum = 0;
        for(int j = 0; j < ITERATIONS; j++)
            tidSum += totalResults[j][i];
        buf[i].time = tidSum / ITERATIONS;
    }
}

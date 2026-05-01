#include "algorithm.h"

#include <stdlib.h>
//
// Private
//

// Bytar plats på två värden i en array.
static void byta_plats(int *arr, int pos1, int pos2){
	int temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}

// Best: O(n)
// Worst: O(n^2)
// Average: O(n^2)
static void perform_quick_sort(int *arr, int n, int d){
	if(d < n) {
		int pivot = arr[n], i = (d - 1);
		for(int j = d; j <= n - 1; j++) {
			if(arr[j] < pivot) {
				i++;
				byta_plats(arr, i, j);
			}
		}
		byta_plats(arr, i + 1, n);
		perform_quick_sort(arr, i, d);
		perform_quick_sort(arr, n, i+2);
	}
}

// Best: O(n)
// Worst: O(n^2)
// Average: O(n^2)
static bool perform_binary_search(const int *a, int n, int v, int start) {
	if(n >= start) {
		int middle = start + (n - start) / 2;
		if(a[middle] == v)
				return true;
		if(a[middle] > v)
				return perform_binary_search(a, middle - 1, v, start);
		return perform_binary_search(a, n, v, middle + 1);
	} return false;
}


//
// Public
//

// Best: O(n)
// Worst: O(n^2)
// Average: O(n^2)
void bubble_sort(int *a, int n){
	bool flagga = false;
	for(int i = 0; i < n - 1; i++) {
		for(int j = 0; j < n - i - 1; j++) {
			if(a[j] > a[j + 1]) {
				byta_plats(a, j, j + 1);
				flagga = true;
			}
		}
		if (!flagga){
			break; // Listan är sorterad om inga byten har skett i hela iterationen.
		}
	}
}

// Best: O(n)
// Worst: O(n^2)
// Average: O(n^2)
void insertion_sort(int *a, int n){
	for (int i = 1; i < n; ++i) {
			int key = a[i];
			int j = i - 1;

			while (j >= 0 && a[j] > key) {
				a[j + 1] = a[j];
				--j;
			}
			a[j + 1] = key;
		}
}

void quick_sort(int *a, int n){
	perform_quick_sort(a, n, 0);
}

bool linear_search(const int *a, int n, int v){
		for(int i = 0; i < n; i++)
		if(a[i] == v) return true;
	    return false;
}

bool binary_search(const int *a, int n, int v){
	return perform_binary_search(a, n, v, 0);
}

#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//
// Private
//
static void print_tab(int n) {
    for (int i = 0; i < n; ++i) {
        printf("\t");
    }
}
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i = 0; i < num_options; i++) {
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}
static void skrift(){
	printf("size");
	print_tab(1);
	printf("time T(s)");
	print_tab(1);
	printf("T/1");
	print_tab(2);
	printf("T/logn");
	print_tab(2);
	printf("T/n");
	print_tab(2);
	printf("T/n/2");
	print_tab(2);
	printf("T/nlogn");
	print_tab(2);
	printf("T/n^2");
	print_tab(2);
	printf("T/n^3\n");
}

static void utskrift_av_lista(const algorithm_t a, const case_t c, result_t *listan) {
	char algo[15];
	ui_line('*', MENU_WIDTH*3.36);
	
	switch(a) {
		case bubble_sort_t:
		strcpy(algo, "bubble sort");
		break;

		case insertion_sort_t:
		strcpy(algo, "insertion sort");
		break;
		
		case quick_sort_t:
		strcpy(algo, "quick sort");
		break;

		case linear_search_t:
		strcpy(algo, "linear search");
		break;

		case binary_search_t:
		strcpy(algo, "binary search");
		break;

		default:
		printf("ogiltig algoritm\n");
		return;
		break;
	}
	print_tab(7);
	printf("%s: %s\n", algo, c == 0 ? "best" : c == 1 ? "worst" : "average");
	
	ui_line('~', MENU_WIDTH*3.36);
	skrift();
	ui_line('~', MENU_WIDTH*3.36);

			for(int i = 0; i < RESULT_ROWS; i++){ 
			printf("%d\t%.8lf", listan[i].size, listan[i].time);
			printf("\t%.8e", listan[i].time / 1);										// T/1
			printf("\t%.8e", listan[i].time / log2(listan[i].size));					// T/logn
			printf("\t%.8e", listan[i].time / listan[i].size);							// T/n
			printf("\t%.8e", listan[i].time / (listan[i].size / 2));					// T/n/2
			printf("\t%.8e", listan[i].time / (listan[i].size * log2(listan[i].size)));	// T/nlogn
			printf("\t%.8e", listan[i].time / pow(listan[i].size, 2));					// T/n^2
			printf("\t%.8e", listan[i].time / pow(listan[i].size, 3));					// T/n^3
			printf("\n");
			}
		
	ui_line('*', MENU_WIDTH*3.36);
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case\n"
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

static void get_Result(const algorithm_t a, case_t c, result_t* result) {
	benchmark(a, c, result, RESULT_ROWS);
	utskrift_av_lista(a, c, result);
}

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			// Bubble sort
			case 'c':
				get_Result(bubble_sort_t, best_t, result);
			//	printf("todo> implemenet BE + present results in FE\n");
				break;
			case 'd':
				get_Result(bubble_sort_t, worst_t, result);
				break;
			case 'e':
				get_Result(bubble_sort_t, average_t, result);
				break;
			// Insertion sort
			case 'f':
				get_Result(insertion_sort_t, best_t, result);
				break;
			case 'g':
				get_Result(insertion_sort_t, worst_t, result); 
				break;
			case 'h':
				get_Result(insertion_sort_t, average_t, result);
				break;
			// quick sort
			case 'i':
				get_Result(quick_sort_t, best_t, result);
				break;
			case 'j':
				get_Result(quick_sort_t, worst_t, result);
				break;
			case 'k':
				get_Result(quick_sort_t, average_t, result);
				break;
			// linear search
			case 'l':
				get_Result(linear_search_t, best_t, result);
				break;
			case 'm':
				get_Result(linear_search_t, worst_t, result);
				break;
			case 'n':
				get_Result(linear_search_t, average_t, result);
				break;
			// binary search
			case 'o':
				get_Result(binary_search_t, best_t, result);
				break;
			case 'p':
				get_Result(binary_search_t, worst_t, result);
				break;
			case 'q':
				get_Result(binary_search_t, average_t, result);
				break;

			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}


#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BOLD_TEXT "\033[1m"
#define RESET_TEXT "\x1b[0m"
#define AVAIL_MEM 65536
#define FRAME_SIZE 256

typedef struct {
    int memoryAccesses;
    int pageHits;
    int pageFaults;
    int pageReplacements;
} stats;

typedef struct trace {
    int* address;
    int length;
} trace;

#endif

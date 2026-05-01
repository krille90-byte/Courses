#ifndef VM_H
#define VM_H

#include "main.h"

typedef struct {
    unsigned int frameP;
    int isValid;
    int nextArrival; // optimal
    int amountUsed; // LRU
} pageTableEntry;

typedef struct {
    pageTableEntry pageTableEntries[AVAIL_MEM/FRAME_SIZE]; // 256 frames
} pageTable;

extern void vmInit(int algorithm, int frameCount, trace traces);
extern void vmAccess(unsigned int addr);
int isMemFull();
extern void fifo(unsigned int addr, unsigned int pageNumber);
extern void optimal(unsigned int addr, unsigned int pageNumber);
extern void lru(unsigned int addr, unsigned int pageNumber);
extern stats getStatistics();

#endif
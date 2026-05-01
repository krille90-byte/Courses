#include "vm.h"

stats statistics;
pageTable pt;
int *freeFrames;
int algorithm, frameCount, time;
trace traces2;

void vmInit(int algorithm, int frameCount, trace traces) {
    traces2 = traces;
    time = 0;
    algorithm = algorithm;
    frameCount = frameCount;
    freeFrames = (int*)malloc(frameCount * sizeof(int));

    for(int i = 0; i < frameCount; i++)
        freeFrames[i] = 0;

    for(int i = 0; i < AVAIL_MEM/FRAME_SIZE; i++) { // make all used frames invalid
        pt.pageTableEntries[i].isValid = 0;
        pt.pageTableEntries[i].amountUsed = 0;
        pt.pageTableEntries[i].nextArrival = 0;
    }

    statistics.memoryAccesses = 0;
    statistics.pageHits = 0;
    statistics.pageFaults = 0;
    statistics.pageReplacements = 0;

    printf("\n");
}

void vmAccess(unsigned int addr) {
    int addrPos = addr / FRAME_SIZE; // ram-index i page table
    switch(algorithm) {
        case 0:
            fifo(addr, addrPos);
            break;
        case 1:
            optimal(addr, addrPos);
            break;
        case 2:
            lru(addr, addrPos);
            break;
         default: printf("Jo tjena! Good try.\n"); break;
    }
    statistics.memoryAccesses++;
}

stats getStatistics() { return statistics; }

int isMemFull() {
    for (int i = 0; i < frameCount; i++)
        if (!freeFrames[i]) { return 0; } 
    return 1;
}

int oldestFrame = 0;
void fifo(unsigned int addr, unsigned int pageNumber) {
    for(int i = 0; i < frameCount; i++) {
        if (!pt.pageTableEntries[pageNumber].isValid) {
            printf("Address %04x not in physical memory\n", addr);
            if(isMemFull()) {
                printf("Page #%d paged out\n", oldestFrame);
                printf("Page #%d paged in\n", pageNumber);
                statistics.pageReplacements++;
                statistics.pageFaults++;
                pt.pageTableEntries[pageNumber].isValid = 1;
                pt.pageTableEntries[oldestFrame].isValid = 0;
                pt.pageTableEntries[pageNumber].frameP = oldestFrame;
                oldestFrame++;
                if(oldestFrame > pageNumber) { oldestFrame = 0; }
                return;
            }
            for (int j = 0; j < frameCount; j++) {
                if (!freeFrames[j]) {
                    printf("Page #%d paged in\n", pageNumber);
                    freeFrames[j] = 1; // nu full
                    pt.pageTableEntries[pageNumber].isValid = 1;
                    pt.pageTableEntries[pageNumber].frameP = j;
                    statistics.pageFaults++;
                    return;
                }
            }
        } else {
            printf("Address %04x is on page %d which is already in physical memory\n", addr, pageNumber);
            statistics.pageHits++;
            return;
        }
    }
}

void optimal(unsigned int addr, unsigned int pageNumber) {
    for(int i = 0; i < frameCount; i++) {
        if(!pt.pageTableEntries[pageNumber].isValid) {
            printf("Address %04x not in physical memory\n", addr);
            if(isMemFull()) {
                for (int k = 0; k < AVAIL_MEM/FRAME_SIZE; k++) {
                    if (pt.pageTableEntries[k].isValid) {
                        for (int j = statistics.memoryAccesses; j < traces2.length; j++) {
                            if (k == (traces2.address[j] / FRAME_SIZE)) {
                                pt.pageTableEntries[k].nextArrival = j;
                                break;
                            }
                        }
                    }
                }
                int nextArrivalVal = -1, nextArrivalPos = 0;
                for (int j = 0; j < (AVAIL_MEM/FRAME_SIZE); j++) {
                    if (pt.pageTableEntries[j].nextArrival == 0 && pt.pageTableEntries[j].isValid){
                        nextArrivalPos = j;
                        break;
                    }
                    if((pt.pageTableEntries[j].nextArrival > nextArrivalVal) && pt.pageTableEntries[j].isValid) {
                        nextArrivalVal = pt.pageTableEntries[j].nextArrival;
                        nextArrivalPos = j;
                    }
                }
                // printf("\n");
                // for (int j = 0; j < 256; j++) {
                //     if (pt.pageTableEntries[j].isValid)
                //         printf("Next arrival: %d\n", pt.pageTableEntries[j].nextArrival);
                // }
                // printf("BIGGEST: %d\n", nextArrivalVal);

                printf("Page #%d paged out\n", nextArrivalPos);
                printf("Page #%d paged in\n", pageNumber);
                statistics.pageReplacements++;
                statistics.pageFaults++;
                pt.pageTableEntries[pageNumber].isValid = 1;
                pt.pageTableEntries[nextArrivalPos].isValid = 0;
                pt.pageTableEntries[pageNumber].frameP = nextArrivalPos;
                return;
            }
            for (int j = 0; j < frameCount; j++) {
                if (!freeFrames[j]) {
                    printf("Page #%d paged in\n", pageNumber);
                    freeFrames[j] = 1; // nu full
                    pt.pageTableEntries[pageNumber].isValid = 1;
                    pt.pageTableEntries[pageNumber].frameP = j;
                    statistics.pageFaults++;
                    return;
                }
            }
        } else {
            printf("Address %04x is on page %d which is already in physical memory\n", addr, pageNumber);
            statistics.pageHits++;
            return;
        }
    }
}

void lru(unsigned int addr, unsigned int pageNumber) {
    for(int i = 0; i < frameCount; i++) {
        if (!pt.pageTableEntries[pageNumber].isValid) {
            printf("Address %04x not in physical memory\n", addr);
            if(isMemFull()) {
                int leastUsedEntryVal = INT_MAX;
                int leastUsedEntryPos = 0;
                for (int j = 0; j < AVAIL_MEM/FRAME_SIZE; j++) {
                    if((pt.pageTableEntries[j].amountUsed < leastUsedEntryVal) && pt.pageTableEntries[j].isValid) {
                        leastUsedEntryVal = pt.pageTableEntries[j].amountUsed;
                        leastUsedEntryPos = j;
                    }
                }

                printf("Page #%d paged out\n", leastUsedEntryPos);
                printf("Page #%d paged in\n", pageNumber);
                statistics.pageReplacements++;
                statistics.pageFaults++;
                pt.pageTableEntries[pageNumber].isValid = 1;
                pt.pageTableEntries[leastUsedEntryPos].isValid = 0;
                pt.pageTableEntries[leastUsedEntryPos].amountUsed = 0;
                pt.pageTableEntries[pageNumber].frameP = leastUsedEntryPos;
                pt.pageTableEntries[pageNumber].amountUsed++;
                return;
            }
            for (int j = 0; j < frameCount; j++) {
                if (!freeFrames[j]) {
                    printf("Page #%d paged in\n", pageNumber);
                    freeFrames[j] = 1; // nu full
                    pt.pageTableEntries[pageNumber].isValid = 1;
                    pt.pageTableEntries[pageNumber].frameP = j;
                    statistics.pageFaults++;
                    return;
                }
            }
        } else {
            printf("Address %04x is on page %d which is already in physical memory\n", addr, pageNumber);
            statistics.pageHits++;
            pt.pageTableEntries[pageNumber].amountUsed++;
            return;
        }
    }
}

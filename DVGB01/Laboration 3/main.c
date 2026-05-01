#include "main.h"
#include "file.h"
#include "vm.h"

void handleArguments(int argc, char *argv[]);
void finalPrint(trace*);

char *filename;
int algorithm = -1; // FIFO = 0, Optimal = 1, LRU = 2
int frameCount;

int main(int argc, char *argv[]) {
    printf("\n+--VMSIM--\\---Laboration 3---\\------+\n");
    handleArguments(argc, argv);
    trace traces = loadTraces(filename);

    vmInit(algorithm, frameCount, traces);

    for(int i = 0; i < traces.length; i++)
        vmAccess(traces.address[i]);

    finalPrint(&traces);
    return 0;
}


void handleArguments(int argc, char *argv[]) {
    if(argc < 7 || argc % 2 == 0) {
        printf("You're missing arguments. Usage: `%s -f <trace file> -a <fifo | optimal | lru> -n <number of frames>`\n", argv[0]);
        exit(1);
    }

    for(int i = 0; i < argc; i++) {
        if(strcmp("-f", argv[i]) == 0) {
            filename = argv[i + 1]; // filename follows -f argument
            printf("\nProcess information file: %s\n", filename);
        } else if(strcmp("-a", argv[i]) == 0) {
            if (strcmp("FIFO", argv[i + 1]) == 0) {
                printf("Page replacement algorithm: FIFO\n");
                algorithm = 0;
            } else if (strcmp("OPT", argv[i + 1]) == 0) {
                printf("Page replacement algorithm: Optimal\n");
                algorithm = 1;
            } else if (strcmp("LRU", argv[i + 1]) == 0) {
                printf("Page replacement algorithm: LRU\n");
                algorithm = 2;
            } else {
                printf("Algorithm doesn't exist. Usage: `-a <fifo | optimal | lru>`.\n");
                exit(1);
            }
        } else if(strcmp("-n", argv[i]) == 0) {
            frameCount = atoi(argv[i + 1]);
            if(frameCount < 1) { printf("Number of frames cannot be less than 1.\n"); exit(1); }
        }
    }
    if(algorithm == -1) {
        printf("You've not selected an algorithm. Usage: `-a <fifo | optimal | lru>`.\n");
        exit(1);
    }
}

void finalPrint(trace *traces) {
    stats stats = getStatistics();
    char algorithmStr[8];
    switch(algorithm) {
        case 0: strncpy(algorithmStr, "FIFO", 5); break;
        case 1: strncpy(algorithmStr, "Optimal", 8); break;
        case 2: strncpy(algorithmStr, "LRU", 4); break;
        default: printf("Okänd Algorithm!\n"); break;
    }
    printf("\n%sSimulation Summary%s\n", BOLD_TEXT, RESET_TEXT);
    printf("Algorithm:\t\t%s\n", algorithmStr);
    printf("Frames:\t\t\t%d\n", frameCount);
    printf("Memory accesses:\t%d\n", stats.memoryAccesses);
    printf("Page hits:\t\t%d\t\n", stats.pageHits);
    printf("Page faults:\t\t%d\n", stats.pageFaults);
    printf("Page replacements:\t%d\n", stats.pageReplacements);
}

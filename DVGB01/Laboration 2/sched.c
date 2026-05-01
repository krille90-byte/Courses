#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) ((a)>(b) ? (a) : (b))


struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    char name;
};
struct Node {
    struct Process process;
    struct Node* next;
};
//Vår kö
struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct Process* array;
};

int compareArrivalTime(const void *a, const void *b) {
    return ((struct Process *)a)->arrivalTime - ((struct Process *)b)->arrivalTime;
}


int compareTurnaroundTime(const void *a, const void *b) {
    return ((struct Process *)a)->turnaroundTime - ((struct Process *)b)->turnaroundTime;
}

int comparePID(const void *a, const void *b) {
    return ((struct Process *)a)->pid - ((struct Process *)b)->pid;
}
int compareBurstTime(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
// Skapar en ny kö med angiven kapacitet
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (struct Process*)malloc(queue->capacity * sizeof(struct Process));
    return queue;
}

// Kontrollerar om vår kö är full
int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

// Kontrollerar om kön är tom
int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Lägger till en process i vår kö
void enqueue(struct Queue* queue, struct Process process) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = process;
    queue->size++;
}

// Ta bort en process från vår kö
struct Process dequeue(struct Queue* queue) {
    struct Process process;
    if (isEmpty(queue))
        return process;
    process = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return process;
}

void fcfs(struct Process processes[], int n) {
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    printf("FCFS:\n");
    printf("PID\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        if (processes[i].waitingTime < 0) {
            processes[i].waitingTime = 0;
        }
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        printf("%d\t%d\t\t%d\n", processes[i].pid, processes[i].waitingTime, processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;

        currentTime += processes[i].burstTime;
    }

    int avgWaitingTime = totalWaitingTime / n;
    int avgTurnaroundTime = totalTurnaroundTime / n;

    // Skriver ut avgWaitingTime och avgTurnaroundTime som heltal om det är jämnt annars inte.
    if (totalWaitingTime % n == 0) {
        printf("Average waiting time: %d ms\n", avgWaitingTime);
    } else {
        printf("Average waiting time: %.1f ms\n", (float)totalWaitingTime / n);
    }

    if (totalTurnaroundTime % n == 0) {
        printf("Average turnaround time: %d ms\n", avgTurnaroundTime);
    } else {
        printf("Average turnaround time: %.1f ms\n", (float)totalTurnaroundTime / n);
    }
}

void sjf(struct Process processes[], int n) {
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    printf("SJF:\n");
    printf("PID\tWaiting Time\tTurnaround Time\n");

    // Använder en separat array för att markera processer som redan körts.
    int *completed = (int *)malloc(n * sizeof(int));
    memset(completed, 0, n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int shortestIndex = -1;
        int shortestBurst = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!completed[j] && processes[j].arrivalTime <= currentTime && processes[j].burstTime < shortestBurst) {
                shortestIndex = j;
                shortestBurst = processes[j].burstTime;
            }
        }

        if (shortestIndex == -1) {
            // Inga processer är tillgängliga att köra, väntar in på nästa ankomst av element.
            currentTime++;
            // Försöker igen med samma tidsintervall
            i--;
        } else {
            // En process hittades att köra.
            processes[shortestIndex].waitingTime = currentTime - processes[shortestIndex].arrivalTime;
            if (processes[shortestIndex].waitingTime < 0) {
                processes[shortestIndex].waitingTime = 0;
            }
            processes[shortestIndex].turnaroundTime = processes[shortestIndex].waitingTime + processes[shortestIndex].burstTime;

            printf("%d\t%d\t\t%d\n", processes[shortestIndex].pid, processes[shortestIndex].waitingTime, processes[shortestIndex].turnaroundTime);

            totalWaitingTime += processes[shortestIndex].waitingTime;
            totalTurnaroundTime += processes[shortestIndex].turnaroundTime;

            currentTime += processes[shortestIndex].burstTime;
            // Markerar den som avslutad.
            completed[shortestIndex] = 1;
        }
    }

    int avgWaitingTime = totalWaitingTime / n;
    int avgTurnaroundTime = totalTurnaroundTime / n;

    // Skriver ut avgWaitingTime och avgTurnaroundTime som heltal om det är jämnt annars inte.
    if (totalWaitingTime % n == 0) {
        printf("Average waiting time: %d ms\n", avgWaitingTime);
    } else {
        printf("Average waiting time: %.1f ms\n", (float)totalWaitingTime / n);
    }

    if (totalTurnaroundTime % n == 0) {
        printf("Average turnaround time: %d ms\n", avgTurnaroundTime);
    } else {
        printf("Average turnaround time: %.1f ms\n", (float)totalTurnaroundTime / n);
    }

    free(completed);
}




void rr(struct Process processes[], int n, int timeQuantum) {
    
    int remainingBurstTime[n];
    int waitingTime[n];
    int turnaroundTime[n];
    int completed = 0;
    int CT[n];
    
    char processNames[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int currentProcess = 0;

    for(int i = 0; i < n; i++){
        processes[i].name = processNames[i];
    }

    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
        waitingTime[i] = 0;
        turnaroundTime[i] = 0;
    }
    qsort(processes, n, sizeof(struct Process), compareArrivalTime);
    printf("RR (Time quantum = %d):\n", timeQuantum);
    printf("Time\tPID\tName\tWaiting Time\tTurnaround Time\n");

    struct Queue* queue = createQueue(n);

    int currentTime = processes[0].arrivalTime;

    while (completed < n) {
        // Lägg till processer som har anlänt vid den aktuella tiden i kön
        while (currentProcess < n && processes[currentProcess].arrivalTime <= currentTime) {
            enqueue(queue, processes[currentProcess]);
            currentProcess++;
        }

        // Om kön är tom, hoppa fram till nästa process-arrivalTime
        if (isEmpty(queue)) {
            currentTime++;
            
        }
        else if(!isEmpty(queue)){

        // Tar bort en process från kön
        struct Process current = dequeue(queue);

        // TimeQuantum loopen
        for (int i = 0; i < timeQuantum; i++) {
            remainingBurstTime[current.pid - 1000]--;
            currentTime++;

            printf("%d\t%d\t%c\t\t\t\n", currentTime, current.pid, current.name);
            
            //Lägger till processer i vår kö.
            while (currentProcess < n && processes[currentProcess].arrivalTime <= currentTime) {
            enqueue(queue, processes[currentProcess]);
            currentProcess++;
        }
            // Kontrollerar om processen har slutförts eller inte.
        if (remainingBurstTime[current.pid - 1000] == 0) {
            completed++;
            CT[current.pid - 1000] = currentTime;
             processes[current.pid - 1000].completionTime = currentTime;
            

            // Uppdatera turnaroundTime och waitingTime här
            turnaroundTime[current.pid - 1000] = CT[current.pid - 1000] - processes[current.pid - 1000].arrivalTime;
            waitingTime[current.pid - 1000] = turnaroundTime[current.pid - 1000] - processes[current.pid - 1000].burstTime;
            
            break;
        } else if (remainingBurstTime[current.pid - 1000] != 0 && i == timeQuantum - 1) {
            // Processen är inte klar än, sätter tillbaka den i vår kö.
            enqueue(queue, current);
        }

            
        }
        }
        
    }
    
    qsort(processes, n, sizeof(struct Process), comparePID);
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    printf("\nResultat:\n");
    // Räknar ut total väntetid och turnaround-tid här.
    int otherW[n];
    int otherT[n];
    for(int i = 0; i < n; i++){
        otherT[i] = CT[i] - processes[i].arrivalTime;
        otherW[i] = otherT[i] - processes[i].burstTime;
    }
    /*for(int i = 0; i < n; i++){
    printf("%d\t%d\t%c\t%d\t\t%d\n",CT[i], processes[i].pid, processes[i].name, otherW[i], otherT[i]);
    }*/
    
    printf("\nTime\tPID\tName\tTurnaround Time\tWaiting Time\n");
    for(int i = 0; i < n; i++){
        processes[i].completionTime = CT[i];
        processes[i].turnaroundTime = CT[i] - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
    qsort(processes, n, sizeof(struct Process), comparePID);
    for(int i = 0; i < n; i++){
    printf("%d\t%d\t%c\t%d\t\t%d\n",processes[i].completionTime, processes[i].pid, processes[i].name, processes[i].turnaroundTime, processes[i].waitingTime);
    }
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    int avgWaitingTime = totalWaitingTime / n;
    int avgTurnaroundTime = totalTurnaroundTime / n;

    // Skriver ut avgWaitingTime och avgTurnaroundTime som heltal om det är jämnt annars inte.
    if (totalWaitingTime % n == 0) {
        printf("Average waiting time: %d ms\n", avgWaitingTime);
    } else {
        printf("Average waiting time: %.1f ms\n", (float)totalWaitingTime / n);
    }

    if (totalTurnaroundTime % n == 0) {
        printf("Average turnaround time: %d ms\n", avgTurnaroundTime);
    } else {
        printf("Average turnaround time: %.1f ms\n", (float)totalTurnaroundTime / n);
    }

    free(queue->array);
    free(queue);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Användning: %s -f <filnamn> -a [FCFS | SJF | RR] [tidskvantum]\n", argv[0]);
        return 1;
    }

    char *filename = NULL;
    char *algorithm = NULL;
    int timeQuantum = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            filename = argv[i + 1];
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            algorithm = argv[i + 1];
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            timeQuantum = atoi(argv[i + 1]);
        }
    }

    if (filename == NULL || algorithm == NULL) {
        printf("Felaktigt användningsfall. Användning: %s -f <filnamn> -a [FCFS | SJF | RR] [tidskvantum]\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Kunde inte öppna filen: %s\n", filename);
        return 1;
    }

    int n = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        n++;
    }

    rewind(file);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
    if (processes == NULL) {
        printf("Minnesallokering misslyckades.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d,%d,%d", &processes[i].pid, &processes[i].arrivalTime, &processes[i].burstTime) != 3) {
            printf("Felaktigt format i filen: %s\n", filename);
            fclose(file);
            free(processes);
            return 1;
        }
    }

    fclose(file);

    if (strcmp(algorithm, "FCFS") == 0) {
        qsort(processes, n, sizeof(struct Process), compareArrivalTime);
        fcfs(processes, n);
    } else if (strcmp(algorithm, "SJF") == 0) {
        sjf(processes, n);
    } else if (strcmp(algorithm, "RR") == 0) {
        if (timeQuantum == -1) {
            timeQuantum = 1;
        }
       // qsort(processes, n, sizeof(struct Process), compareArrivalTime);
        rr(processes, n, timeQuantum);
    } else {
        printf("Okänd schemaläggningsalgorihtm: %s\n", algorithm);
    }

    free(processes);

    return 0;
}
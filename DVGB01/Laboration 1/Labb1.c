#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int N;             //Antal konsumenter
int tid;           //Tidsintervallet
int* buffern;      //Buffert för att dela data mellan producent och konsumenter
int BufferSize;    //Storlek på bufferten
sem_t mutex, empty, full;  //Semaforer för trådsynkronisering
pthread_t producent_thread;  //Tråd för producenten
pthread_t* konsument_thread; //Array av trådar för konsumenterna

// Producentfunktion
void* producer() {
    do {
        srand(time(NULL));
        int item = (rand() % 100) + 1;
        sleep(tid);

        sem_wait(&empty);  //Vänta om bufferten är tom innan produktion
        sem_wait(&mutex);  //Lås buffern för att säkerställa exklusiv åtkomst

        //Placerar det slumpmässiga elementet i bufferten
        for (int i = 0; i < BufferSize; i++) {
            if (buffern[i] == -1) { //Hitta en tom plats i bufferten
                buffern[i] = item;
                break;
            }
        }

        sem_post(&mutex);  //Släpp buffern så att andra trådar kan komma åt den
        sem_post(&full);   //Signalerar att bufferten är full nu

    } while (1);
}

// Konsumentfunktion
void* consumer(void* arg) {
    int konsument_id = *((int*)arg);

    do {
        sem_wait(&full);  //Vänta om bufferten är tom innan konsumtion
        sem_wait(&mutex); //Lås buffern för att säkerställa exklusiv åtkomst

        int item = -1;

        // Ta ett element från bufferten
        for (int i = 0; i < BufferSize; i++) {
            if (buffern[i] != -1) { // Hitta ett element i bufferten
                item = buffern[i];
                buffern[i] = -1; // Markerar elementet som tomt
                break;
            }
        }

        sem_post(&mutex); //Släpp buffern
        sem_post(&empty); //Signalera att det finns en tom plats i bufferten nu

        printf("Konsument nummer:[%d] - konsumerade tal: %d\n", konsument_id, item);

    } while (1);
}

//Funktionen för att hantera SIGINT-signalen (CTRL+C)
void signalHanteraren() {
    //Avbryter producenttråden för att avsluta produktionen
    pthread_cancel(producent_thread);

    //Avbryter alla konsumenttrådar för att avsluta konsumtionen
    for (int i = 0; i < N; i++) {
        pthread_cancel(konsument_thread[i]);
    }

    //Skriver ut avslutningsmeddelande 
    printf("\nProgrammet avslutas... CTRL+C tryckt! [^C] \n");

    //Städar upp och frigör resurser
    free(konsument_thread); //Frigör minnet som används för konsumenttrådarna
    free(buffern); //Frigör minnet som används för bufferten
    sem_destroy(&mutex); //Förstör mutex-semaforen
    sem_destroy(&empty); //Förstör semaforen för tomma platser i bufferten
    sem_destroy(&full); //Förstör semaforen för fulla platser i bufferten

    exit(0); //Avslutar programmet
}

int main() {
    printf("Ange antalet konsumenter: ");
    scanf("%d", &N);
    printf("Ange storlek på bufferten: ");
    scanf("%d", &BufferSize);
    printf("Ange tidsintervall (Sek): ");
    scanf("%d", &tid);

    konsument_thread = (pthread_t*)malloc(N * sizeof(pthread_t));
    buffern = (int*)malloc(BufferSize * sizeof(int));

    //Initierar bufferten
    for (int i = 0; i < BufferSize; i++) {
        buffern[i] = -1; // Markera alla platser som tomma
    }

    //Initierar semaforer
    sem_init(&mutex, 0, 1); // Mutex initialiseras till 1 (upplåst)
    sem_init(&empty, 0, BufferSize); // Antal tomma platser i bufferten
    sem_init(&full, 0, 0); // Antal fulla platser i bufferten

    //Skapar producenttråden
    pthread_create(&producent_thread, NULL, producer, NULL);

    //Skapa konsumenttrådarna
    for (int i = 0; i < N; i++) {
        int* konsument_idMain = malloc(sizeof(int));
        *konsument_idMain = i;
        pthread_create(&konsument_thread[i], NULL, consumer, konsument_idMain);
    }

    //signalhanteraren för SIGINT (CTRL+C)
    signal(SIGINT, signalHanteraren);

    //Väntar på att producent- och konsumenttrådarna ska avslutas
    pthread_join(producent_thread, NULL);

    for (int i = 0; i < N; i++) {
        pthread_join(konsument_thread[i], NULL);
    }

    //Städar upp och avslutar programmet
    free(konsument_thread);
    free(buffern);
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

/*
VAD ÄR MUTEX OCH SEMAFORER:

- Mutex:
En Mutex är en form av "mutual exclusion/ömsesidig uteslutning" och det är en princip och mekanism
som används här för att säkerställa att endast en tråd eller en process åt gången får en åtkomst åt
gången. Syftet till varför vi använder det är för att undvika datakonflikter och inkonsekvenser när
flera trådar försöker ändra på samma resurs samtidigt.

Men om vi ska sammanfatta det så säkerställer vi att när en tråd är inne i en kritisk sektion och
ändrar i en delad resurs så kommer ingen annan tråd att få åtkomst till den samtidigt. Och då undviker
vi konkurrenssituationer där flera trådar ändrar i datan samtidigt(Vilket skulle leda till felaktiga
resultat).

Sem_t "Mutex":
Detta är vårt lås för programmet och vi har ställt in den för att endast hantera en tråd åt gången med
"sem_init(&mutex, 0, 1)".

sem_wait(&mutex) Och sem_post(&mutex):
När en av våra trådar, procudenten eller våra konsumenter vill komma åt vår buffer så låser vi den med
"sem_wait(&mutex)". Om vi redan har låst den så är vårt värde här 0 och då kommer tråden att blockeras
tills en annan tråd släpper på låset genom att använda "sem_post(&mutex)". Tråden säkerställer
vår buffer och utför operationer på den delade resursen i de kritiska sektionerna, Vilket är då 
skyddat av vår mutex(vårt lås). sem_post(&mutex) ökar också vårt värde just nu till 1 och gör vår tråd
tillgänglig för andra trådar igen(för att ta del av vår buffer).

-----------------------------------------------------------------------------------------------------
- Empty:

Sem_t "Empty":
Detta kontrollerar och signalerar antalet tomma platser i vår buffer(BufferSize av platser).

sem_wait(&Empty):
När vår producent sätter in ett nytt tal i vår buffer så använder vi oss utav "sem_wait(&Empty)", det
är för att minska värdet av Empty med 1. Om Empty är 0 så kommer producenten blockeras tills någon
konsument har tagit bort(konsumerat) ett tal ur vår array och ökar värdet för Empty igen med 1.

sem_post(&Empty):
När en konsument har konsumerat ett av talen som producenten har producerat så använder vi oss utav
"sem_post(&Empty)" , detta ökar värdet av Empty med 1, vilket då kommer att signalera att det finns nu
ett tomt utrymme i vår buffer för att producera ett nytt tal.

SAMMANFATTNING:
Sem_t Empty är for att kolla och kontrollera, signalerna om det finns tomma platser i vår buffer 
och då säkerställa vår produktion av tal och att våra konsumenter inte ska gå utan att få sina tal
(Typ som mat).

-----------------------------------------------------------------------------------------------------
- Full:

Sem_t "Full":
Detta håller koll på antalet "Fulla" platser i vår buffer. Alltså, hur många platser i vår buffer som 
är fulla. I min main funktion så initierar jag värdet till att vara 0 för antal fulla platser 
"sem_init(&full, 0, 0)" , för vi har ju inga fulla platser för tillfället.

sem_post(&Full):
När till exempel en producent lägger till ett nytt tal i vår buffer så använder jag 
"sem_post(&Full)" för att öka värdet på "Full" med 1 för att signalera att det nu finns ett element i
vår buffer som väntar på att bli konsumerat av en konsument.

sem_wait(&Full):
När vår konsument har konsumerat vårt tal så tar vi bort den från vår buffer och då används
"sem_wait(&Full)" för att minska värdet med 1 för "Full". Vilket betyder att vi nu kan producera ett
nytt tal för våra konsumenter igen.

SAMMANFATTNING:
Med "Full" så avgör vi när vår buffer är helt enkelt full eller inte. Med sem_wait(&Full) så minskar vi
värdet av "Full" med ett och klargör för producenten att det finns utrymme för att vi producera ett nytt
tal för våra konsumenter. Med sem_post(&Full) så ökar vi "Full" med 1 för att klargöra att buffern är
full och det finns inte plats för att producera ett nytt tal tills våra konsumenter har konsumerat
produkten.



wait:
minskar värdet och är värdet redan 0 så blockeras tråden tills semaforen ökar igen.

post:
ökar värdet och om det finns någon tråd som väntar på semaforen så kommer den att bli upplåst och
fortsätta.

destroy:
Frigör helt enkelt våra resurser. Typ avallokerar våra semaforer.




*/
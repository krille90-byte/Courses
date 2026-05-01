Användning:

kompilering:
gcc -o sched sched.c

Hur vi använder programmet:

- flaggor: -f för fil, -a för algorithm, -q för Tidskvant.

Algorithmer:

__FCFS:

./program -f textFil -a FCFS

__SJF:

./program -f textFil -a SJF

__Round Robin:

./program -f textFil -a RR -q 2

// du knappar in tiden efter -q, behöver inte vara 2, kan vara vad som. 
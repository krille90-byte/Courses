Labb4.o: Labb4.c
	gcc -c Labb4.c

functions.o: functions.c functions.h
	gcc -c functions.c

fileManagement.o: fileManagement.c functions.h
	gcc -c fileManagement.c

KALLE: Labb4.o functions.o fileManagement.o
	gcc -o KALLE Labb4.o functions.o fileManagement.o

clean:
	-rm a.out functions.o KALLE Labb4.o
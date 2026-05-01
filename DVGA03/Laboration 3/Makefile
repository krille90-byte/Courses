# kompilatorvariabel
kompilator=gcc

main.o: main.c main.h
	$(kompilator) -c main.c

list.o: list.c list.h
	$(kompilator) -c list.c

functions.o: functions.c functions.h
	$(kompilator) -c functions.c

Labb3: main.o list.o functions.o
	$(kompilator) -o Labb3 main.o list.o functions.o

pre-clean:
	rm *.o Labb3

post-clean:
	rm *.o

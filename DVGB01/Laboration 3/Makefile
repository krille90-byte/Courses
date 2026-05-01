kompilator=gcc

Labb3: main.o file.o vm.o
	$(kompilator) -o Labb3 main.o file.o vm.o

main.o: main.c
	$(kompilator) -c main.c

file.o: file.c
	$(kompilator) -c file.c

vm.o: vm.c
	$(kompilator) -c vm.c

pre-clean:
	rm *.o Labb3

post-clean:
	rm *.o
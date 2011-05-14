Make: Make.o grafo.o
	gcc -Wall -ansi -pedantic -g Make.o grafo.o -o Make

Make.o: Make.c grafo.o
grafo.o: grafo.c grafo.h

.PHONY: clean
clean:
	rm *.o *~

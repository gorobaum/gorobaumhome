Make: Make.o grafo.o
	gcc -Wall -ansi -pedantic -g Make.o grafo.o -o Make

Make.o: Make.c grafo.o
	cc -c Make.c
grafo.o: grafo.c grafo.h
	cc -c grafo.c

clean:
	rm *.o *~

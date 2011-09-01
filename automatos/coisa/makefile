Make: auto.o grafo.o queue.o
	gcc -Wall -ansi -pedantic -g auto.o grafo.o queue.o -o auto

Make.o: auto.c grafo.o
	cc -c auto.c
grafo.o: queue.o grafo.c grafo.h
	cc -c grafo.c
queue.o: queue.c queue.h
	cc -c queue.c
clean:
	rm *.o *~

Make: tarefa5.o grafo.o queue.o
	gcc -Wall -ansi -pedantic -g tarefa5.o grafo.o queue.o -o tarefa5

Make.o: tarefa5.c grafo.o
	cc -c tarefa5.c
grafo.o: queue.o grafo.c grafo.h
	cc -c grafo.c
queue.o: queue.c queue.h
	cc -c queue.c
clean:
	rm *.o *~

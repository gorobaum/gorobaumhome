Make: tarefa5.o grafo.o
	gcc -Wall -ansi -pedantic -g tarefa5.o grafo.o -o tarefa5

Make.o: tarefa5.c grafo.o
	cc -c tarefa5.c
grafo.o: grafo.c grafo.h
	cc -c grafo.c

clean:
	rm *.o *~

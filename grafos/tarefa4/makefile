CFLAGS = -Wall -ansi -pedantic -g
OBJECTS = Make.o grafo.o

CC = gcc

Make: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o Make

Make.o: Make.c grafo.o
grafo.o: grafo.c grafo.h

.PHONY: clean
clean:
	rm *.o *~

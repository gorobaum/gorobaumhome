CFLAGS = -Wall -ansi -pedantic -g -lm
OBJECTS = main.o grafo.o hash.o

CC = gcc

Make: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o ep3

grafo.o: grafo.c grafo.h hash.h
Make.o: Make.c grafo.h
hash.o: hash.c hash.h

.PHONY: clean
clean:
	rm *.o *~

CFLAGS = -Wall -ansi -pedantic -g -lm
OBJECTS = main.o compress.o trie.o

CC = gcc

EP3: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o ep3

compress.o: compress.c compress.h trie.h
main.o: main.c compress.h
trie.o: trie.c trie.h

.PHONY: clean
clean:
	rm *.o *~

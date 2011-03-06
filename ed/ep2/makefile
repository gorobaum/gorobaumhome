CFLAGS = -Wall -ansi -pedantic
OBJECTS = main.o BST.o LL.o Interface.o RPN.o

CC = gcc

EP2: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o EP2

BST.o : BST.c BST.h LL.c LL.h
Interface.o: BST.h BST.c LL.c LL.h RPN.c RPN.h Interface.c Interface.h
LL.o: LL.c LL.h
main.o: main.c BST.h BST.c LL.c LL.h RPN.c RPN.h Interface.c Interface.h
RPN.o: RPN.c RPN.h LL.c LL.h BST.c BST.h

.PHONY: clean
clean:
	rm *.o *~

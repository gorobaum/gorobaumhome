#include <stdio.h>
#include <stdlib.h>
#include "ITEM.h"
#include "STACK.h"

typedef Cell* Link;

struct Cell {
	int item;
	Link Next;
}

struct stack {
	Link Next;
	Link Top;
	int Tam;
}

void STACKdump(Stack s) {
	Link c;
	if ( STACKempty(s) ) printf("A pilha estã vazia.");
	else {
		c = s->Next;
		while ( !c.Next ) { 
			ITEMprintf(c.item);
			c = c.Next;
		}
	}
}

int STACKempty(Stack s) {
	return (s->Top == NULL);
}

void STACKput(Stack s, Item item) {
	Link cell, c;
	
	cell = malloc(sizeof(Cell));
	cell->item = item;
	cell->Next = NULL;
	
	c = s->Next;
	while ( !c->Next ) { 
		c = c->Next;
	}
	c->Next = cell;
	s->Top = cell;
	(s->Tam)++;
}
	
Item STACKget(Stack s) {
	Item item;
	Link c, bef;
	
	c = s->Next;
	bef = NULL;
	while ( !c->Next ) {
		bef = c; 
		c = c->Next;
	}
	item = c->item;
	bef->Next = NULL;
	s->Top = bef;
	(s->Tam)--;
	free(c);
	return item;
}

Stack* STACKinit(int n) {
	Stack *s;
	int i;
	s = malloc(n*sizeof(stack));
	for ( i = 0; i < n; i+ ) {
		s[i].Next = NULL;
		s[i].TOP = NULL;
		s[i].Tam = 0;
	}
	return s;
}

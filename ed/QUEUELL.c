#include <stdio.h>
#include <stdlib.h>
#include "QUEUE.h"
#include "ITEM.h"

typedef queue* Link;

struct queue {
	Item item;
	Link *prox;
}Cell;

typedef struct head {
	Link *prox;
	int TAM;
}Head;

void QUEUEdump(Link q) {
	if ( QUEUEempty(q) ) {
		printf("A lista estã vazia!");
	}
	else {
		while(!QUEUEempty(q)) {
			ITEMprintf(q->item);
			q = q->prox;
		}
	}
}

Link QUEUEinit(int maxN) {
	Head head = malloc(sizeof(head));
	if ( head == NULL ) return 0;
	else {
		head->prox = NULL;
		head->TAM = 0;
		return head;
}

int QUEUEempty(Link q) {
	return q->prox == NULL;
}

void QUEUEput(Link q, Item item, int *TAM) {
	Cell *cell = malloc(sizeof(Cell));
	if ( cell == NULL ) {
		printf("Nao ha memoria o sulficiente!");
	}
	else {
		cell->item = item;
		cell->prox = NULL;
		(*TAM)++;
		while(!QUEUEempty(q)) {
			q = q->prox;
		}
		q->prox = cell;
	}
}

Item QUEUEget(Link q, int *TAM) {
	Item item = -1;
	Link cell;
	if ( QUEUEempty(q) ) {
		printf("A lista estã vazia!");
	}
	else{
		item = q->item;
		cell = q->prox;
		q->prox = cell->prox;
		(*TAM)--;
		free(cell);
	}
	return item;
}

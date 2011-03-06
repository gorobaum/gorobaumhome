#include <stdio.h>
#include <stdlib.h>
#include "ITEM.h"
#include "STACKLL.c"

#define MAX_C 48
#define NUM_CPN 12
#define NUM_N 4

typedef stack Pilha;

int* GenDeck() {
	int *Deck, i;
	Deck = malloc(MAX_C*sizeof(int));
	if ( Deck == NULL ) { 
		printf("O Deck nao pode ser gerado. \n");
		exit(0);
	}
	for ( i = 0; i <MAX_C; i++ ) Deck[i] = i;
	return Deck;
}

int main() {
	Pilha *Cartas, *Nipes, Head;
	int *Deck = GenDeck, i;
	
	Cartas = STACKinit( MAX_CPN );
	Nipes = STACKinit( MAX_N );
	
	for ( i = 0; i < MAX_CPN; i++ ) { 
		STACKdump(Pilha[i]);
	}
	for ( i = 0; i < MAX_N; i++ ) {
		STACKdump(Nipes[i]);
	}
	
	return 0;
}

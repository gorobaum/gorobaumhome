#include <stdio.h>
#include <stdlib.h>

#define MAX 7

typedef struct {
		int x;
		int y;
		} posicao;
		
typedef struct {
		posicao pos;
		int mov;
		} item;		

static int tab[7][7] = {
	  {0,0,1,1,1,0,0},
		{0,0,1,1,1,0,0},
		{1,1,1,1,1,1,1},
		{1,1,1,2,1,1,1},
		{1,1,1,1,1,1,1},
		{0,0,1,1,1,0,0},
		{0,0,1,1,1,0,0} };

void desenha() {
	int j, k;
	printf("\n");
	for ( j = 0; j < MAX; j++ ) {
		for ( k = 0; k < MAX; k++ ) {
			if ( tab[j][k] == 0 ) printf(" ");
			else if ( tab[j][k] == 1 ) printf("*");
			if ( tab[j][k] == 2 ) printf("O");
			printf(" ");
		}
		printf("\n");
	}
}

int podemov( posicao * atual, int mov )
{
	posicao aux;
	switch (mov) {
		case 1:
		aux.x = atual->x - 2;
		aux.y = atual->y;
		if ( (aux.x >= 0) && (tab[aux.x][aux.y] == 1 && tab[++aux.x][aux.y] == 1) ) return 1;
		break; 
		case 2:
		aux.x = atual->x;
		aux.y = atual->y + 2;
		if ( (aux.y < 7) && (tab[aux.x][aux.y] == 1 && tab[aux.x][--aux.y] == 1) ) return 1;
		break;
		case 3:
		aux.x = atual->x + 2;
		aux.y = atual->y;
		if ( (aux.x < 7) && (tab[aux.x][aux.y] == 1 && tab[--aux.x][aux.y] == 1) ) return 1;
		break;
		case 4:
		aux.x = atual->x;
		aux.y = atual->y - 2;
		if ( (aux.y >= 0) && (tab[aux.x][aux.y] == 1 && tab[aux.x][++aux.y] == 1) ) return 1;
		break;
	}
	return 0;
}

void atualizatab( item local , posicao * atual )
{
 	switch (local.mov) {
 		case 1:
 		tab[local.pos.x - 2][local.pos.y] = 2;
 		tab[local.pos.x - 1][local.pos.y] = 2;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).x = (*atual).x - 2;
 		break;
 		case 2:
 		tab[local.pos.x][local.pos.y + 2] = 2;
 		tab[local.pos.x][local.pos.y + 1] = 2;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).y = (*atual).y + 2;
 		break;
 		case 3:
 		tab[local.pos.x + 2][local.pos.y] = 2;
 		tab[local.pos.x + 1][local.pos.y] = 2;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).x = (*atual).x + 2;
 		break;
 		case 4:
 		tab[local.pos.x][local.pos.y - 2] = 2;
 		tab[local.pos.x][local.pos.y - 1] = 2;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).y = (*atual).y - 2;
 		break;
 	}
}

void desatualizatab ( item local )
{
	switch (local.mov) {
 		case 1:
 		tab[local.pos.x][local.pos.y] = 1;
 		tab[local.pos.x + 1][local.pos.y] = 1;
 		tab[local.pos.x + 2][local.pos.y] = 2;
 		break;
 		case 2:
 		tab[local.pos.x][local.pos.y] = 1;
 		tab[local.pos.x][local.pos.y - 1] = 1;
 		tab[local.pos.x][local.pos.y - 2] = 2;
 		break;
 		case 3:
 		tab[local.pos.x][local.pos.y] = 1;
 		tab[local.pos.x - 1][local.pos.y] = 1;
 		tab[local.pos.x - 2][local.pos.y] = 2;
 		break;
 		case 4:
 		tab[local.pos.x][local.pos.y] = 1;
 		tab[local.pos.x][local.pos.y + 1] = 1;
 		tab[local.pos.x][local.pos.y + 2] = 2;
 		break;
 	}
}

posicao procura( posicao atual, int x, int y )
{
	posicao aux;
	aux = atual;
	printf("Procurando uma posicao... \n");
	printf(" %d %d -> FOR 0 \n", x, y);
		for ( ; y < MAX ; y++ ) {
			printf(" %d %d -> FOR 2 \n", x, y);
			if ( tab[x][y] == 2 && x != aux.x && y != aux.y ) {
				aux.x = x;
				aux.y = y;
				return aux;
			}	
		}
	x++;
	for ( ; x < MAX; x++) {
		printf(" %d %d -> FOR 1 \n", x, y);
		for ( y = 0 ; y < MAX ; y++ ) {
			printf(" %d %d -> FOR 2 \n", x, y);
			if ( tab[x][y] == 2 && x != aux.x && y != aux.y ) {
				aux.x = x;
				aux.y = y;
				return aux;
			}	
		}
	}
}

void empilha( item pilha[], int *topo, item local )
{
	pilha[*topo] = local;
	*topo = *topo + 1;
}

void desempilha( int *topo )
{
	(*topo)--;
}

item topodapilha(item pilha[], int topo)
{
	return pilha[topo-1];
}

void resolve()
{
	int mov, topo, passos, x, y;
	item aux;
	posicao atual;
	item pilha[32];
	topo = 0; passos = 1; mov = 1;
	atual.x = 3; atual.y = 3;
	while ( passos < 32 ) {
		while ( mov <= 4 ) {
			printf("X = %d Y = %d \n", atual.x, atual.y );
			desenha();
			printf("podemov = %d \nmov = %d \n", podemov( &atual, mov ), mov );
			if ( podemov( &atual, mov ) ) {
				getchar();
				printf("Testando uma posicao... \n");
			  aux.pos.x = atual.x;
				aux.pos.y = atual.y;
				aux.mov = mov;
				atualizatab( aux , &atual );
				printf("Empilhando uma posicao... \n");
	  		empilha( pilha, &topo, aux );
	  		x = 0; y = 0;
	  		passos++;
	  		mov = 1;
			  break;
			}
			else mov++;
		}
	 	if ( ( x != 6 ) && ( y != 6 ) && ( mov == 5 ) ) {
	 		printf(" %d %d -> FOR -1 \n", x, y);
			atual = procura( atual, x, y );
			mov = 1;
			getchar();
		}
		else if ( (x == 6) && (y == 6) && (mov == 5) ) {
			if ( topo == 0 ) printf("Sem Solucao. /n");
			else {
				aux = topodapilha( pilha, topo );
				desatualizatab( aux );
				atual.x = aux.pos.x; atual.y = aux.pos.y;
				x = aux.pos.x; y = aux.pos.y;
				mov = aux.mov + 1;
				passos--;
				printf("Desempilhando uma posicao... \n");
				getchar();
				desempilha( &topo );
			}
		} 
	}
	desenha();
} 	
		
int main()
{
	desenha();
	resolve();
	return 0;
}

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
			}item;		

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

int achaoutro(int x, int y)
{
	if ( tab[x][y] == 2 ) return 1;
	return 0;
}

void empilha( item pilha[], int *topo, item local )
{
	pilha[*topo] = local;
	*topo = *topo + 1;
}

void desempilha( int *topo )
{
	*topo = *topo - 1;
}

item topodapilha(item pilha[], int topo)
{
	return pilha[topo-1];
}

void resolve()
{
	int mov, topo, passos, x,y;
	item local, aux;
	posicao atual;
	item pilha[32];
	
	topo = 0; passos = 1; x = 0, y = 0, mov = 1;
	atual.x = 3; atual.y = 3;
	local.pos.x = 0; local.pos.y = 0; local.mov = 1;
	
	while ( passos < 32 ) {
		while ( mov <= 4 ) {
			desenha();
			printf(" %d ", podemov( atual, mov ) );
			if ( podemov( &atual, mov ) ) {
			 printf("Testando uma posicao... \n ");			
			 break;
			} 
			else mov++;
		}
		if ( mov < 5 ) {
		local.pos.x = atual.x;
		local.pos.y = atual.y;
		local.mov = mov;
		printf("Empilhando uma posicao... \n");
	  empilha( pilha, &topo, local );
	  x = 0; y = 0;
	  passos++;
	  mov = 1;
	  }
		else if ( mov == 5 ) {
			printf("Procurando uma posicao... \n");
			for ( ; x < MAX, x++ ) {
				for ( ; y < MAX, y++ ) {
					if ( achaoutro( x, y ) ) {
						atual.x = x;
						atual.y = y;
						break;
					}	
				}
			}
		}	
		if ( x == 6 && y == 6 && mov == 5 ) {
			if ( topo == 0 ) printf("Sem Solucao. /n");
			else {
				aux = topodapilha( pilha, topo );
				atual.x = aux.pos.x;
				atual.y = aux.pos.y;
				mov = aux.mov + 1;
				passos--;
				printf("Desempilhando uma posicao... \n");
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

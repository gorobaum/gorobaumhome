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
		{-1,-1,0 ,0 ,0 ,-1,-1},
		{-1,-1,0 ,1 ,0 ,-1,-1},
		{0 ,0 ,0 ,1 ,0 ,0 ,0 },
		{0 ,1 ,1 ,1 ,1 ,1 ,0 },
		{0 ,0 ,0 ,1 ,0 ,0 ,0 },
		{-1,-1,0 ,1 ,0 ,-1,-1},
		{-1,-1,0 ,0 ,0 ,-1,-1} };

void desenha() {
	int j, k;
	printf("\n");
	for ( j = 0; j < MAX; j++ ) {
		for ( k = 0; k < MAX; k++ ) {
			if ( tab[j][k] == -1 ) printf(" ");
			else if ( tab[j][k] == 1 ) printf("*");
			if ( tab[j][k] == 0 ) printf("O");
			printf(" ");
		}
		printf("\n");
	}
}

int podemov( item atual )
{
	posicao aux;
	switch (atual.mov) {
		case 1:
		aux.x = atual.pos.x;
		aux.y = atual.pos.y + 2;
		if ( (aux.y < 7) && (tab[aux.x][aux.y] == 1 && tab[aux.x][--aux.y] == 1) ) return 1;
		break;
		case 2:
		aux.x = atual.pos.x + 2;
		aux.y = atual.pos.y;
		if ( (aux.x < 7) && (tab[aux.x][aux.y] == 1 && tab[--aux.x][aux.y] == 1) ) return 1;
		break;
		case 3:
		aux.x = atual.pos.x;
		aux.y = atual.pos.y - 2;
		if ( (aux.y >= 0) && (tab[aux.x][aux.y] == 1 && tab[aux.x][++aux.y] == 1) ) return 1;
		break;
		case 4:
		aux.x = atual.pos.x - 2;
		aux.y = atual.pos.y;
		if ( (aux.x >= 0) && (tab[aux.x][aux.y] == 1 && tab[++aux.x][aux.y] == 1) ) return 1;
		break; 
	}
	return 0;
}

void atualizatab( item local , item * atual )
{
 	switch (local.mov) {
 		case 1:
 		tab[local.pos.x][local.pos.y + 2] = 0;
 		tab[local.pos.x][local.pos.y + 1] = 0;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).pos.y = (*atual).pos.y + 2;
 		break;
 		case 2:
 		tab[local.pos.x + 2][local.pos.y] = 0;
 		tab[local.pos.x + 1][local.pos.y] = 0;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).pos.x = (*atual).pos.x + 2;
 		break;
 		case 3:
 		tab[local.pos.x][local.pos.y - 2] = 0;
 		tab[local.pos.x][local.pos.y - 1] = 0;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).pos.y = (*atual).pos.y - 2;
 		break;
 		case 4:
 		tab[local.pos.x - 2][local.pos.y] = 0;
 		tab[local.pos.x - 1][local.pos.y] = 0;
 		tab[local.pos.x][local.pos.y] = 1;
 		(*atual).pos.x = (*atual).pos.x - 2;
 		break;
 	}
}

void desatualizatab ( item local )
{
	switch (local.mov) {
 		case 1:
 		tab[local.pos.x][local.pos.y + 2] = 1;
 		tab[local.pos.x][local.pos.y + 1] = 1;
 		tab[local.pos.x][local.pos.y] = 0;
 		break;
 		case 2:
 		tab[local.pos.x + 2][local.pos.y] = 1;
 		tab[local.pos.x + 1][local.pos.y] = 1;
 		tab[local.pos.x][local.pos.y] = 0;
 		break;
 		case 3:
 		tab[local.pos.x][local.pos.y - 2] = 1;
 		tab[local.pos.x][local.pos.y - 1] = 1;
 		tab[local.pos.x][local.pos.y] = 0;
 		break;
 		case 4:
 		tab[local.pos.x - 2][local.pos.y] = 1;
 		tab[local.pos.x - 1][local.pos.y] = 1;
 		tab[local.pos.x][local.pos.y] = 0;
 		break;
 	}
}

item procura( item atual, int *x, int *y )
{
	int k, i;
	item aux;
	aux.mov = 1;
	k = *x;
	i = *y;
	i++;
	for( ; i < 7; i++ ) {
		if ( tab[k][i] == 0 ) {
			aux.pos.x = k;
			aux.pos.y = i;
			while ( aux.mov <= 4 ) {
				if ( podemov( aux ) ) { 
					*x = k;
					*y = i;
					return aux;
				}
				else aux.mov++;
			}
			aux.mov = 1;
		}
	}
	if ( k <= 5 ) k++;
	else k = 0;
	for( ; k < 7; k++ ) {
		for ( i = 0; i < 7; i++ ) {		
			if ( tab[k][i] == 0 ) {
				aux.pos.x = k;
				aux.pos.y = i;
				while ( aux.mov <= 4 ) {
					if ( podemov( aux ) ) { 
						*x = k;
						*y = i;
						return aux;
					}
					else aux.mov++;
				}
			}
			aux.mov = 1;
		}
	}
	*x = k;
	*y = i;
	aux.mov = 10;
	return aux;
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

void imprimesol( item pilha[], int topo )
{
	int x;
	item aux;
	for ( x = 0; x < topo; x++ ) {
		aux = pilha[x];
		printf("(%c , %d)", (aux.pos.y + 'A'), (aux.pos.x + 1) );
		switch( aux.mov) {
			case 1:
			printf("  Para a Direita.\n");
			break;
			case 2:
			printf("  Para Baixo.\n");
			break;
			case 3:
			printf("  Para a Esquerda.\n");
			break;
			case 4:
			printf("  Para cima.\n");
			break;
		}
	}
}

int ganhou()
{
	int i, k, soma;
	soma = 0;
	for( k = 0; k < MAX; k++ ) {
		for( i = 0; i < MAX; i++ ) {
			soma+=tab[k][i];
		}
	}
	if ( soma == -15 && tab[3][3] == 1 ) return 0;
	else return 1;
}

void resolve()
{
	int topo, passos, x, y;
	item atual;
	item pilha[32];
	topo = 0; passos = 0; x = 0; y = 0;
	atual.pos.x = 0; atual.pos.y = 0;
	atual = procura( atual, &x, &y );
	while ( ganhou() ) {
		getchar();
		printf("X = %d Y = %d Mov = %d x = %d y = %d P = %d \n", atual.pos.x, atual.pos.y, atual.mov, x, y, passos);
		desenha();	
		while ( atual.mov <= 4 ) {
			if ( podemov(atual) ) {
				printf("Empilhando - \n");
				empilha( pilha, &topo, atual );
	 			atualizatab( atual, &atual );
	 			x = 0;
	 			y = 0;
	 			passos++;
	 			getchar();
				printf("X = %d Y = %d Mov = %d x = %d y = %d P = %d \n", atual.pos.x, atual.pos.y, atual.mov, x, y, passos);
				desenha();		
			}
			else atual.mov++;
		}
		if ( atual.mov > 4 ) {
			if ( x >= 6 && y >= 4 ) {
				if ( topo == 0 ) { 
					printf("Sem Solucao.");
					break;
				}
				else {
					printf("Backtrack - \n");
					atual = topodapilha( pilha, topo );
					desatualizatab( atual ); 
					x = atual.pos.x;
					y = atual.pos.y;
					atual.mov++;
					desempilha( &topo );
					passos--;
				}
		}				 
	}
	}
	imprimesol(pilha, topo);
}

int main()
{
	desenha();
	resolve();
	desenha();
	return 0;
}

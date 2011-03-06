#include <stdio.h>
#include <stdlib.h> 

int *p, topo; /* O p é a pilha e o vetor para ser retornado */

int Podepinta ( int, int );

void empilha ( int )

void desempilha ()

void topodapilha ()

int* 4cores(int **mapa, int n )
{
	int i, cor;
	i = 0;
	topo = 0;
	p = malloc ( n*sizeof ( int ) );
	if ( p == NULL ) return(NULL);

	while ( i < n )
	{
		i++;
	}
	
}		

int podeempilhar ( int **mapa, int n, int cor )
{
	int i;
	for ( i = 0; i < n; i++ ) {
		if ( mapa[topo][i])
			if(i < topo )
				if( cor ==p[i])
					return 0;
	}
}

void empilha ( int cor )
{
	p[topo] = cor;
	topo++;
}

void desempilha ()
{
	p[topo-1] = 0;
	topo--;
}

void topodapilha()
{
	return p[topo-1];
}

int main()
{

}

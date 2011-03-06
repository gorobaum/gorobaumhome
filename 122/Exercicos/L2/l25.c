#include <stdio.h>
#include <stdlib.h>

void imprimevetor( int v[], int n)
{
	int k;
	for ( k = 0; k < n; k++) printf(" %d", v[k]);
	printf("\n");
}

void algoritmo ( int V[], int n )
{
	int *cont, *w, i, j, comp = 0, trocas = 0;
	cont = malloc (n*sizeof(int));
	w = malloc (n*sizeof(int));
	for (i = 0; i < n; i++) cont[i] = 0;
		for (i = 0; i < n; i++)
   		for (j = 0; j < n; j++)
        if (V[j] < V[i]) { 
        	cont[i]++;
        	comp++;
        }    
	for (i = 0; i < n; i++ ) {
		w[cont[i]] = V[i];
		trocas++;
	}
	for (i = 0; i < n; i++ ) V[i] = w[i];
	printf("%d %d \n", trocas, comp);
} 

int main()
{
	int v[20], i;
	for (i = 0; i < 20; i ++ ) v[i] = rand()%100;
	imprimevetor(v, 20);
	algoritmo(v, 20);
	imprimevetor(v, 20);
	return 0;
}

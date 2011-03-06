#include <stdio.h>

static int trocas = 0;
static int comp = 0;

void bubblesort(int v[], int n )
{
	int i, aux, trocou, j;
	for ( trocou = 1, j = 0; j < n -1 && trocou; j++ ) 
		for ( i = 0, trocou = 0; i < n - 1 - j; i++) 
		if ( v[i] > v[i+1] )
			aux = v[i], v[i] = v[i+1], v[i+1] = aux, comp++, trocas++, trocou = 1;
	printf("Bubblesort: \n Numero de trocas:%d Numero de comparacoes:%d \n", trocas, comp );					
}

void mergesort( int p, int r, int v[])
{
	if ( p < r - 1 ) {
		int q = ( p + r )/2;
		mergesort(p ,q ,v);
		mergesort(q ,r ,v);
		intercala(p, q, r, v);
		printf("Mergesort: \n Numero de trocas:%d Numero de comparacoes:%d \n", trocas, comp );
}

void intercala( int p, int q, int r, int v[] )
{
	int i, j, k, *w;
	w = malloc ((r - p) * sizeof (int));
	i = p, j = q, k = 0;
	
	while ( i < q && j < r ) {
		if ( v[i] <= v[j]) w[k++] = v[i++];
		else w[k++] = v[j++];
	}
	while ( i < q ) w[k++] = v[i++];
	while ( j < r ) w[k++] = v[j++];
	for ( i = p; i < r; i++ ) v[i] = w[i-p];
	free(w);
}

int main()
{
	int v[12] = { 12, 23, 5, 9, 0, 4, 1, 12, 21, 2, 5, 14 },
	n, k;
	n = 12;
	for ( k = 0; k < n; k++) printf("%d  ", v[k]);
	printf("\n");
	trocas = 0;
	comp = 0;
	bubblesort( v, n);
	for ( k = 0; k < n; k++) printf("%d  ", v[k]);
	printf("\n");
	trocas = 0;
	comp = 0;
	mergesort(0, 12, v);
	return 0;	
}

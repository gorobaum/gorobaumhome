#include <stdio.h>
#include <stdlib.h>

static int trocas = 0;
static int comp = 0;

void bubblesort(int v[], int n )
{
	int i, aux, trocou, j;
	for ( trocou = 1, j = 0; j < n -1 && trocou; j++ ) 
		for ( i = 0, trocou = 0; i < n - 1 - j; i++) 
		if ( v[i] > v[i+1] )
			aux = v[i], v[i] = v[i+1], v[i+1] = aux, comp++, trocas++, trocou = 1;					
}

void intercala( int p, int q, int r, int v[] )
{
	int i, j, k, *w;
	w = malloc ((r - p) * sizeof (int));
	i = p, j = q, k = 0;
	
	while ( i < q && j < r ) {
		if ( v[i] <= v[j]) w[k++] = v[i++], comp++, trocas++;
		else w[k++] = v[j++], trocas++;
	}
	while ( i < q ) w[k++] = v[i++], trocas++;
	while ( j < r ) w[k++] = v[j++], trocas++;
	for ( i = p; i < r; i++ ) v[i] = w[i-p], trocas++;
	free(w);
}

void mergesort( int p, int r, int v[])
{
	if ( p < r - 1 ) {
		int q = ( p + r )/2;
		mergesort(p ,q ,v);
		mergesort(q ,r ,v);
		intercala(p, q, r, v);
	}
}

void insereemheap( int m, int v[] )
{
	int f = m + 1, t;	
	while ( f > 1 && v[f/2] < v[f] ) {
		comp++;
		trocas++;
		t = v[f/2]; v[f/2] = v[f]; v[f] = t;
		f = f/2;
	} 
}

void sacodeheap ( int m, int v[] )
{
	int t, f = 2;
	while ( f <= m ) {
		if ( f < m && v[f] < v[f+1] ) ++f;
		if ( v[f/2] >= v[f] ){ 
			comp++;	
			break;
		}
		t = v[f/2]; v[f/2] = v[f]; v[f] = t;
		f *= 2;
		comp++;
		trocas++;
		}
}

void heapsort(int n, int v[])
{
	int m;
	for ( m = 1; m < n; m++ ) insereemheap ( m, v );
	for ( m = n; m > 1; m-- ) {
		int t = v[1]; v[1] = v[m]; v[m] = t;
		sacodeheap ( m-1, v );
	}
}

int separa(int ini, int fim, int v[])
{
	int x, aux;
	x = v[ini];
	if ( ini != fim ) {
		while ( v[fim] >= x ) {
			aux = v[fim--];	
			v[fim] = v[ini];
			v[ini] = aux;
			comp++;
			trocas++;
		}
		while ( v[ini] < x ) {
			aux = v[fim];
			v[fim] = v[ini++];
			v[ini] = aux;
			comp++;
			trocas++;
		}
	}
	return ini;	  
}

void quicksort(int ini, int fim, int v[])
{
	int ind;
	if ( fim - ini >= 1 ) {
		ind = separa( ini, fim, v );
		quicksort( ini, ind, v);
		quicksort( ind + 1, fim, v);
	}
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
	printf("Bubblesort: \n Numero de trocas:%d Numero de comparacoes:%d \n", trocas, comp );
	for ( k = 0; k < n; k++) printf("%d  ", v[k]);
	printf("\n");
	trocas = 0;
	comp = 0;
	mergesort(0, 12, v);
	printf("Mergesort: \n Numero de trocas:%d Numero de comparacoes:%d \n", trocas, comp );
	for ( k = 0; k < n; k++) printf("%d  ", v[k]);
	printf("\n");
	trocas = 0;
	comp = 0;
	/*heapsort(12, v);
	printf("Heapsort: \n Numero de trocas:%d Numero de comparacoes:%d \n", trocas, comp );
	for ( k = 0; k < n; k++) printf("%d  ", v[k]);
	printf("\n");*/
	trocas = 0;
	comp = 0;
	quicksort(0, 12, v);
	printf("Quicksort: \n Numero de trocas:%d Numero de comparacoes:%d \n", trocas, comp );
	for ( k = 0; k < n; k++) printf("%d  ", v[k]);
	return 0;	
}

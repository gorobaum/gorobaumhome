#include <stdio.h>
#include <stdlib.h>

static int comp;

int MAX( int x, int y ) 
{
 if ( x > y ) return x;
 	return y;
}

int MIN( int x, int y ) 
{
 if ( x > y ) return y;
 	return x;
}

void imprimevetor( int v[], int n)
{
	int k;
	for ( k = 0; k < n; k++) printf("  %d", v[k]);
	printf("\n");
}

void junta( int v[], int m, int s[], int n )
{
	int k, i, j, *w;
	w = malloc ( (n+m) * sizeof ( int ) );
	if ( w == NULL ) {
		printf("Memoria insulficiente \n");
		exit(0);
	}
	for ( i = 0, j = 0, k = 0; i < m && j < n; k++ ) {
		if ( v[i] <= s[j] ) w[k] = v[i++];
		else w[k] = s[j++];
		printf(" \n%d %d %d", k, j ,i);
		comp++;
	}
	if ( j == n ) 
	for ( k = i; k < m; k++) w[n+k] = v[i++];
	else if ( i == m )
	for ( k = j; k < n; k++) w[m+k] = s[j++];
	imprimevetor(w, (m+n));
}

int main()
{
	int v[5] = {10, 10, 10, 10, 10}, s[5] = {9, 9, 9, 9, 9};
	comp = 0;
	imprimevetor(v , 5);
	imprimevetor(s , 5);
	junta(v, 5, s, 5);
	printf("\n %d", comp);
	return 0;
}

#include <stdio.h>

void arruma( int v[], int n )
{
	int i, j, t;
	i = 0, j = n-1;
	while ( j != i ) {
		if ( v[i] <= 'A' ) i++;
		else {
			t = v[i]; v[i] = v[j]; v[j] = t;
			j--;
		}
	}
}

int main()
{
	int v[20] = {'B', 'A', 'B', 'A', 'A', 'A', 'B', 'B', 'A', 'B', 'B', 'A', 'A', 'A', 'B', 'B', 'A', 'A', 'B', 'A'};	
	int k = 0;
	for ( k = 0; k < 20; k++) printf("%c  ", v[k]);
	printf("\n");
	arruma(v, 20); 
	for ( k = 0; k < 20; k++) printf("%c  ", v[k]);
	printf("\n");
	return 0;
}

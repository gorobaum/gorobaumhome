#include <stdio.h>
#include <string.h>

void comparing( char s[], int n, char p[], int m)
{
	int i, k, achou;
	achou = 0;
	for ( i = 0; i < n - m; i++ ) {
		for ( k = 0; k < m && p[k] == s[i + k]; k++ ) {
			if ( k == m ) achou++;
		}
	}
	printf("%d \n", achou);	
}

int main()
{
	char s[27], p[4];
	strcpy( s, "0000100010000100010110100" );
	strcpy( p, "0001" );
	comparing( s, 27, p, 4 );
	return 0;
}

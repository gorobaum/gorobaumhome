#include <stdio.h>
#include <stdlib.h>

typedef struct MaxMin {
		int max;
		int min;
		}	maxmin;
		
*maxmin MaxMin ( int v[], int n, maxmin *t )
{	
	if ( v[n] >= t->max ) t->max = v[n];
	if ( v[n] <= t->min ) t->min = v[n];
	MaxMin ( v[], ++n, t );
  return t;
}  

int main ()
{
	int v[6] = { 0, 10, 7, 14, 2, 1 };
	maxmin *t = malloc( 1 * (sizeof ( maxmin ) ) );
	MaxMin( v, 0, t);
	printf("%d %d", t->max, t->min);
	return 0;
}
	
	

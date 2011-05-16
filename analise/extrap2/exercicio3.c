/*username Gorobaum */
/*password rajimema */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1000
#define maxT 5607

int separa (int str[], int wgt[], int p, int r)
{
	int c = str[p], k = wgt[p], i = p+1, j = r, t;
	while ( i <= j) {
  		if (str[i] <= c) ++i;
		else if (c < str[j]) --j; 
		else {
     		t = str[i], str[i] = str[j], str[j] = t;
 			t = wgt[i], wgt[i] = wgt[j], wgt[j] = t;
     		++i; --j;
  		}
   	}                
	str[p] = str[j], str[j] = c;
   	wgt[p] = wgt[j], wgt[j] = k;
   	return j; 
}

void quickSort (int str[], int wgt[], int p, int r)
{
	int j;
	while (p < r) {      
	  j = separa (str, wgt, p, r);    
	  if (j - p < r - j) {     
		 quickSort (str, wgt, p, j-1);
		 p = j + 1;            
	  } 
	  else {                 
		 quickSort (str, wgt, j+1, r);
		 r = j - 1;
	  }
	}
}

int min(int a, int b) {
	if ( a > b ) return b;
	else return a;
}

void printfmatriz(int **c, int co, int l ) {
	int i, j;
	
	for ( i = 0; i < co; i++ ) {
		for ( j = 0; j < l; j++ )
			printf("%6d", c[i][j]);
		printf("\n");
	}	

}

int infi(int v[], int size ) {
	int i, max;
	max = 0;
	for ( i = 0; i < size; i++ ) max += v[i];
	max++;
	return max;
}

int bestThrone( int str[], int wgt[], int turtles) {
	int **c, i ,j, infinito, maxt;
	
	infinito = infi(wgt, turtles);
	maxt = 0;
	
	c = malloc(turtles*sizeof(c));
	for ( i = 0; i < turtles+1; i++ ) {
		c[i] = malloc((turtles+1)*sizeof(int));
		for ( j = 0; j < (turtles+1); j++ ) {
			if ( j > i ) c[i][j] = infinito;
			else c[i][j] = 0;
		}
	}
	for ( i = 1; i < turtles+1; i++ ) {
		for ( j = 1; j < turtles+1; j++ ) {
			if( c[i-1][j-1] + wgt[i-1] <= str[i-1] ) c[i][j] = min( c[i-1][j], c[i-1][j-1]+wgt[i-1]);
			else c[i][j] = c[i-1][j];
		}
	}
	for ( j = 0, i = turtles; j < turtles+1; j++ ) if ( c[i][j] < infinito ) maxt = j;
	return maxt;
}

int main() {
	int wgt[maxT], str[maxT], turtles;
	char *line, *st, *wt;
	
	line = malloc(LINESIZE*sizeof(char));
	st = malloc(LINESIZE*sizeof(char));
	wt = malloc(LINESIZE*sizeof(char));
	
	turtles = 0;
	
 	while( fgets(line, LINESIZE, stdin) != NULL ) {
 		sscanf(line,"%s %s", wt, st);
 		wgt[turtles] = atoi(wt);
 		str[turtles] = atoi(st);
		turtles++;
	}
	
	quickSort( str, wgt, 0, turtles-1);
	
	printf("%d\n", bestThrone(str, wgt, turtles));
	return 0;
}

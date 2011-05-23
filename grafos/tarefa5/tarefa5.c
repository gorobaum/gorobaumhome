/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define MAXVERTEX 100
#define LINESIZE 20

int main(){
    int NumVert, NumArcs, i, posLine, tam, *parnt;
    double *cst;
    char line[LINESIZE], ptr[LINESIZE], arc1[LINESIZE], arc2[LINESIZE], prob[LINESIZE];
    Graph G;
    
    while ( fgets(line, LINESIZE, stdin) != NULL ) {
		sscanf(line, "%s %n", ptr, &tam);
    	NumVert = atoi(ptr);
    	if ( NumVert == 0 ) break;
    	posLine = tam;
    	sscanf(line+posLine, "%s %n", ptr, &tam);
    	NumArcs = atoi(ptr);
    	
    	G = DIGRAPHinit(NumVert);
    	parnt = malloc(NumVert*sizeof(int));
    	cst = malloc(NumVert*sizeof(double));
    	
    	for ( i = 0; i < NumArcs; i++ ) {
    		fgets(line, LINESIZE, stdin);
    		if ( sscanf(line, "%s %s %s", arc1, arc2, prob) == 3 ) {
				GRAPHinsertE( G, atoi(arc1)-1, atoi(arc2)-1, atof(prob)/100.0 );
			}
		}
		dijkstra(G, 0, parnt, cst);
		printf("%f\n", cst[NumVert-1]*100.0);
	}
			
        
    return 0;
}

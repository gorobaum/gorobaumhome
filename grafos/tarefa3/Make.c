/*username Gorobaum */
/*password rajimema123 */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int main() {
    int NumVert, NumArcs, i, j,*bipartite, inst;
    char *line, *ptr;
    Graph G;
    
    line = malloc(LINESIZE*sizeof(char));
    inst = 0;
    
    while ( fgets(line, 10, stdin) != NULL ) {
        if ( inst != 0 ) printf("\n");
        for ( j = 0; j < LINESIZE && line[j] != ' '; j++);
        ptr = line+j*sizeof(char);
        NumVert = atoi(line);
        NumArcs = atoi(ptr);
        
        bipartite = malloc(NumVert*sizeof(int));
        for ( i = 0; i < NumVert; i++ ) bipartite[i] = 0;
        G = GRAPHinit(NumVert);
        inst++;
        
        for ( i = 0; i < NumArcs && fgets(line, 10, stdin) != NULL; i++ ) {
            for ( j = 0; j < LINESIZE && line[j] != ' '; j++);
            ptr = line+j*sizeof(char);
            GRAPHinsertE(G, (atoi(line)-1), (atoi(ptr)-1));
        }
        printf("Instancia %d\n", inst);
        if ( GRAPHisbipart(G, bipartite) == 1 ) printf("sim\n");
        else printf("nao\n");
        free(bipartite);
        free(G);
    }
    free(line);
    return 0;
}

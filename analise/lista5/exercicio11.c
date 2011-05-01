/*username Gorobaum */
/*password rajimema */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 100

int min(int a, int b) {
    if ( a <= b) return a;
    else return b;
}

int Mem-CalcMinCuts(int *cutstodo, int numcut, int length, int *cuts){
    
}

int CalcMinCuts(int *cutstodo, int numcut, int length){
    int *cuts, i, j, cost;
    
    cuts = malloc(numcut*sizeof(int));
    for( i = 0; i < numcuts; i++ ) cuts[i] = 0;

    return Mem-CalcMinCuts(cutstodo, numcut, length, cuts);         
}

int main() {
    int length, numcut, *cuts, i;
    char *line, *aux;
    
    line = malloc(LINESIZE*sizeof(char));
    
    while ( (fgets(line, 100, stdin) != NULL) && line[0] != '0') {
        length = atoi(line);
        fgets(line, 100, stdin);
        numcut = atoi(line);
        cuts = malloc(numcut*sizeof(int));
        fgets(line, 100, stdin);
        aux = strtok(line, " ");
        i = 0;
        while( aux != NULL ){
            cuts[i] = atoi(aux);
            aux = strtok(NULL, " ");
            i++;
        }
        
    }
    return 0;
}

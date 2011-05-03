/*username Gorobaum */
/*password rajimema */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1000

int CalcMinCuts(int cuts[], int numcut, int length){
    int c[LINESIZE][LINESIZE], i, j, k, l;

    for( i = 1; i <= numcut+1; i++ ) c[i][i-1] = 0;

    for( l = 1; l <= numcut; l++ ) {
        for( i = 1; i <= numcut-l+1; i++ ) {
            j = i+l-1;
            c[i][j] = c[i+1][j];
            for( k = i+1; k <= j; k++ )
                if (c[i][k-1] + c[k+1][j] < c[i][j] ) c[i][j] = c[i][k-1] + c[k+1][j];
            c[i][j] = c[i][j] + cuts[j+1] - cuts[i-1];
        }
    }
    return c[1][numcut];
}

int main() {
    int length, numcut, cuts[LINESIZE], i, aux, tam;
    char line[LINESIZE], str[LINESIZE];
    
    while ( (fgets(line, LINESIZE, stdin) != NULL) && line[0] != '0') {
        length = atoi(line);
        fgets(line, LINESIZE, stdin);
        numcut = atoi(line);
        fgets(line, LINESIZE, stdin);
        aux = 0;
        i = 1;
        while (sscanf(line+aux, "%s %n", str, &tam) == 1){
            cuts[i] = atoi(str);
            i++;
            aux += tam;
        }
        cuts[0] = 0;
        cuts[i] = length;
        printf("The minimum cutting is %d.\n", CalcMinCuts(cuts, numcut, length));
    }
    return 0;
}

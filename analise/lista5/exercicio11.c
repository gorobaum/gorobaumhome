/*username Gorobaum */
/*password rajimema */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printmatrix(int m[100][100], int i, int j ) {
    int x,y;
    for ( x = 0; x < i; x++ ) {
        for ( y = 0; y < j; y++ ) printf("%d ", m[x][y]);
        printf("\n");
    }
}

int CalcMinCuts(int cuts[], int numcut, int length){
    int c[100][100], i, j, k, l;

    for( i = 0; i < numcut+1; i++ ) c[i][i-1] = 0;

    for( l = 1; l <= numcut; l++ ) {
        for( i = 1; i <= numcut-l+1; i++ ) {
            j = i+l-1;
            c[i][j] = c[i+1][j];
            printf("c[%d][%d] = %d \n", i, j, c[i][j]);
            for( k = i+1; k <= j; k++ )
                if (c[i][k-1] + c[k+1][j] < c[i][j] ) c[i][j] = c[i][k-1] + c[k+1][j];
            c[i][j] = c[i][j] + 
        }
    }
    /*printmatrix(c, numcut, numcut);*/
    return c[1][numcut];
}

int main() {
    int length, numcut, cuts[1000], i;
    char line[1000], *aux;
    
    while ( (fgets(line, 100, stdin) != NULL) && line[0] != '0') {
        length = atoi(line);
        fgets(line, 100, stdin);
        numcut = atoi(line);
        fgets(line, 100, stdin);
        aux = strtok(line, " ");
        i = 1;
        while( aux != NULL ){
            cuts[i] = atoi(aux);
            aux = strtok(NULL, " ");
            i++;
        }
        cuts[0] = 0;
        cuts[i+1] = length;
        printf("%d \n", CalcMinCuts(cuts, numcut, length));
    }
    return 0;
}

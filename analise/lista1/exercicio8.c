/*
    Nome: Thiago de Gouveia Nunes
    #USP: 6797289
    MAC0338 - Analise de Algoritmos
    Data - 16/03/2011
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define VETORSIZE 5

/*  Coloquei uma funcao para gerar vetores aleatorios e para imprimir os vetores
    para que eu possa testar o algoritmo, eles nao influem no algoritmo em si. */
int* RANDvetor( int size ) {
    int* vetor;
    int i, j, aux;
    
    vetor = malloc(size*sizeof(int));
    for ( i = 0; i < size; i++ ) vetor[i] = i+1;
    for ( i = 0; i < size; i++ ) {
        j = rand()%size;
        aux = vetor[j];
        vetor[j] = vetor[i];
        vetor[i] = aux;
    }

    return vetor;
}

void PRINTvetor ( int*A ) {
    int i;
    for ( i = 0; i < VETORSIZE; i++ ) printf("%d ", i);
    printf("\n");
    for ( i = 0; i < VETORSIZE; i++ ) printf("%d ", A[i]);
    printf("\n");
}

int CONTintercala ( int* A, int p, int q, int r) {
    int* B;
    int i, j, c, k, l, m;
    B = malloc((r+1)*sizeof(int));
    for ( i = p; i <= q; i++ ) B[i] = A[i];
    for ( j = q+1; j <= r; j++ ) B[r+q+1-j] = A[j];

    i = p;
    l = i;
    j = r;
    m = j;
    c = 0;
  
    for ( k = p; k <= r; k++ ) {
        if ( B[l] > 2*B[m] ) {
                c += ((q-l)+1);
                m--;
        }
        else l++;
        if ( B[i] < B[j] ) {
            A[k] = B[i];
            i++;
        }
        else {
            A[k] = B[j];
            j--;
        }
    }
    return c;
}

int CONTordena ( int* A, int p, int r ) {
    int c, q;    
    if ( p >= r ) return 0;
    else {
        q = floor( (p+r)/2 );
        c = CONTordena(A, p, q) + CONTordena(A, q+1, r) + CONTintercala(A, p, q, r);
    }
    return c;
} 

int main() {
    int* vetor;
    srand(time(NULL));   
 
    vetor = RANDvetor( VETORSIZE );
    PRINTvetor(vetor);
    printf("\n%d\n", CONTordena( vetor, 0, VETORSIZE-1 ));
    return 0;
}

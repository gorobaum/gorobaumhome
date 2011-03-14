#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define VETORSIZE 15

int* RANDvetor( int size ) {
    int* vetor;
    int i, j, aux;
    
    vetor = malloc(size*sizeof(int));
    for ( i = 0; i < size; i++ ) vetor[i] = i;
    for ( i = 0; i < size; i++ ) {
        j = rand()%size;
        aux = vetor[j];
        vetor[j] = vetor[i];
        vetor[i] = aux;
    }

    return vetor;
}

int CONTintercala ( int* A, int p, int q, int r) {
    int* B;
    int i, j, c, k;

    B = malloc(VETORSIZE*sizeof(int));
    for ( i = p; i < q; i++ ) B[i] = A[i];
    for ( i = q+1; i < r; i++ ) B[r+q+1-i] = A[i];
    
    i = p;
    j = r;
    c = 0;
    
    for ( k = p; k < r; k++ ) {
        if ( B[i] < B[j] ) { 
            A[k] = B[i];
            i++;
        }   
        else {
            if ( B[i] > 2*B[j] ) c += 1 + j - r;
            A[k] = B[j];
            j++;
        }
    }
    free(B);  
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
    int i;

    srand(time(NULL));    

    vetor = RANDvetor( VETORSIZE );
    for ( i = 0; i < VETORSIZE; i++ ) printf("%d  ", i);
    printf("\n"); 
    for ( i = 0; i < VETORSIZE; i++ ) printf("%d  ", vetor[i]);
    printf("\n");
    
    printf("\n%d\n", CONTordena( vetor, 0, VETORSIZE ));    
    free(vetor);
    return 0;
}

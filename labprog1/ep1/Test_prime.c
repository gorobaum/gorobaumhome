#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SQUARE 256 //Maior numero que vai ser usado pelo clivo de erastoteles, pois raiz(65535) e aproximadamente 256
#define MAX_SIZE   1000000 //A maior quantidade de numeros a serem testados.


/* Essa funcao usa o Clivo de Erastoteles, como no Assembly. A implementecao do algoritmo e a mesma. */
void primes(unsigned int *primen, int size, FILE *pfile ) {
	int div, i, primes = 0;
	
	for ( i = 0, div = 2; div <= 256; i++ ) {
		if ( i <= size ) {
			if ( ( primen[i] != -1) && ( primen[i]%div == 0) ) primen[i] = -1; 
		}
		else {
			i = 0;
			div++;
		}
	}
	
	for ( i = 0; i <= size; i++ ) {
		if ( primen[i] != -1 ) {
			primes++;
			fprintf( pfile, "%u \n", primen[i] );
		}
	}
	
	printf("Foram encontrados %u primo(s) \n", primes);
}	

/* O main usa a mesma logica do nosso EP. Ele pega os numeros que estao num arquivo A, recolhe somente os que estao dentro do intervalo [p,r] e depois filtra os primos dos numeros recolhidos usando a funcao primes. */
int main( int argc, char **argv ) {
	if ( argc != 5 ) {
		printf("Uso <num> <num> <falenamein> <falinameout> \n");
	}
	else {
		unsigned int p, r, i, number, *primen;
		FILE *pfilein, *pfileout;
		
		p = atoi(argv[1]);
		r = atoi(argv[2]);
		pfilein = fopen( argv[3], "r");
		pfileout = fopen( argv[4], "w");
		primen = malloc(MAX_SIZE*sizeof(int));
		if ( pfilein == NULL ) printf("Seu feio. \n");
		fscanf(pfilein,"%u", &number);
		
		for ( i = 0 ; fscanf(pfilein,"%u", &number) != EOF; ) {
			if( number >= p && number <= r ) {
				primen[i] = number;
				i++;
			}
			fscanf(pfilein,"%u", &number);
		}
		primes( primen, i, pfileout );
	}
	return 0;
}

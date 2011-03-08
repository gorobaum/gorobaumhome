/***********************************************************************************************************

MAC211 - Laboratorio de Programação
IME - USP - Primeiro semestre de 2010
Turma 45 - Prof. Fabio Kon

Primeiro Exercicio-programa
Arquivo EP1.c

Aluno:									Numero USP:
Wilson Kazuo Mizutani				    6797230
Thiago G. Nunes							6797289

06/04/2010

***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_NUM_16_BIT 65536

/* Esta funcao e usada para preencher o arquivo <filename> com <num> numeros aleatorios */
int main( int argc, char **argv) {
		
		if ( argc != 3 ) {
		 	printf("Uso: %s <num> <filename>.", argv[0]);
		 	return 0;
		}
		else {
	    	int nrand, j = 0;
	    	register int i;
	    	unsigned int N = atoi(argv[1]);
	    	char *buffer = malloc( (6*N)*sizeof(char));
	    	
	    	FILE *pFile = fopen( argv[2], "w");
	    	
	    	srand ( time(NULL) );
	    	
	    	for ( i = 0; i < 6*N; i++ ) buffer[i] = ' ';
	    	
	    	/* Neste for o numero 65536 e usado para garantir que o numero gerado tenha 16 bit. */	    	
	    	for( i = 0; i < N; i++ ) {
	    		nrand = rand()%MAX_NUM_16_BIT;
	    		sprintf( buffer+j, "%d", nrand );
	    		j += (int)log10( nrand ) + 2;
	    		buffer[j-1] = ' ';
	    	}
		
		    fwrite( buffer, 1, j, pFile);
		    return 0; 
		}
}

/*******************************************************************************

MAC211 - Laboratorio de Programação
IME - USP - Primeiro semestre de 2010
Turma 45 - Prof. Fabio Kon

Primeiro Exercicio-programa
Arquivo EP1main.c

Aluno:									Numero USP:
Wilson Kazuo Mizutani				    6797230
Thiago G. Nunes							6797289

06/04/2010

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int filtra_os_primos (unsigned short int p, unsigned short int r,
  char * nome_arquivo_entrada, char * nome_arquivo_saida);
  
void print_num(unsigned int fdout, unsigned short num);


/* Esta e' a funcao em C princiapl do EP. Ela prepara os argumentos para a parte
 * em assemble a chama. */
int main( int argc, char **argv ) {
	
    unsigned short int p, r, aux;
    
    if ( argc != 5 ) {
        printf("Uso: %s <num> <num> <filenamein> <filenameout>.\n", argv[0]);
		return 0;
	}
	else {
        p = atoi(argv[1]);
        r = atoi(argv[2]);
        
        if(p > r) aux = r, r = p, p = aux;

        printf("%d primo(s) encontrado(s).\n", filtra_os_primos ( p, r, argv[3],
          argv[4] ) );
    
        return 0;
    }
}

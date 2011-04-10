/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP3.c

Aluno:									Numero USP:
Thiago G. Nunes							6797289

19/06/2010

***********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "compress.h"


/* Essa funcao cria o nome do arquivo que sera criado dependendo da operacao
   escolhida. Which = 0 e´ a compressao e Which = 1 e´ a descompressao. */
void NewFileName( char *Name, char *NewName, int Which )
{	
    if ( Which == 0 ) 
    {
    	strcpy( NewName, Name );
    	strcat( NewName, ".cod" );
   	}
    else if ( Which == 1 ) 
    {
    	strncpy( NewName, Name, strlen(Name)-4 );
    	strcat( NewName, ".dec" );
    }
    else
   	{
		printf("Erro na criacao do nome do arquivo! \n");
		exit(0);
	}
}

/* O main cira dois ponteiros para arquivos, um para a entrada e outro para saida.
   O ponteiro Entry abre o arquivo passado para o programa via os parametros rece
   bidos e o ponteiro Out abre o arquivo com o nome recebido da funcao NewFileName.
   Com isso o programa compacta ou descompacta o arquivo Entry, baseado no prime
   iro ponteiro. */
int main( int argc, char **argv )
{
    FILE *Entry, *Out;
    char NewFile[100];
        
    if ( argc <= 1 ) printf("Esse programa usa ./EP3 <nome_do_arquivo> \n");
    else
    {
        if ( strcmp( argv[1], "-x" ) == 0 )
        {
            printf("Descompactando... \n");
            Entry = fopen(argv[2],"r");
            NewFileName( argv[2], NewFile, 1 );
            Out = fopen( NewFile, "wb+" );
            DecompressFile( Entry, Out );    
        }
        else
        {
            printf("Compactando... \n");
            Entry = fopen(argv[1],"r");
            NewFileName( argv[1], NewFile, 0 );
            Out = fopen( NewFile, "wb+");
            CompressFile( Entry, Out );
        } 
        fclose( Entry );
        fclose( Out );  
    }
    return 0;   
}

/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Interface.h"

int main( int argc, char** argv )
{
	char entry[100], *Auxstring, AuxBook[100];
	int NP;
	BST WordBst;
	Pilha PilhaRPN;
	pNode Aux;
	FILE* auxFile;
	
	NP = 0;
	WordBst = BSTinit();
	PilhaRPN = STACKinit( 0 );
	
	if ( argc > 1 )
	{
		if ( argv[1][0] == '-' && argv[1][1] == 'f' )
		{
			Auxstring = argv[1] + 2;
			auxFile = fopen( Auxstring, "r" );
			if ( auxFile == NULL ) printf("Erro!");
			else
			{
				fscanf( auxFile, "%s", AuxBook );
				while ( feof( auxFile ) == 0 )
				{
					AddBookToBst( WordBst, AuxBook );
					fscanf( auxFile, "%s", AuxBook );				
				}
			}
		}
		else AddBookToBst( WordBst, argv[1]);
	}
	
	while(1)
	{
		printf("ep2 > ");
		scanf("%s", entry );
		if ( entry[0] == '.' )
		{
			if ( entry[1] == '+' )
			{
				Auxstring = entry + 2;
				AddBookToBst( WordBst, Auxstring );
			}
			else if ( entry[1] == '-' )
			{
				Auxstring = entry + 2;
				BSTRemoveBook( WordBst, Auxstring );
			}
			else if ( entry[1] == 'D' )
			{
				STACKrelivetop( PilhaRPN );
			}
			else if ( entry[1] == 'p' )
			{
				LLprint( STACKpeek( PilhaRPN ), NULL );
			}
			else if ( entry[1] == 'q' )
			{
				Auxstring = entry + 2;
				if ( strcmp( Auxstring, "uit" ) == 0 ) break;
				else printf("Erro!");
			}
			else if ( entry[1] == 'N' )
			{
				if ( entry[2] == 'P' ) printf("Tem %d elementos na pilha. \n", STACKsize( PilhaRPN ) );
				else printf("Erro!");
			}
		}
		else if ( entry[0] == '+' ) Plus( PilhaRPN );
		else if ( entry[0] == '-' ) Except( PilhaRPN );
		else if ( entry[0] == '/' ) Diff( PilhaRPN );
		else 
		{	
			ToLowerCase( strlen( entry ), entry );
			if ( ( Aux = BSTsearch( WordBst, entry ) ) != NULL ) STACKput( PilhaRPN, BSTlinked( Aux ) );
			else printf("Erro!");
		}
	}
	
	BSTdestroy( WordBst );
	STACKdestroy( PilhaRPN );
	return 0;
}

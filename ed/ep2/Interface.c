/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#include "Interface.h"

#define WORDSIZE 50

void AddBookToBst( BST bst, char* Book )
{
	FILE *pFile;
	char aux[WORDSIZE], *word, c;
	int i, line;
	long int pLine;
	LL teste;
	teste = LLinit();
	
	pFile = fopen( Book ,"r" );
	if ( pFile == NULL ) printf("Erro na abertura do Arquivo %s. \n", Book );
	else
	{
		pLine = ftell(pFile);
		i = line = 0;
		
		c = fgetc( pFile );
		while ( c != EOF ) 
		{ 
			if ( ( c >= 'A' && c <= 'Z' ) ) 
			{
				aux[i] = ( c - 'A' ) + 'a';
				i++;
			}
			else if ( ( c >= 'a' && c <= 'z') )
			{
				aux[i] = c;
				i++;
			}
			else if ( c == '\n' ) 
			{
				pLine = ftell(pFile);
				line++;
				i = 0;
			}
			else 
			{
				word = malloc((i+1)*sizeof(char)); 
				strncpy( word, aux, i );
				word[i+1] = '\0';
				if ( !BSTisthere( bst, word ) ) BSTAddNode( bst, word );
				BSTPutInNode( bst, word, Book, line, pLine );
				i = 0;
			}
			c = fgetc( pFile );
		}
		fclose(pFile);	
	}
}

void ToLowerCase( int Size, char* Word )
{
	int Cont;
	
	for ( Cont = 0; Cont < Size; Cont++ )
	{
		if ( Word[Cont] >= 'A' && Word[Cont] <= 'Z' )
			Word[Cont] = ( Word[Cont] - 'A' ) + 'a';
	}
}

void Plus( Pilha p )
{
	LL linkA, linkB, linkR;
	
	if ( STACKsize( p ) >= 2 )
	{
		linkA = STACKget(p);
		linkB = STACKget(p);
		linkR = Junction( linkA, linkB );
		STACKput( p, linkR );
	}
}

void Except( Pilha p )
{
	LL linkA, linkB, linkR;
	
	if ( STACKsize( p ) >= 2 )
	{
		linkA = STACKget(p);
		linkB = STACKget(p);
		linkR = Intersection( linkA, linkB );
		STACKput( p, linkR );
	}
}

void Diff( Pilha p )
{
	LL linkA, linkB, linkR;
	
	if ( STACKsize( p ) >= 2 )
	{
		linkA = STACKget(p);
		linkB = STACKget(p);
		linkR = Difference( linkA, linkB );
		STACKput( p, linkR );
	}
}

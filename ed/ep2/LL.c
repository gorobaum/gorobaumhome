/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#include "LL.h"

#define MAXLINE 200

typedef struct Linkedlist 
{
     pCell Head;
     pCell Last;
     int Size;
} Linkedlist;

typedef struct cell 
{
    char* book;
    int line;
    long int pLine;
    pCell Next;
} cell;

pCell CELLinit()
{
	pCell NewCell;
	
	NewCell = malloc(sizeof(cell));
	NewCell->line = 0;
	NewCell->pLine = 0;
	NewCell->Next = NULL;
	
	return NewCell;
}

LL LLinit() 
{
    LL newll;
    
    newll = malloc(sizeof(Linkedlist)); 
    if ( newll == NULL )
	{
		printf("A lista nao pode ser alocado. \n");
		exit(0);
	}
    newll->Head = NULL;
    newll->Last = NULL;
    newll->Size = 0;
    
    return newll;
}

void LLput( LL l, char* book, int line, long int pLine ) 
{
    pCell c;
    
    c = CELLinit();
	c->book = malloc( strlen( book )*sizeof( char ));
	
	if ( Isthere( l, book, line ) != 1 )
	{
    	strcpy( c->book, book );
	    c->line = line;
    	c->pLine = pLine;
    	c->Next = NULL;
    	if ( l->Head == NULL ) l->Head = c;
    	else (l->Last)->Next = c;
    	l->Last = c;
    	(l->Size)++;
    }
}

int LLempty( LL l ) 
{
    return ( l->Head == NULL );
}

void LLremoveBook( LL l, char* book ) 
{
	pCell c, aux;
    
    if ( LLempty( l ) ) printf("Lista vazia.");
    else {
    	c = l->Head;
    	while ( c != NULL && strcmp( c->book ,book ) == 0 ) 
    	{
    		l->Head = c->Next;
    		free(c);
    		c = l->Head;
    	}
    	if ( l->Head != NULL )
    	{
    		aux = l->Head;
    		c = aux->Next;
       		while ( c != NULL ) 
       		{
        		c = aux->Next;
        		if ( strcmp( c->book ,book ) == 0 ) 
        		{
        			aux->Next = c->Next;
        			free(c);
        		}
        		else aux = aux->Next;
        	}
        }
    }
}

int LLSize( LL l ) 
{
	return (l->Size);
}

void LLdestroy ( LL l ) 
{
	pCell c, b;
	c = l->Head->Next;
	b = l->Head;
	while ( c != NULL ) 
	{
		free(b);
		b = c;
		c = b->Next;
	}
	free(b);
	free(l);
}	

/* Esta funcao recebe uma lista ligada e um item e retorna 1 se o item esta na
	lista ligada, e 0 caso contrario. */
int Isthere( LL l , char* book, int line ) 
{
	pCell c;
	
	if ( !LLempty( l ) ) 
	{
		c = l->Head;
		while ( c != NULL ) 
		{
			if ( (strcmp( c->book ,book ) == 0) && line == c->line ) return 1;
			else c = c->Next;
		}
	}
	
	return 0;
}

/* Essa funcao imprime o conteudo da Lista Ligada l dependendo o book passado.
   se book for NULL, ele imprime todas as CELL da lista, se nao somente as CELL
   com campo book igual ao passado. */
void LLprint( LL l, char* Book )
{
	pCell AuxCell;
	FILE* pFile;
	char *AuxBook, Aux[MAXLINE];
	
	if ( l != NULL )
	{
		AuxBook = malloc( strlen(l->Head->book)*sizeof(char));
		strcpy( AuxBook, l->Head->book );
		printf("%s\n", AuxBook );
		AuxCell = l->Head;
		pFile = fopen( AuxBook, "r" );
		
		if ( Book == NULL )
		{
			while ( AuxCell != NULL )
			{
				if ( strcmp( AuxCell->book, AuxBook ) != 0 ) 
				{
					strcpy( AuxBook, AuxCell->book );
					pFile = fopen( AuxBook, "r" );
				}
				fseek( pFile, AuxCell->pLine, SEEK_SET );
				fgets( Aux, 200, pFile );
				printf("\t %d:%s", AuxCell->line, Aux );
				AuxCell = AuxCell->Next;
			}
		}
		else
		{
			while ( AuxCell != NULL || strcmp( AuxCell->book, Book ) != 0 ) AuxCell = AuxCell->Next;
			if ( AuxCell != NULL ) 
			{
				while ( strcmp( AuxCell->book, Book ) == 0 )
				{
					pFile = fopen( Book, "r" );
					while ( AuxCell != NULL || strcmp( AuxCell->book, Book ) != 0 )
					{
						fseek( pFile, AuxCell->pLine, SEEK_SET );
						fgets( Aux, 200, pFile );
						printf("\t %d:%s", AuxCell->line, Aux );
						AuxCell = AuxCell->Next;
					}
				}
			}
		}
	}
}
		
/* Essa funcao retorna um apontador para uma lista ligada que resulta na uniao da
	lista ligada A e a lista ligada B. Aqui usamos funcoes que iniciao uma lista
	ligada ( LLinit ), que verifica se uma lista ligada esta vazia ( LLempty ),
	uma que coloca um item numa lista ligada ( LLput ). Se nao ha uniao, um pon
	teiro para NULL e retornado.*/
LL Junction( LL a, LL b ) 
{
	LL j;
	pCell c;
	j = LLinit();

	if ( LLempty( a ) ) 
	{
		if ( LLempty( b ) ) return NULL;	
		else {
			c = b->Head;
			while ( c != NULL ) 
			{
				LLput( j, c->book, c->line, c->pLine );
				c = c->Next;
			}
			j->Size = b->Size;
		}
	}
	else {
		c = a->Head;
		while ( c != NULL ) 
		{
			LLput( j, c->book, c->line, c->pLine );
			c = c->Next;
		}
		j->Size = a->Size;
		if ( !LLempty(b) ) 
		{
			c = b->Head;
			while ( c != NULL )	
			{
				if ( !(Isthere( j, c->book, c->line ) ) ) 
				{ 
					LLput( j, c->book, c->line, c->pLine );
				}
				c = c->Next;
			}
		}
	}
	return j;
}

/* Essa funcao usa as mesmas funcoes auxiliares que a anterior, e devolve NULL se
	nao ha interseccao entre os conjuntos A e B, e a lista ligada que representa
	a interseccao caso contrario. */
LL Intersection( LL a, LL b ) 
{
	LL j;
	pCell c;
	j = LLinit();
	
	if ( LLempty(a) || LLempty(b) ) return NULL;
	else 
	{
		c = a->Head;
		while ( c != NULL ) 
		{
			if ( Isthere( b, c->book, c->line ) ) 
			{
				LLput( j, c->book, c->line, c->pLine );
			}
			c = c->Next;
		}
	}
	return j;
}
			
/* Essa funcao retorna a diferenca entre os conjuntos A e B. Se algum conjunto e
	vazio, ela devolve uma lisa ligada com o conteudo do conjunto nao nulo, caso
	contrario ela devolve a diferenca deles. Se os dois conjuntos forem vazios
	ela retorna NULL. */
LL Difference( LL a, LL b) 
{	
	LL j;
	pCell c;
	j = LLinit();
	
	if ( LLempty(a) && LLempty(b) ) return NULL;
	else if ( LLempty(a) ) 
	{
		c = b->Head;
		j->Size = b->Size;
		while ( c != NULL ) 
		{
			LLput( j, c->book, c->line, c->pLine );
			c = c->Next;
		}
	}
	else if ( LLempty(b) ) 
	{
		c = a->Head;
		j->Size = a->Size;
		while ( c != NULL ) 
		{
			LLput( j, c->book, c->line, c->pLine );
			c = c->Next;
		}
	}
	else {
		c = a->Head;
		while ( c != NULL ) 
		{
			if ( !Isthere( b, c->book, c->line ) ) 
			{
				LLput( j, c->book, c->line, c->pLine );
			}
			c = c->Next;
		}
		c = b->Head;
		while ( c != NULL ) 
		{
			if ( !Isthere( a, c->book, c->line ) ) 
			{ 
				LLput( j, c->book, c->line, c->pLine );
			}
			c = c->Next;
		}
	}
	return j;
}

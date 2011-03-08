/************************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP3.c

Aluno:									Numero USP:
Thiago G. Nunes							6797289

19/06/2010

***********************************************************************************************************/

#include "trie.h"

/********************************
    Definicoes da Trie e Node.
********************************/

typedef struct node 
{
	unsigned Index;
	unsigned Pair;
	pNode ZERO;
	pNode ONE;
} node;

typedef struct trie 
{
	pNode Root;
} trie;

/********************************
    Funcoes Auxiliares ( Trie )
********************************/

void TRIEdestroyR( pNode Node )
{
    if ( Node->ZERO != NULL ) TRIEdestroyR( Node->ZERO );
    if ( Node->ONE != NULL ) TRIEdestroyR( Node->ONE );
    NODEdestroy( Node );
}


/********************************
    Funcoes Principais ( Node )
********************************/

pNode NODEinit( int Index, int Pair ) 
{
	pNode NewNode;
	
	NewNode = malloc(sizeof(node));
	if ( NewNode == NULL )
	{
	    printf("Erro na alocacao de um novo Node \n");
		exit(0);
	}
	NewNode->Index = Index;
	NewNode->Pair = Pair;
	NewNode->ZERO = NULL;
	NewNode->ONE = NULL;
	
	return NewNode;
}

void NODEput( pNode Node, pNode NewNode, int Binary )
{
    if ( Binary == 0 ) Node->ZERO = NewNode;
    else if ( Binary == 1 ) Node->ONE = NewNode;
    else
    {
        printf("Erro na insercao em um Node! \n");
        exit(0);
    }
}

int NODEpair( pNode Node )
{
    return Node->Pair;
}

int NODEindex( pNode Node )
{
    return Node->Index;
}

void NODEdestroy( pNode Node )
{
	free(Node);
}

/********************************
    Funcoes Principais ( Trie )
********************************/

TRIE TRIEinit()
{
	TRIE NewTrie;
	
	NewTrie = malloc(sizeof(trie));
	if ( NewTrie == NULL )
	{
	    printf("Erro na alocacao da Trie \n");
		exit(0);
	}
	NewTrie->Root = NODEinit( 0, 0 );
	
	return NewTrie;
}

void TRIEdestroy( TRIE trie )
{
	pNode Node;
	
	Node = trie->Root;
	TRIEdestroyR( Node );
	free( trie );
}

int TRIEempty( TRIE trie )
{
	return ( trie->Root->ZERO == NULL && trie->Root->ONE == NULL );
}

pNode TRIEroot ( TRIE trie )
{
    return trie->Root;
}

pNode TRIEiterate( pNode Node, int Binary )
{
    if ( Binary == 0 ) return Node->ZERO;
    else if ( Binary == 1 ) return Node->ONE;
    else
    {
        printf("Erro na iteracao da Trie! \n");
        exit(0);
    }
}

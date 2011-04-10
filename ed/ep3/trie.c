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

/* Estruturas do no( Node ) e da trie ( Trie ) */

typedef struct node 
{
	unsigned Index;/* Indice usado na compactacao */
	unsigned Pair;/* Par usado na compactacao */
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

/* Funcao que libera a memoria usada na Trie. Ela funciona recursivamente para 
   desalocar os nos da Trie. */
void TRIEdestroyR( pNode Node )
{
    if ( Node->ZERO != NULL ) TRIEdestroyR( Node->ZERO );
    if ( Node->ONE != NULL ) TRIEdestroyR( Node->ONE );
    NODEdestroy( Node );
}


/********************************
    Funcoes Principais ( Node )
********************************/

/* Inicia um no com Index e Pair em seus respectivos campos, e devolve o ponteiro
   para a posicao alocada.*/
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

/* Coloca o NewNode no Ramo relativo ao int Binary do no Node. */
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

/* Devolve a informacao do campo Pair do no Node */
int NODEpair( pNode Node )
{
    return Node->Pair;
}

/* Devolve a informacao do campo Index do no Node */
int NODEindex( pNode Node )
{
    return Node->Index;
}

/* Libera a memoria usada pelo no Node */
void NODEdestroy( pNode Node )
{
	free(Node);
}

/********************************
    Funcoes Principais ( Trie )
********************************/

/* Funcao que inicia uma Trie usando a especificacao do lz78, que cira um no
   usando o indice 0 e o par 0 */
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

/* Libera a memoria usada pela Trie, usando uma funcao recursiva */
void TRIEdestroy( TRIE trie )
{
	pNode Node;
	
	Node = trie->Root;
	TRIEdestroyR( Node );
	free( trie );
}

/* Verifica se a Trie esta vazia. */
int TRIEempty( TRIE trie )
{
	return ( trie->Root->ZERO == NULL && trie->Root->ONE == NULL );
}

/* Devolve o no Raiz da Trie */
pNode TRIEroot ( TRIE trie )
{
    return trie->Root;
}

/* Funcao que itera sobre a Trie. Ela recebe um no Node e retorna o ponteiro do
   proximo no, que e pego usando o int Binary, que determina qual ramo usaremos 
   para procurar o proximo Node. */
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

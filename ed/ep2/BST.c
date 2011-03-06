/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#include "BST.h"
#include "LL.h"

typedef struct node 
{
	char* Key;
	LL Occurence;
	pNode Esq;
	pNode Dir;
} node;

typedef struct bst 
{
	pNode Root;
} bst;

pNode NODEinit( char* name ) 
{
	pNode NewNode;
	
	NewNode = malloc(sizeof(node));
	
	NewNode->Key = name;
	NewNode->Occurence = LLinit();
	NewNode->Dir = NULL;
	NewNode->Esq = NULL;
	
	return NewNode;
}

void NODEdestroy( pNode Node )
{
	LLdestroy( Node->Occurence );
	free(Node);
}

BST BSTinit()
{
	BST NewBst;
	
	NewBst = malloc(sizeof(bst));
	
	NewBst->Root = NULL;
	
	return NewBst;
}

void BSTdestroyR( pNode Node )
{
	if ( Node != NULL )
	{
		BSTdestroyR( Node->Dir );
		BSTdestroyR( Node->Esq );
		NODEdestroy( Node );
	}
}

void BSTdestroy( BST bst )
{
	pNode Node;
	
	Node = bst->Root;
	BSTdestroyR( Node );
	free( bst );
}
	
int BSTempty( BST bst )
{
	return ( bst->Root == NULL );
}

int BSTisthere( BST bst, char* name )
{
	pNode AuxNode;
	
	if ( BSTempty( bst ) ) return 0;
	else 
	{
		AuxNode = bst->Root;
		while( AuxNode != NULL ) 
		{
			if ( strcmp( name, AuxNode->Key ) < 0 ) AuxNode = AuxNode->Esq;
			else if ( strcmp( name, AuxNode->Key ) > 0 ) AuxNode = AuxNode->Dir;
			else return 1;
		}
		return 0;
	}

}

pNode BSTsearch( BST bst, char* name )
{
	pNode AuxNode;
	
	if ( BSTempty( bst ) ) return NULL;
	else
	{
		AuxNode = bst->Root;
		while( AuxNode != NULL ) 
		{
			if ( strcmp( name, AuxNode->Key ) < 0 ) AuxNode = AuxNode->Esq;
			else if ( strcmp( name, AuxNode->Key ) > 0 ) AuxNode = AuxNode->Dir;
			else return AuxNode;
		}
		return NULL;
	}
}

LL BSTlinked( pNode Node )
{
	return (Node->Occurence);
}

void BSTAddNode( BST bst, char* name )
{
	pNode NewNode, AuxNode;
	
	NewNode = NODEinit( name );
	
	if ( BSTempty( bst ) ) bst->Root = NewNode;
	else
	{
		AuxNode = bst->Root;
		while( AuxNode != NULL ) 
		{
			if ( strcmp( name, AuxNode->Key ) < 0 ) 
			{
				if ( AuxNode->Esq == NULL ) 
				{
					AuxNode->Esq = NewNode;
					break;
				}				
				else AuxNode = AuxNode->Esq;
			}
			else if ( strcmp( name, AuxNode->Key ) >= 0 ) 
			{
				if ( AuxNode->Dir == NULL ) 
				{
					AuxNode->Dir = NewNode;
					break;
				}
				else AuxNode = AuxNode->Dir;
			}
		}
	}
}

void BSTPutInNode( BST bst, char* name, char* Book, int line, long int pLine )
{
	pNode AuxNode;
	
	AuxNode = BSTsearch( bst, name );
	
	LLput( AuxNode->Occurence, Book, line, pLine );
}

/* A funcao BSTremove primeiro procura pelo NODE com campo Key igual a name. 
   Depois, verifica se ela tem mais de um filho. Se sim, ela procura o NODE com
   a menor das maiores Key em relacao a name. Com esse NODE encontrado, o algoritmo
   troca a Key e a Occurence do primeiro NODE com o segundo NODE e deleta o segundo
   NODE. Se o primeiro NODE tem menos de dois filhos, ele o deleta, colocando no
   pNode que levou ate ele o seu unico filho. */
void BSTremove( BST bst, char* name )
{
	pNode NodeDelete, NodeDeleteBef, AuxNodeBef, AuxNode;
	int Esq, Dir;
	
	if ( !BSTempty( bst ) ) 
	{
		if ( !BSTisthere( bst, name ) ) printf("%s nao esta na BST!" , name);
		else 
		{
			NodeDelete = bst->Root;
			NodeDeleteBef = NULL;
			while ( NodeDelete != NULL )
			{
				if ( strcmp( name, NodeDelete->Key ) < 0 )
				{
					NodeDeleteBef = NodeDelete;
					NodeDelete = NodeDelete->Esq;
					Esq = 1;
					Dir = 0;
				}
				else if ( strcmp( name, NodeDelete->Key ) > 0 )
				{
					NodeDeleteBef = NodeDelete;
					NodeDelete = NodeDelete->Dir;
					Dir = 1;
					Esq = 0;
				}
				else break;
			}
			if ( NodeDelete->Esq == NULL && NodeDelete->Dir == NULL )
			{
				if ( Dir == 1) NodeDeleteBef->Dir = NULL;
				else NodeDeleteBef->Esq = NULL;
				NODEdestroy( NodeDelete );
			}
			else if ( ( NodeDelete->Esq == NULL && NodeDelete->Dir != NULL ) )
			{
				if ( Dir == 1 ) NodeDeleteBef->Dir = NodeDelete->Dir;
				else NodeDeleteBef->Esq = NodeDelete->Dir;
				NODEdestroy( NodeDelete );
			}
			else if ( ( NodeDelete->Dir == NULL && NodeDelete->Esq != NULL ) )
			{
				if ( Dir == 1 ) NodeDeleteBef->Esq = NodeDelete->Esq;
				else NodeDeleteBef->Esq = NodeDelete->Esq;
				NODEdestroy( NodeDelete );
			}
			else 
			{
				AuxNode = NodeDelete->Dir;
				AuxNodeBef = NULL;
				while ( AuxNode->Esq != NULL )
				{
					AuxNodeBef = AuxNode;
					AuxNode = AuxNode->Esq;
				}
				NodeDelete->Key = AuxNode->Key;
				if ( AuxNode->Dir != NULL ) AuxNodeBef->Esq = AuxNode->Dir;
				else AuxNodeBef->Esq = NULL;
				NODEdestroy( AuxNode);
			}		
		}
	}
}

void BSTNodeRemoveBook( pNode Node, char* Book )
{
	if ( Node != NULL ) 
	{
		LLremoveBook( Node->Occurence, Book );
		BSTNodeRemoveBook( Node->Esq, Book );
		BSTNodeRemoveBook( Node->Dir, Book );
	}
}

void BSTRemoveBook( BST bst, char* Book )
{
	if ( BSTempty( bst ) ) printf("BST Vazia!. \n");
	else BSTNodeRemoveBook( bst->Root, Book );
}

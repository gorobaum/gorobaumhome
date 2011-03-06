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

#ifndef TRIE_H_
#define TRIE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* pNode;
typedef struct trie* TRIE;

/*** Funcoes para NODES ***/
pNode NODEinit( int Index, int Pair );
void NODEput( pNode Node, pNode NewNode, int Binary );
int NODEpair( pNode Node );
int NODEindex( pNode Node );
void NODEdestroy( pNode Node );

/*** Funcoes para TRIES ***/
TRIE TRIEinit();
void TRIEdestroy( TRIE trie );
int TRIEempty( TRIE trie );
pNode TRIEroot ( TRIE trie );
pNode TRIEiterate( pNode Node, int Binary );

#endif

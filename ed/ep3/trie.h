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

/** Para maiores explicacoes das funcoes, leia os comentarios no arquivo .c 
	respectivo. **/

/*** Funcoes para NODES ***/
/* Funcao que inicia um novo no com as informacoes passadas */
pNode NODEinit( int Index, int Pair );
/* Funcao que coloca o no NewNode no Ramo correspondente ao Binary do no Node */
void NODEput( pNode Node, pNode NewNode, int Binary );
/* Essa funcao devolve o Par do no Node */
int NODEpair( pNode Node );
/* Essa funcao devolve o Indice do no Node */
int NODEindex( pNode Node );
/* Essa funcao desaloca a memoria do no recebido */
void NODEdestroy( pNode Node );

/*** Funcoes para TRIES ***/
/* Essa funcao inicia uma Trie, com algumas especificacoes do EP */
TRIE TRIEinit();
/* Essa funcao desaloca a memoria da Trie passada */
void TRIEdestroy( TRIE trie );
/* Essa funcao verifica se a Trie esta vazia */
int TRIEempty( TRIE trie );
/* Funcao que retorna a raiz da Trie */
pNode TRIEroot ( TRIE trie );
/* Funcao que itera sobre a Trie, ela retorna o no do ramo Binary do no Node. */
pNode TRIEiterate( pNode Node, int Binary );

#endif

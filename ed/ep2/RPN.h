/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/
#ifndef RPN_H_
#define RPN_H_

#include <stdio.h>
#include <stdlib.h>
#include "LL.h"
#include "BST.h"

typedef struct stack* Pilha;

LL STACKget( Pilha p );
/* Essa funcao retorna a lista ligada que esta no topo da pilha p e libera a
   memoria usada pelo Ramo que se encontrava no topo da pilha p. */
int STACKempty(Pilha p);
/* Funcao que verifica se a pilha esta vazia. */
void STACKrelivetop( Pilha p );
/* Funcao que retira o item do topo da pilha sem retorna-lo. */
void STACKput(Pilha p, LL l);
/* Funcao que coloca um item no topo da pilha. */
int STACKsize(Pilha p);
/* Funcao que devolve o tamanho da pilha. */
LL STACKpeek(Pilha p);
/* Funcao que devolve o topo da pilha. */
Pilha STACKinit(int N);
/* Funcao que inicializa uma pilha e devolve um ponteiro para a pilha iniciada. */
void STACKdestroy( Pilha p );
/* Funcao que retira uma pilha da memoria. */

#endif

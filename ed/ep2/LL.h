/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

06/05/2010

***********************************************************************************************************/

#ifndef LL_H_
#define LL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell* pCell;

typedef struct Linkedlist* LL;

pCell CELLinit();
/* Essa funcao aloca espaco na memoria para uma nova estrutura de nome CELL e re
   torna o apontador para este espaco alocado. */
LL LLinit();
/* Essa funcao aloca espaco na memoria para uma lista ligada e retorna o aponta
   dor para este espaco. */
int LLSize( LL l );
/* Essa funcao retorna o tamanho da lista ligada l. */
void LLput( LL l, char* book, int line, long int pLine );
/* Essa funcao coloca uma nova CELL com as informacoes book, line e pLine na lis
   ta ligada l. */
int LLempty( LL l );
/* Essa funcao retona 1 se a lista ligada l esta vazia e 0 caso contrario.*/
void LLremoveBook( LL l, char* book );
/* Essa funcao remove todas as CELL da lista ligada l que contenham o campo book
   igual ao parametro book passado. */
void LLdestroy ( LL l );
/* Essa funcao libera o espaco na memoria alocado para a lista ligada l. */
int Isthere( LL l , char* book, int line );
/* Essa funcao verifica se existe uma CELL com os campos book e line iguais aos
   parametros book e line passados. */
void LLprint( LL l, char* Book );
/* Essa funcao imprime todas as linhas continhas na lista ligada que sejam do
   livro passado por book. Caso book seja NULL, a funcao imprime toda a informacao
   da lista ligada. */
LL Junction( LL a, LL b );
/* Essa funcao retorna uma lista ligada resultando da unicao de a com b. */
LL Intersection( LL a, LL b );
/* Essa funcao retorna uma lista ligada resultando da interseccao de a com b. */
LL Difference( LL a, LL b);
/* Essa funcao retorna uma lista ligada resultando da diferenca de a com b. */

#endif

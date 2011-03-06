/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#ifndef BST_H_
#define BST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LL.h"

typedef struct node* pNode;
typedef struct bst*	 BST;

pNode NODEinit( char* name );
/* Essa funcao aloca espaco para um NODE e coloca name no seu campo Key. Ela re
   torna um apontador para o espaco alocado.*/
void NODEdestroy( pNode node );
/* Esta Funcao libera a memoria usada para alocar o NODE apontador por Node. */
BST BSTinit();
/* Essa funcao aloca espaco para uma BST. Ela retorna um ponteiro para o espaco 
   alocado. */
void BSTdestroy( BST bst );
/* Essa funcao libera o espaco alocado pela BST bst. Ela chama a funcao recusiva
   BSTremoveR, que libera o espaco alocado para todos os NODES da BST bst. */
int BSTempty( BST bst );
/* Essa funcao retorna 1 se a BST bst esta vazia e 0 caso contrario. */
int BSTisthere( BST bst, char* name );
/* Essa funcao retorna 1 se existe um NODE na BST bst com o campo Key igual a 
   name e zero caso contrario. */
pNode BSTsearch( BST bst, char* name );
/* Essa funcao retorna um apontador para a NODE que tenha o campo igual a name e
   esteja na BST bst. Se nao existe NODE com Key igual a name ela retorna NULL. */
LL BSTlinked( pNode Node );
/* Essa funcao retorna um apontador para a estrutura LL que se encontra no campo
   Occurence do NODE Node. */
void BSTAddNode( BST bst, char* name );
/* Essa funcao adiciona um NODE com campo Key na BST bst. */
void BSTPutInNode( BST bst, char* name, char* Book, int line, long int pLine );
/* Essa funcao coloca as informacoes Book, line e pLine no NODE que contenha
   o campo Key igual a name na BST bst. */
void BSTremove( BST bst, char* name );
/* Essa funcao remove o NODE com campo Key igual a name da BST bst. */
void BSTRemoveBook( BST bst, char* book );
/* Essa funcao percorre toda a BST bst retirando das listas ligadas no campo
   Occurence de cada NODE toda informacao sobre o livro book. */

#endif

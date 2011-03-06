/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BST.h"
#include "LL.h"
#include "RPN.h"

void AddBookToBst( BST bst, char* Book );
/* Essa funcao le caracter por caracter do arquivo passado por Book, reconhecendo
   palavras e a colocando na BST passada por bst. O algoritmo e case insensitive. */
void ToLowerCase( int Size, char* Word );
/* Essa funcao faz com que o String Word fique todo em letras minusculas. */
void Plus( Pilha p );
/* Essa funcao faz a unicao de dois conjuntos no topo da pilha p. */
void Except( Pilha p );
/* Essa funcao faz a interseccao de dois conjuntos no topo da pilha p. */
void Diff( Pilha p );
/* Essa funcao faz a diferenca de dois conjuntos no topo da pilha p. */

#endif

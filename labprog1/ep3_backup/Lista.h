/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Lista.h - Interface da lista ligada implementada como um tipo de primeira classe (yay Estrutura de Dados :D)
          Note que todos algoritmos usados nessa interface/implementacao de lista ligada sao iterativos.

Fernando Omar Aluani      #USP: 6797226

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/

#ifndef LIST_H
#define LIST_H

/*Definicao do tipo generalizado usado pela lista, e em algumas outras parte deste projeto.*/
typedef void* Item;

/* definicao do tipo da pilha/lista basico.*/
typedef struct list* S;

/* Principais funcoes para mexer com uma pilha/lista: */
S LISTinit();                                    /*Inicializa uma lista nova (parametro nao e' usado)*/
/*Esvazia a lista, chamando a funcao passada clearItem para para cada item (normalmente para dar free nele)*/
void LISTclear(S s, void (*clearItem)(Item d));
void LISTfree(S s, void (*clearItem)(Item d));   /*Libera totalmente a lista, alem de chamar LISTclear(s, clearItem) */


/* Funcoes para uso do S como uma Pilha.*/
void LISTpush(S s, Item d);
Item LISTpop(S s);

/* Funcoes para uso do S como uma lista ligada ordenada em ordem crescente, baseada na funcao de comparacao de items compareFunc
   passada como argumento. */
/*remove a primeira ocorrencia de um item da lista que seja considerado igual ao item D de acordo com a funcao de comparacao compareFunc
  retornando 1 caso a remocao foi bem sucedida, 0 caso contrario.
  A funcao clearItem passada, caso seja passada, e' usada para limpar o Item removido.*/
int LISTremove(S s, Item d, int (*compareFunc)(Item d1, Item d2), void (*clearItem)(Item d) );
/*Procura um item na lista que seja considerado igual a D de acordo com a funcao de comparacao compareFunc passada, retornando 1
  caso encontre um item, 0 caso contrario.*/
int LISTisItemIn(S s, Item d, int (*compareFunc)(Item d1, Item d2) );
/*Procura um item na lista que seja considerado igual a D de acordo com a funcao de comparacao compareFunc passada,
  retornando o item encontrado.*/
Item LISTgetItem(S s, Item d, int (*compareFunc)(Item d1, Item d2) );

/* Funcoes auxiliares para a lista/pilha S*/
int LISTempty(S s);             /*Retorna 1 caso a lista esteja vazia, 0 caso contrario.*/
int LISTcount(S s);             /*Retorna o numero de items em S.*/
/*Executa a funcao execForItem passada para cada item de S, passando como parametros o tal item da lista, e o item arg passado como
  argumento. Usados normalmente com uma funcao para imprimir um item, para que toda a lista S seja impressa.*/
void LISTdump(S s, void (*execForItem)(Item d, Item arg), Item arg );
#endif

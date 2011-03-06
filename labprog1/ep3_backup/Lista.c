/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Lista.c - Implementacao da lista ligada implementada como um tipo de primeira classe (yay Estrutura de Dados :D)
          Note que todos algoritmos usados nessa interface/implementacao de lista ligada sao iterativos.

Fernando Omar Aluani      #USP: 6797226

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/


/****************************************************
 Os includes basicos...
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"


/****************************************************
 Tipos/Structs da Pilha
*****************************************************/
/* Struct representando uma celula (node) da pilha. Ela contem o apontador para um Item e outro apontador para a proxima celula. */
typedef struct _listNode
{
	Item item;
	struct _listNode* next;
} listNode;

/* Implementacao da pilha - essa struct representa a pilha em si, contendo um contador de items nela e um apontador para a primeira
   celula da pilha. */
struct list
{
	struct _listNode* data;
	int count;
};


/****************************************************
 Funcoes Principais
*****************************************************/
/* Funcao para criar e inicalizar uma pilha.*/
S LISTinit()
{
    S s = malloc( sizeof(struct list) );
	s->data = NULL;
	s->count = 0;
	return s;
}

/* Funcao para limpar (ou esvaziar) uma pilha, tirando todos seus elementos, e liberando a memoria usada por eles, assim como
   chamar a funcao clearItem passada para limpar cada armazenado. */
void LISTclear(S s, void (*clearItem)(Item d))
{
    Item d;
    while ( LISTempty(s) == 0)
    {
        d = LISTpop(s);
        if (clearItem != NULL && d != NULL)
        {
            clearItem(d);
            d = NULL;
        }
    }
}

/* Funcao para deletar uma pilha - primeiro limpa seus elementos e depois deleta a propria pilha, liberando a memoria usada por tudo.
   A funcao clearItem passada e' usada para limpar cada item que estava armazenado na pilha. */
void LISTfree(S s, void (*clearItem)(Item d))
{
    if (s == NULL)
		return;

    LISTclear(s, clearItem);

    free(s);
}


/****************************************************
 Funcoes para uso de S como uma Pilha
*****************************************************/
/* Funcao para empilhar um item na pilha. */
void LISTpush(S s, Item d)
{
	listNode* ln = malloc( sizeof(listNode) );
	ln->item = d;
	ln->next = s->data;
	s->data = ln;
    s->count = s->count + 1;
}

/* Funcao para desempilhar um item da pilha, retornando-o. */
Item LISTpop(S s)
{
    listNode* ln;
    Item ret;

    if (s == NULL)
        return NULL;
	ln = s->data;
	if (ln == NULL)
        return NULL;
	ret = ln->item;
	s->data = ln->next;
	free(ln);
	s->count = s->count - 1;
	return ret;
}


/****************************************************
 Funcoes para uso de S como uma lista ligada ordenada
*****************************************************/
/*remove a primeira ocorrencia de um item da lista que seja considerado igual ao item D de acordo com a funcao de comparacao compareFunc
  retornando 1 caso a remocao foi bem sucedida, 0 caso contrario.
  A funcao clearItem passada, caso seja passada, e' usada para limpar o Item removido.*/
int LISTremove(S s, Item d, int (*compareFunc)(Item d1, Item d2), void (*clearItem)(Item d) )
{
    listNode* node;
    listNode* prev;
    int result;

    prev = NULL;
    node = s->data;
    while (node != NULL)
    {
        result = compareFunc(d, node->item);

        if ( result == 0) /*significa que d = node, portanto, temos que remove-lo.*/
        {
            if (prev == NULL) /*tamo removendo o primeiro item da lista*/
                s->data = node->next;
            else              /*node esta no meio da lista.*/
                prev->next = node->next;

            if (clearItem != NULL)  /*chamamos a funcao de limpeza caso ela tenha sido passada.*/
            {
                clearItem( node->item );
                node->item = NULL;
            }
            free(node);
            s->count = s->count - 1;
            return 1;
        }

        prev = node;
        node = node->next;
    }
    return 0;
}

/*Procura um item na lista que seja considerado igual a D de acordo com a funcao de comparacao compareFunc passada, retornando 1
  caso encontre um item, 0 caso contrario.*/
int LISTisItemIn(S s, Item d, int (*compareFunc)(Item d1, Item d2) )
{
    listNode* node = s->data;
    if (d == NULL)
        return 0;

    while (node != NULL)
    {
        if ( compareFunc(d, node->item) == 0) /*significa que d = node, portanto, d existe no conjunto.*/
            return 1;

        node = node->next;
    }
    return 0;
}

/*Procura um item na lista que seja considerado igual a D de acordo com a funcao de comparacao compareFunc passada,
  retornando o item encontrado.*/
Item LISTgetItem(S s, Item d, int (*compareFunc)(Item d1, Item d2) )
{
    listNode* node = s->data;

    if (d == NULL)
        return NULL;

    while (node != NULL)
    {
        if ( compareFunc(d, node->item) == 0) /*significa que d = item do node, portanto, achamos o item.*/
            return node->item;

        node = node->next;
    }
    return NULL;
}


/****************************************************
 Funcoes Auxiliares
*****************************************************/
/* Checa se a pilha esta vazia, retornando 1 caso esteja, 0 se tiver um ou mais items. */
int LISTempty(S s)
{
	if (s == NULL)
		return 1;
	if ( s->count == 0)
		return 1;
	return 0;
}

/* Funcao para retornar o numero de elementos em S. */
int LISTcount(S s)
{
	if (s == NULL)
		return 0;
	return s->count;
}

/*Executa a funcao execForItem passada para cada item de S, passando como parametros o tal item da lista,
  e o item extra passado como argumento.*/
void LISTdump(S s, void (*execForItem)(Item d, Item arg), Item arg )
{
    listNode *ln, *node;
    ln = s->data;

    while (ln != NULL)
    {
        node = ln;
        ln = ln->next;
        execForItem( node->item, arg );
    }
}

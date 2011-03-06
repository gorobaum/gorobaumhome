/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Bote.h - interface do tipo Bote, uma variacao de entidade.
          C nao e' orientado a objetos, mas implementamos um sistema de gerenciamento das entidades
          que faz com que seja bem parecido com OO.
          Assim, podemos dizer que um Bote e' praticamente uma derivacao do tipo basico de uma entidade.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/

#ifndef BOTE_H
#define BOTE_H

#include "Entity.h"
/*Funcoes Principais dessa Interface.*/
void inicializaBotes(); /*Inicializa esse modulo.*/
void terminaBotes();    /*Termina esse modulo, liberando toda memoria usada por ele.*/

/*Funcoes Principais sobre um Bote.*/

/*Cria uma Bote (uma entidade) nova com os parametros passados.*/
Entity criaBote(Vetor pos, Vetor vel);

/*Funcoes Auxiliares.*/
/*Altera a probabilidade da matriz de transicao usada pelos Botes pra mudar de direcao, indo do estado
  antigo para o estado novo, usando a probabilidade prob (entre 0 e 1) passada.
  Note que e' preciso cuidado ao usar essa funcao para que nao 'estrague' a matriz de transicao.*/
void setProbDeMudancaDeEstadoBote(int estadoAntigo, int estadoNovo, double prob);
unsigned int getRaioBote(int Base, int Altura); /*Calcula o raio de um Bote com a base e altura passados.*/
short isBote(Entity ent); /*Checa se a entidade e' um Bote, retornando 1 se for, 0 caso contrario.*/
int getNumBotesVivos();   /*Retorna o numero de Botes atualmente vivos.*/

#endif

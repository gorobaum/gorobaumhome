/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Passageiro.h - interface do tipo passageiro, uma variacao de entidade.
               C nao e' orientado a objetos, mas implementamos um sistema de gerenciamento das entidades
               que faz com que seja bem parecido com OO.
               Assim, podemos dizer que um Passageiro e' praticamente uma derivacao do tipo basico de uma entidade.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/


#ifndef PASSAGEIRO
#define PASSAGEIRO

#include "Entity.h"

/*Funcoes Principais dessa Interface.*/
void inicializaPassageiros(); /*Inicializa esse modulo.*/
void terminaPassageiros();    /*Termina esse modulo, liberando toda memoria usada por ele.*/

/*Funcoes Principais sobre um Passageiro.*/

/*Altera a direcao do vetor velocidade passado de acordo com o estado (como usado pela cadeia de Markov) passado.
  o estado pode ser qualquer i em {0, 1, 2, 3, 4, 5, 6, 7}
  Onde cada estado quer dizer:
  0=Norte; 1=Sul; 2=Leste; 3=Oeste; 4=Nordeste; 5=Sudeste; 6=Noroeste; 7=Sudoeste.*/
void setEstado(int estado, Vetor vel);
/*Cria uma passageiro (uma entidade) nova com os parametros passados.*/
Entity criaPassageiro(Vetor pos, Vetor vel, int mass);

/*Funcoes Auxiliares.*/
/*Altera a probabilidade da matriz de transicao usada pelos passageiros pra mudar de direcao, indo do estado
  antigo para o estado novo, usando a probabilidade prob (entre 0 e 1) passada.
  Note que e' preciso cuidado ao usar essa funcao para que nao 'estrague' a matriz de transicao.*/
void setProbDeMudancaDeEstado(int estadoAntigo, int estadoNovo, double prob);
short isPassageiro(Entity ent); /*Checa se a entidade e' um passageiro, retornando 1 se for, 0 caso contrario.*/
int getNumPassageirosVivos();   /*Retorna o numero de passageiros atualmente vivos.*/

#endif


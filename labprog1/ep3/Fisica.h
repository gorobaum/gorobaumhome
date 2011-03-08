/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Fisica.h - interface das funcoes de fisica.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/

#ifndef FISICA
#define FISICA

/*Definicao dos tipos implementados pela interface de fisica.*/
/*Representa um vetor 2D no plano cartesiano R2.
  Note que o vetor representa diretamente um ponto na tela, em pixels, mesmo sendo que pixels sao valores inteiros
  e o vetor usa doubles. Usamos doubles para manter precisao em calculos (principalmente nos fisicos), e fazemos um
  simples arredondamento para o int mais proximo ao passar o vetor para as funcoes da biblioteca que usam pixels como ints.*/
typedef struct vetor* Vetor;
typedef struct colisao* Colisao;  /*Struct usada para auxiliar na checagem de colisoes, contendo informacoes pertinentes.*/

#include "Entity.h"

/*Funcoes Relativas a Vetores.*/
Vetor VETORinit(double x, double y);   /*Inicializa e retorna um vetor novo com os valores passados.*/
double getX(Vetor v);                  /*Retorna a componente X do vetor passado.*/
double getY(Vetor v);                  /*Retorna a componente Y do vetor passado.*/
void setX( Vetor v, double newX );     /*Altera o valor do componente X do vetor passado, com o novo valor dado.*/
void setY( Vetor v, double newY );     /*Altera o valor do componente Y do vetor passado, com o novo valor dado.*/
double VETORmodulo( Vetor v );         /*Retorna o modulo do vetor dado.*/
double CalcDist( Vetor v1, Vetor v2 ); /*Retorna a distancia entre os 2 vetores passados.*/
void VETORadd(Vetor A, Vetor B);       /*Soma o vetor B no vetor A.*/
void VETORsubtract(Vetor A, Vetor B);  /*Subtrai o vetor B do vetor A.*/
double VETORprodutoInterno(Vetor A, Vetor B); /*Calcula o produto interno (escalar) entre dois vetores.*/
void VETORscale(Vetor v, double f);    /*Multiplica o vetor por um valor escalar.*/
void VETORnormalize(Vetor v);          /*Normaliza o vetor passado.*/
int round(double x);                   /*Arredonda o double passado para o inteiro mais proximo.*/

/*Funcoes Relativas ao posicionamento e velocidade de entidades.*/
/*Atualiza a posicao da entidade de acordo com sua variacao de movimento (dada pela velocidade e variacao de tempo DeltaTime).*/
void atualizaPosicao( Entity ent, double DeltaTime );
/*Funcao para "colidir" duas entidades, corrigindo suas velocidades de acordo com suas velocidades anteriores, massa
  e coeficiente de restituicao da colisao (passado como argumento - CoefRest, devendo estar enter 0 e 1). */
void atualizaVelocidade( Entity ent1, Entity ent2, double CoefRest );

/*Funcoes Relativas a Colisao.
  Realiza o teste geral de colisao, checando todas entidades vivas para ver se elas estao colidindo.
  Se estiverem, seta que elas estao colidindo e atualiza suas velocidades de acordo.
  Notando que o tipo de colisao e' aleatorio. O coeficiente de restituicao da colisao e' calculado aleatoriamente,
  com uma chance maior (definida pela constante CHANCE_REST no Fisica.c) de ser uma colisao elastica.*/
void colisaoGeral( double DeltaTime );

#endif

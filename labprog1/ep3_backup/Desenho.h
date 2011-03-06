/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Desenho.h - interface das rotinas para desenho do jogo.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/


#ifndef DESENHO
#define DESENHO

#include "Fisica.h"


/*Funcoes Principais da Interface: */
void inicializaDesenho(); /*Inicializa a interface e seus atributos.*/
void terminaDesenho();    /*Fecha a interface, liberando toda a memoria por ela usada.*/

/*Funcoes principais para cada ciclo de update grafico: */
/*Funcao para prepara a interface para um novo ciclo de desenho.*/
void preparaPraDesenho();
/*Funcao principal para desenhar os graficos na tela.
  Como usamos double-buffering, todo o desenho real das entidades e etc e' feito numa memoria separada (num buffer),
  e com essa funcao esse buffer e' desenhado de uma vez so' na tela.*/
void updateScreen();

/* Funcoes de desenho de formas geometricas: */
/*Desenha um circulo cheio na tela, com centro na posicao passada, com raio e cor passados.*/
void drawCircle(Vetor pos, int raio, unsigned long cor);
/*Desenha um triangulo isosceles cheio com a cor passada na tela, com seu centro na posicao dada pelo vetor pos,
  direcionado de acordo com o vetor dir passado (logo a base do vetor fica perpendicularmente na direcao contraria),
  de acordo com a altura e base passados. */
void drawTriangle(Vetor pos, Vetor dir, int base, int altura, unsigned long cor);
/*Desenha um retangulo cheio na tela, com base, altura e cor passados, centrado na posicao dada.*/
void drawRect(Vetor pos, int base, int altura, unsigned long cor);

/*Funcoes Auxiliares: */
/*Testa as duas entidades passadas para ver se seus desenhos estao em cima um do outro, isto e', se a interseccao
  das suas formas e' diferente de nulo.
  Assim essa funcao pode ser usada para detectar colisao por pixel entre as duas entidades.*/
short checkIntersecaoDeFormas(Entity e1, Entity e2);
/*Funcao auxiliar para transformar um valor RGB num inteiro representando uma cor (como o Allegro usa).
  E' um simples wrapper para uma funcao do Allegro, porem nao quero ter q incluir o Desenho.h e o Allegro em varios
  arquivos, so' por causa dessa funcao, portanto aqui estamos...*/
unsigned long makecolor(short R, short G, short B);

#endif


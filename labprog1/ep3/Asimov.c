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

/****************************************************
 Os includes basicos...
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Asimov.h"
#include "Lista.h"
#include "Entity.h"
#include "Desenho.h"
#include "Fisica.h"

/****************************************************
 Atributos, Constantes e Variaveis Globais
*****************************************************/

#define ASIMOV_POS_X 512
#define ASIMOV_POS_Y 768/2
#define ASIMOV_MASS 2000
#define ASIMOV_ALTURA 42
#define ASIMOV_BASE 256


/****************************************************
 Funcoes Internas
*****************************************************/
/*Funcao importante usada internamente. Ela executa um update logico do Asimov.*/
void updateAsimov(Entity ent, double deltaTime)
{
    Vetor vel;

    /*E pra ter certeza que continuaremos parados:*/
    vel = getVelocidade(ent);
    setX(vel, 0);
    setY(vel, 0);
}

/*Funcao importante usada internamente. Ela executa o update grafico do Asimov no jogo.*/
void drawAsimov(Entity ent)
{
    Vetor pos = getPosicao(ent);

    drawRect(pos, (Rect)getData(ent), getColor(ent));
}

/*Funcao importante usada internamente. Ela trata a colisao entre as entidades ent e aux, levando em conta a variacao de tempo.
  Note que enquanto ela trata a colisao de ambas entidades, fazendo o necessario, ela e' executada e funciona do ponto de vista
  da entidade ENT, que pode ser assumida um Asimov nessa funcao (nesse contexto).*/
void colisaoAsimov(Entity ent, Entity aux, double deltaTime)
{
    /*Nao precisamos tratar a colisao nos mesmos, as outras entidades o farao.
      Lembrando que como o Asimov deve ficar sempre parado, nao devemos colidir com a parede...
      Mas e' sempre bom prevenir a remediar :P*/
    if (aux != NULL)
        callColidiuCom(aux, ent, deltaTime);
}

/****************************************************
 Funcoes Principais (Asimov)
*****************************************************/
/*Cria o Asimov baseado nos defines do arquivo. */
Entity criaAsimov()
{
    Entity ent;
    Rect Medidas;
    Vetor pos, vel;
	unsigned long cor, raio;

	Medidas = criaRect(ASIMOV_BASE, ASIMOV_ALTURA);
	raio = getRaioAsimov( ASIMOV_BASE, ASIMOV_ALTURA );

	pos = VETORinit( ASIMOV_POS_X, ASIMOV_POS_Y );
	vel = VETORinit( 0 , 0 );
	cor = makecolor( 250, 90, 90);

    ent = criaEntidade(pos, vel, ASIMOV_MASS, Medidas, raio, ASIMOV, cor, updateAsimov, drawAsimov, colisaoAsimov, clearSimpleData );

    return ent;
}


/****************************************************
 Funcoes Auxiliares
*****************************************************/
/*Calcula o raio de um Asimov de base e altura passados.*/
unsigned int getRaioAsimov( int Base, int Altura )/*TESTAR*/
{
	unsigned int Raio = 0;

    /*Raio circunscrito de um retangulo pegamos com um simples pitagoras...*/
	Raio = round(  sqrt((Base*Base/4) + (Altura*Altura/4)) );

	return Raio;
}

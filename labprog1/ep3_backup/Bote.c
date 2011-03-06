/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Barco.c - implementacao do tipo Barco, uma variacao de entidade.
          C nao e' orientado a objetos, mas implementamos um sistema de gerenciamento das entidades
          que faz com que seja bem parecido com OO.
          Assim, podemos dizer que um Barco e' praticamente uma derivacao do tipo basico de uma entidade.

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
#include "Lista.h"
#include "Entity.h"
#include "Desenho.h"
#include "Fisica.h"
#include "Estat.h"
#include "Barco.h"

/****************************************************
 Atributos, Constantes e Variaveis Globais
*****************************************************/
#define CHANCE_REST 65.0
#define BOTE_MASS 300
#define BOTE_ALTURA 12
#define BOTE_BASE 10

struct _itembote {
        int base;
        int altura;
}

double** markovTransicao;  /*Matriz de transicao para a cadeia de Markov usada pelos Barcos.*/

/****************************************************
 Funcoes Internas
*****************************************************/
/*Funcao auxiliar usada internamente para retornar o estado de um Barco de acordo com o vetor velocidade dele passado.
  O estado representa para que direcao o Barco esta se movendo:
  0=Norte; 1=Sul; 2=Leste; 3=Oeste; 4=Nordeste; 5=Sudeste; 6=Noroeste; 7=Sudoeste.
  Ou retorna -1 caso nao tenha sido possivel determinar a direcao.*/
int getEstado(Vetor vel)
{
    int x, y;

	if (vel == NULL)
		return -1;
	x = y = 0;

    x = round(getX(vel));
    y = round(getY(vel));

	if (x != 0)
		x /= abs(x);
	if (y != 0)
		y /= abs(y);

    if (x == 0 && y == -1)   /*norte*/
        return 0;
    else if (x == 0 && y == 1)  /*sul*/
        return 1;
    else if (x == 1 && y == 0)   /*leste*/
        return 2;
    else if (x == -1 && y == 0)  /*oeste*/
        return 3;
    else if (x == 1 && y == -1)   /*nordeste*/
        return 4;
    else if (x == 1 && y == 1)  /*sudeste*/
        return 5;
    else if (x == -1 && y == -1)  /*noroeste*/
        return 6;
    else if (x == -1 && y == 1) /*sudoeste*/
        return 7;

	return -1;
}

/*Altera a direcao do vetor velocidade passado de acordo com o estado (como usado pela cadeia de Markov) passado.
  o estado pode ser qualquer i em {0, 1, 2, 3, 4, 5, 6, 7}
  Onde cada estado quer dizer:
  0=Norte; 1=Sul; 2=Leste; 3=Oeste; 4=Nordeste; 5=Sudeste; 6=Noroeste; 7=Sudoeste.*/
void setEstado(int estado, Vetor vel)
{
    /*Lembrando que apenas alteramos a direcao da velocidade. Temos que manter seu modulo.*/
    double m = VETORmodulo(vel);
    if (m == 0)
        return;
        return;

    if (estado == 0)       /*norte*/
	{
		setX(vel, 0);
		setY(vel, -m );
	}
    else if (estado == 1)  /*sul*/
	{
		setX(vel, 0);
		setY(vel, m );
	}
    else if (estado == 2)  /*leste*/
	{
		setX(vel, m );
		setY(vel, 0);
	}
    else if (estado == 3)  /*oeste*/
	{
		setX(vel, -m );
		setY(vel, 0);
	}
    else if (estado == 4)  /*nordeste*/
	{
		setX(vel, sqrt(pow(m,2)/2)  );
		setY(vel, -sqrt(pow(m,2)/2) );
	}
    else if (estado == 5)  /*sudeste*/
	{
		setX(vel, sqrt(pow(m,2)/2) );
		setY(vel, sqrt(pow(m,2)/2) );
	}
    else if (estado == 6)  /*noroeste*/
	{
		setX(vel, -sqrt(pow(m,2)/2)  );
		setY(vel, -sqrt(pow(m,2)/2)  );
	}
    else if (estado == 7)  /*sudoeste*/
	{
		setX(vel, -sqrt(pow(m,2)/2) );
		setY(vel, sqrt(pow(m,2)/2)  );
	}
}

/*Funcao importante usada internamente. Ela executa um update logico de um Barco.*/
void updateBarco(Entity ent, double deltaTime)
{
	int estado;
	Vetor v;

    atualizaPosicao(ent, deltaTime);  /*atualizamos nossa posicao de acordo com a velocidade e variacao do tempo.*/

    /*Se nao estivermos colidindo podemos tentar mudar nossa direcao de movimento de acordo */
    if ( !getEstaColidindo(ent) )
    {
        v = getVelocidade(ent);
        estado = getEstado(v);

        if (estado != -1)
        {
            /*E tentamos mudar nosso estado de acordo com uma cadeia de markov...*/
            estado = markovProximoEstado(estado, 8, markovTransicao);
            setEstado(estado, v);
        }
    }
}

/*Funcao importante usada internamente. Ela executa o update grafico do Barco no jogo.*/
void drawBarco(Entity ent)
{
    Vetor pos = getPosicao(ent);
    drawTriangle(pos, getVelocidade(ent), round(sqrt(7*getRaio(ent)*getRaio(ent)/4)), round((double)getRaio(ent)*3/2.0), getColor(ent));
}

/*Funcao importante usada internamente. Ela trata a colisao entre as entidades ent e aux, levando em conta a variacao de tempo.
  Note que enquanto ela trata a colisao de ambas entidades, fazendo o necessario, ela e' executada e funciona do ponto de vista
  da entidade ENT, que pode ser assumida um Barco nessa funcao (nesse contexto).*/
void colisaoBarco(Entity ent, Entity aux, double deltaTime)
{
    double x;

    if (aux == NULL || isCoral(aux) == 1 || isAsimov(aux) == 1)
    {
	    return;
    }
    else if ( isBarco(aux) == 1)
    {
        /*Colisao entre Barcos, colisao simples, basta acertar as velocidades.*/
        x = 1.0;

        atualizaVelocidade( ent, aux, x );
    }
    else if ( isPassageiro(aux) == 1 )
    {
        recolhePassageiro( aux );
    }
}

/*Funcao importante usada internamente. Chamada quando um Barco e' destruido, ela delata a parte especifica a um Barco
  da entidade (a data da entidade).*/
void clearBoteData(Item data)
{
    free(data);
}


/****************************************************
 Funcoes Principais da Interface
*****************************************************/
/*Inicializa essa interface, criando a matriz de transicao da cadeia de markov usada pelos Barcos.*/
void inicializaBarcos()
{
    int i, j;

    markovTransicao = malloc( 8*sizeof(double*) );
    for (i=0; i<8; i++)
        markovTransicao[i] = malloc( 8*sizeof(double) );

    for (i=0; i<8; i++)
    {
        for (j=0; j<8; j++)
        {
            if (i == j)
                markovTransicao[i][j] = 1.0;
            else
                markovTransicao[i][j] = 0.0;

            if (i == j)
                markovTransicao[i][j] = 0.65;
            else
                markovTransicao[i][j] = 0.05;
        }
    }
}

/*Termina essa interface, deletando tudo dela e liberando a memoria usada aqui.*/
void terminaBarcos()
{
    int i;
    for (i=0; i<8; i++)
        free(markovTransicao[i]);
    free(markovTransicao);
}


/****************************************************
 Funcoes Principais (Barco)
*****************************************************/
/*Cria um Barco novo com os parametros passados. */
Entity criaBarco(Vetor pos, Vetor vel )
{
    Entity ent;
    ItemBote Medidas;
    unsigned long cor;

    Medidas = malloc(sizeof(_itembote));

	Medidas->Base = BOTE_BASE;
	Medidas->Altura = BOTE_ALTURA;

    /*Calculamos o raio do Barco, que e' tido como uma forma circular, e a cor, para entao criar ele...*/
	cor = makecolor( 250, 90, 90);

    ent = criaEntidade(pos, vel, BOTE_MASSA, Medidas, BOTE_ALTURA, BOTE, cor, updateBarco, drawBarco, colisaoBarco, clearBoteData );

    return ent;
}


/****************************************************
 Funcoes Auxiliares
*****************************************************/
/*Altera a probabilidade da matriz de transicao usada pelos Barcos pra mudar de direcao, indo do estado
  antigo para o estado novo, usando a probabilidade prob (entre 0 e 1) passada.
  Note que e' preciso cuidado ao usar essa funcao para que nao 'estrague' a matriz de transicao.*/
void setProbDeMudancaDeEstado(int estadoAntigo, int estadoNovo, double prob)
{
    if (estadoAntigo < 0 || estadoAntigo >= 8 || estadoNovo < 0 || estadoNovo >= 8)
        return;
    markovTransicao[estadoAntigo][estadoNovo] = prob;
}

/*Checa se a entidade passada e' um Barco, retornando 1 se for, 0 caso contrario.
  Para isso simplesmente checamos se a ID da entidade consta na nossa lista de IDs de Barcos.*/
short isBarco(Entity ent)
{
	return getTipo(ent) == BOTE;
}

/*Funcao auxiliar usada internamente pela getNumBarcosVivos(), para aumentar um contador
  para cada entidade viva que seja um Barco.*/
void _checkBarcoVivo(Item ent_i, Item arg)
{
    int* count;
    Entity ent;

    ent = (Entity)ent_i;
    count = (int*)arg;

    if ( isBarco(ent) )
        *count = *count + 1;
}

/*Funcao auxiliar para retornar o numero de Barcos atualmente vivos no jogo.*/
int getNumBarcosVivos()
{
    int count;

    count = 0;
    executeForAllEntities(_checkBarcoVivo, &count );
    return count;
}


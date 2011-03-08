/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Bote.c - implementacao do tipo Bote, uma variacao de entidade.
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
#include "Lista.h"
#include "Entity.h"
#include "Desenho.h"
#include "Fisica.h"
#include "Estat.h"
#include "Bote.h"

/****************************************************
 Atributos, Constantes e Variaveis Globais
*****************************************************/
#define CHANCE_REST 65.0
#define BOTE_MASS 300
#define BOTE_ALTURA 40
#define BOTE_BASE 32
#define CHANCE_ENCALHAR 0.3

double** markovTransicaoBote;  /*Matriz de transicao para a cadeia de Markov usada pelos Botes.*/

/****************************************************
 Funcoes Internas
*****************************************************/
/*Funcao auxiliar usada internamente para retornar o estado de um Bote de acordo com o vetor velocidade dele passado.
  O estado representa para que direcao o Bote esta se movendo:
  0=Norte; 1=Sul; 2=Leste; 3=Oeste; 4=Nordeste; 5=Sudeste; 6=Noroeste; 7=Sudoeste.
  Ou retorna -1 caso nao tenha sido possivel determinar a direcao.*/
int getBoteEstado(Vetor vel)
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
void setBoteEstado(int estado, Vetor vel)
{
    /*Lembrando que apenas alteramos a direcao da velocidade. Temos que manter seu modulo.*/
    double m = VETORmodulo(vel);
    if (m == 0)
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

/*Funcao importante usada internamente. Ela executa um update logico de um Bote.*/
void updateBote(Entity ent, double deltaTime)
{
	int estado, estadoAntigo;
	Vetor v;

    atualizaPosicao(ent, deltaTime);  /*atualizamos nossa posicao de acordo com a velocidade e variacao do tempo.*/

    /*Se nao estivermos colidindo podemos tentar mudar nossa direcao de movimento de acordo */
    if ( !getEstaColidindo(ent) )
    {
        v = getVelocidade(ent);
        estadoAntigo = getBoteEstado(v);

        if (estadoAntigo != -1)
        {
            /*E tentamos mudar nosso estado de acordo com uma cadeia de markov...*/
            estado = markovProximoEstado(estadoAntigo, 8, markovTransicaoBote);
            if (estado != estadoAntigo)
                setBoteEstado(estado, v);
        }
    }
}

/*Funcao importante usada internamente. Ela executa o update grafico do Bote no jogo.*/
void drawBote(Entity ent)
{
    Vetor pos = getPosicao(ent);

    drawTriangle(pos, getVelocidade(ent), (Rect)getData(ent), getColor(ent));
}


/*Funcao importante usada internamente. Ela trata a colisao entre as entidades ent e aux, levando em conta a variacao de tempo.
  Note que enquanto ela trata a colisao de ambas entidades, fazendo o necessario, ela e' executada e funciona do ponto de vista
  da entidade ENT, que pode ser assumida um Bote nessa funcao (nesse contexto).*/
void colisaoBote(Entity ent, Entity aux, double deltaTime)
{
    if (aux == NULL) /*TESTAR*/
    {
    	calculaDirecaoColisaoParede(ent);
	    return;
    }
    else if ( getTipo(aux) == RECIFE )
    {
    	if ( checkChance( CHANCE_ENCALHAR )  )
        {
            /*Bote encalhou... Deve ser reinicializado na borda da tela, com velocidade/direcao novas.
              Por enquanto, simplesmente deletamos ele. O loop do jogo (no Naufrago) tomara conta de recria-lo.
              Porem se quisermos fazer algum efeito ou codigo extra nesse caso, aqui e' o lugar.*/
            setEntityToBeDestroyed( ent );
        }
    	else
            calculaDirecoesColisao(ent, aux);
    }
    else if ( isBote(aux) == 1 || getTipo(aux) == ASIMOV)
    {
        /*Colisao entre Botes ou Bote->Asimov, colisao simples, basta acertar as velocidades.*/
        atualizaVelocidade( ent, aux, 1.0 );
    }
    else if ( getTipo(aux) == PASS )
    {
        setEntityToBeDestroyed( aux );
        /*aqui este bote (ent) recolheu o passageiro (aux).
          Por enquanto nao fazemos nada mais, mas se necessario, adicionar extras aqui, como aumentar um contador de
          passageiros pegos, aumentar a massa do bote, etc.*/
    }
}



/****************************************************
 Funcoes Principais da Interface
*****************************************************/
/*Inicializa essa interface, criando a matriz de transicao da cadeia de markov usada pelos Botes.*/
void inicializaBotes()
{
    int i, j;

    markovTransicaoBote = malloc( 8*sizeof(double*) );
    for (i=0; i<8; i++)
        markovTransicaoBote[i] = malloc( 8*sizeof(double) );

    for (i=0; i<8; i++)
    {
        for (j=0; j<8; j++)
        {
            if (i == j)
                markovTransicaoBote[i][j] = 1.0;
            else
                markovTransicaoBote[i][j] = 0.0;
        }
    }
}


/*Termina essa interface, deletando tudo dela e liberando a memoria usada aqui.*/
void terminaBotes()
{
    int i;
    for (i=0; i<8; i++)
        free(markovTransicaoBote[i]);
    free(markovTransicaoBote);
}


/****************************************************
 Funcoes Principais (Bote)
*****************************************************/
/*Cria um Bote novo com os parametros passados. */
Entity criaBote( Vetor pos, Vetor vel )/*TESTAR*/
{
    Entity ent;
    Rect Medidas;
	unsigned long cor, raio;

	Medidas = criaRect(BOTE_BASE, BOTE_ALTURA);

	raio = getRaioBote( BOTE_BASE, BOTE_ALTURA );
	cor = makecolor( 250, 90, 90);

    ent = criaEntidade(pos, vel, BOTE_MASS, Medidas, raio, BOTE, cor, updateBote, drawBote, colisaoBote, clearSimpleData );

    return ent;
}


/****************************************************
 Funcoes Auxiliares
*****************************************************/
/*Altera a probabilidade da matriz de transicao usada pelos Botes pra mudar de direcao, indo do estado
  antigo para o estado novo, usando a probabilidade prob (entre 0 e 1) passada.
  Note que e' preciso cuidado ao usar essa funcao para que nao 'estrague' a matriz de transicao.*/
void setProbDeMudancaDeEstadoBote(int estadoAntigo, int estadoNovo, double prob)
{
    if (estadoAntigo < 0 || estadoAntigo >= 8 || estadoNovo < 0 || estadoNovo >= 8)
        return;
    markovTransicaoBote[estadoAntigo][estadoNovo] = prob;
}

/*Calcula o raio de um Bote com a base e altura passados.*/
unsigned int getRaioBote( int Base, int Altura )/*TESTAR*/
{
	int Lado = 0;
	unsigned int Raio = 0;

	Lado = sqrt( pow( Base/2, 2 ) + pow( Altura, 2 ) );
	Raio = ( 2*Lado*Lado) / ( sqrt( ( Lado + Lado + Base )*( Lado + Lado - Base ) ) );
	Raio /= 2;

	return Raio;
}

/*Checa se a entidade passada e' um Bote, retornando 1 se for, 0 caso contrario.
  Para isso simplesmente checamos se a ID da entidade consta na nossa lista de IDs de Botes.*/
short isBote(Entity ent)
{
	return getTipo(ent) == BOTE;
}

/*Funcao auxiliar usada internamente pela getNumBotesVivos(), para aumentar um contador
  para cada entidade viva que seja um Bote.*/
void _checkBoteVivo(Item ent_i, Item arg)
{
    int* count;
    Entity ent;

    ent = (Entity)ent_i;
    count = (int*)arg;

    if ( isBote(ent) )
        *count = *count + 1;
}

/*Funcao auxiliar para retornar o numero de Botes atualmente vivos no jogo.*/
int getNumBotesVivos()
{
    int count;

    count = 0;
    executeForAllEntities(_checkBoteVivo, &count );
    return count;
}

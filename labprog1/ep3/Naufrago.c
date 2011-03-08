/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Naufrago.c - arquivo principal do jogo.

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
#include <time.h>
#include <allegro.h>
#include "Entity.h"
#include "Desenho.h"
#include "Config.h"
#include "Passageiro.h"
#include "Bote.h"
#include "Asimov.h"
#include "Estat.h"


/****************************************************
  Atributos e Variaveis Globais
*****************************************************/
/*Valor usado pelo updateGameLogic para marcar tempo passado (em segundos).*/
double timeElapsed = 0.0;

/****************************************************
 Funcoes Principais
*****************************************************/
/*Funcao de update logico do proprio jogo. E' executada em cada ciclo apos a checagem de colisao, antes
  do update logico das entidades do jogo.*/
void updateGameLogic(double deltaTime)
{
    int i, estadoInicial, posInicial, numVivos;
    Vetor v, p;

	/*Antes temos que criar os dois botes, sempre que der.*/
	while ( (2 - getNumBotesVivos()) > 0 ) 
	{
		/*Apenas criamos o vetor e setamos apenas 1 de suas coordenadas (a outra = 0). Assim esse valor que estamos setando
          sera igual ao modulo do vetor, que queremos que seja um numero especifico dependendo das configuracoes.
          Depois iremos atualizar (para variar) a direcao, e somente a direcao, da velocidade.*/
        v = VETORinit(getSpeed() + (getRandDouble()*10 ), 0);
		/*Inicializamos a posicao com um valor fora da tela, para que no teste a seguir nao haja nenhuma entidade para que possamos
		  criar uma.*/
		p = VETORinit(-30.0, -30.0);

        /*Agora escolhemos uma posicao aleatoria ao longo das bordas do oceano para criar o bote,
          e atualizamos a sua direcao para eles comecarem se mexendo para algum lado.*/
		while ( getEntityByPositionVector(p) != NULL || getX(p) < 0)
		{
			posInicial = rand()%4;
    	    estadoInicial = rand()%2;

	        if (posInicial == 0)
    	    {
    	    	setX(p, rand()%SCREEN_W);
				setY(p, 10);
    	        if (estadoInicial == 0)
					setEstado(7, v);
				else if (estadoInicial == 1)
					setEstado(5, v);
			}
			else if (posInicial == 1)
    	    {
				setX(p, 0);
				setY(p, rand()%SCREEN_H);
				if (estadoInicial == 0)
					setEstado(4, v);
				else if (estadoInicial == 1)
					setEstado(5, v);
			}
			else if (posInicial == 2)
    	    {
				setX(p, rand()%SCREEN_W);
				setY(p, SCREEN_H-1);
				if (estadoInicial == 0)
					setEstado(6, v);
				else if (estadoInicial == 1)
					setEstado(4, v);
			}
			else if (posInicial == 3)
    	    {
				setX(p, SCREEN_W-1);
				setY(p, rand()%SCREEN_H);
    	        if (estadoInicial == 0)
					setEstado(6, v);
				else if (estadoInicial == 1)
					setEstado(7, v);
    		}
		}
        /*Finalmente, criamos o bote.*/
        criaBote(p, v);
	}

    /*deltaTime em segundos, frequencia em ciclos por segundo (passageiros a serem criados por segundo).*/
    timeElapsed += deltaTime;
    if (timeElapsed >= 1)  /*Um segundo inteiro foi completado, criar passageiros...*/
    {
		numVivos = getNumPassageirosVivos();

        for (i=0; i<getFrequency() && numVivos < getMaxNumPassageiros(); i++)
        {
            /*Apenas criamos o vetor e setamos apenas 1 de suas coordenadas (a outra = 0). Assim esse valor que estamos setando
              sera igual ao modulo do vetor, que queremos que seja um numero especifico dependendo das configuracoes.
              Depois iremos atualizar (para variar) a direcao, e somente a direcao, da velocidade.*/
            v = VETORinit(getSpeed() + (getRandDouble()*2 - 1), 0);
			/*Inicializamos a posicao com um valor fora da tela, para que no teste a seguir nao haja nenhuma entidade para que possamos
			  criar uma.*/
			p = VETORinit(-30.0, -30.0);

            /*Agora escolhemos uma posicao aleatoria ao longo das bordas do oceano para criar o passageiro,
              e atualizamos a sua direcao para eles comecarem se mexendo ao centro do oceano.*/
			while ( getEntityByPositionVector(p) != NULL || getX(p) < 0)
			{
	            posInicial = rand()%4;
    	        estadoInicial = rand()%6;

	            if (posInicial == 0)
    	        {
    	            setX(p, rand()%SCREEN_W);
					setY(p, 10);
    	            if (estadoInicial <= 3)
    	                setEstado(1, v);
    	            else if (estadoInicial == 4)
    	                setEstado(7, v);
    	            else if (estadoInicial == 5)
    	                setEstado(5, v);
    	        }
    	        else if (posInicial == 1)
    	        {
					setX(p, 0);
    	            setY(p, rand()%SCREEN_H);
    	            if (estadoInicial <= 3)
    	                setEstado(2, v);
    	            else if (estadoInicial == 4)
    	                setEstado(4, v);
    	            else if (estadoInicial == 5)
    	                setEstado(5, v);
    	        }
    	        else if (posInicial == 2)
    	        {
    	            setX(p, rand()%SCREEN_W);
					setY(p, SCREEN_H-1);
    	            if (estadoInicial <= 3)
    	                setEstado(0, v);
    	            else if (estadoInicial == 4)
    	                setEstado(6, v);
    	            else if (estadoInicial == 5)
    	                setEstado(4, v);
    	        }
    	        else if (posInicial == 3)
    	        {
    	            setX(p, SCREEN_W-1);
					setY(p, rand()%SCREEN_H);
    	            if (estadoInicial <= 3)
    	                setEstado(3, v);
    	            else if (estadoInicial == 4)
    	                setEstado(6, v);
    	            else if (estadoInicial == 5)
    	                setEstado(7, v);
    			}
			}

            /*Finalmente, criamos o passageiro.*/
            criaPassageiro(p, v, rand()%60 + 40);

			numVivos++;
        }

        timeElapsed -= 1.0;
    }
}


/*******************************
 Main...
*********************************/
int main(int argc, char *argv[])
{
	clock_t inicial, previous, delta;
	double deltaTime;

	/*Primeiramente lemos os parametros passados:*/
	interpretaParametros(argc, argv);

    /*Entao inicializamos nossas coisas, comecando com os graficos...*/
    if (allegro_init() != 0)
    {
        printf("Incapaz de inicializar o Allegro...\n");
        return 1;
    }

    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0) != 0)
    {
        printf("Incapaz de setar o modo grafico/janela. \n");
        return 2;
    }
    /* set the color palette */
    set_palette(desktop_palette);

	srand( getRandomSeed() );
	inicializaEntidades();
	inicializaPassageiros();
	inicializaBotes();
	inicializaDesenho();

    /*Qualquer codigo necessario para inicializacao de outras coisas vem aqui.*/
    criaAsimov();

	inicial = clock();
	previous = 0;
	while (clock() - inicial < CLOCKS_PER_SEC*getTimeLimit() )
	{
		delta = clock() - previous;
		if (delta > (double)CLOCKS_PER_SEC/(double)getFramesPerSec() )
		{
			previous = clock();

		    /*Calculo da variacao de tempo (em segundo) entre o ciclo anterior e esse.*/
			deltaTime = (double)delta/(double)CLOCKS_PER_SEC;
			/*===================================================*/
			/*executa update aqui (desenho -> logica). */

			/*update logico...*/
			colisaoGeral(deltaTime);
			updateGameLogic(deltaTime);
			updateLogic(deltaTime);

			/*update grafico...*/
            preparaPraDesenho();
            updateDesenho(); /*Chama o update grafico de todas entidades...*/
            updateScreen();
            /*CHECK:
                >arrumar colisao pra setar a direcao certa depois de uma colisao (a normal da tangente da superficie naquele ponto)
                >pode ser necessario arrumar passageiro para que ele nao sete explicitamente sua direcao, mas sim que tome
                 a cadeia de markov como "o quanto virar" para algum lado, assim poderemos ter que as entidades possam se mexer
                 em qualquer direcao nesse incrivel mundo R2 continuo :P

            */
			/*====================================================*/
		}
	}

    /*Qualquer codigo necessario para finalizacao de outras coisas vem aqui.*/

    /*Finalmente terminamos esses modulos do programa, liberando toda a memoria usada.*/
    terminaDesenho();
    allegro_exit();
	terminaBotes();
    terminaPassageiros();
	terminaEntidades();

    return 0;
}
END_OF_MAIN()  /*macro magica do Allegro pra manter portabilidade do main entre alguns SOs (incluindo Linux e Windows...)*/

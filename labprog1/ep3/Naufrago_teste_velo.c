/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Naufrago_teste_velo.c - arquivo de teste automatizado do jogo.
                        Roda o jogo normalmente, porem vai coletando informacoes sobre as velocidades dos passageiros
                        criados, apresentando os resultados ao fim da execucao do programa.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: --/04/2010
Testado no Windows7 e Linux (Debian)
Compilando com -Wall -ansi -pedantic
***************************************************/


/****************************************************
 Os includes basicos...
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Entity.h"
#include "Desenho.h"
#include "Config.h"
#include "Passageiro.h"
#include "Estat.h"


/****************************************************
  Atributos e Variaveis Globais
*****************************************************/
/*timeElapsed e' usado pelo updateGameLogic para marcar tempo passado (em segundos).

  Os vetores AuxVelo e MediaVelo sao usados para calcular a velocidade media
  dos passageiros do jogo. As variaveis Contador e Time sao usadas para as itera
  coes do AuxVelo e do MediaVelo, respectivamente.*/
double timeElapsed = 0.0, *AuxVelo, *MediaVelo;
int Contador = 0, Time = 0;


/****************************************************
 Funcoes Para o Teste de Variacao da Velocidade dos
 Passageiros.
*****************************************************/

void VelocidadeTotal( Item ent, Item not_used )
{
	Entity AuxEnt;
	AuxEnt = (Entity)ent;
	AuxVelo[Contador] = VETORmodulo( getVelocidade( AuxEnt ) );
	Contador++;
}

void getTodasVelocidades()
{
	executeForAllEntities( VelocidadeTotal, NULL );
}

void updateMedia( int i )
{
	MediaVelo[i] = getMedia( getEntityCount(), AuxVelo );
	Contador = 0;
	free( AuxVelo );
}


/****************************************************
 Funcoes Principais
*****************************************************/
/*Funcao de update logico do proprio jogo. E' executada em cada ciclo apos a checagem de colisao, antes
  do update logico das entidades do jogo.*/
void updateGameLogic(double deltaTime)
{
    int i, estadoInicial, posInicial, numVivos;
    Vetor v, p;

	/*Esta parte aloca espaco para um vetor auxiliar, coloca a media da velocidade
	  de todas as entidades que existem no momento na posicao Time do vetor MediaVelo.*/
	if ( getEntityCount() > 0 )
	{
		AuxVelo = malloc( getEntityCount()*sizeof(double) );
		getTodasVelocidades();
		updateMedia( Time );
		Time++;
	}

    /*deltaTime em segundos, frequencia em ciclos por segundo (passageiros a serem criados por segundo).*/
    timeElapsed += deltaTime;
    if (timeElapsed >= 1)  /*Um segundo inteiro foi completado, criar passageiros...*/
    {
		numVivos = getNumPassageirosVivos();

        for (i=0; i<getFrequency() && numVivos < getMaxNumPassageiros(); i++)
        {
            posInicial = rand()%4;
            estadoInicial = rand()%6;

            /*Apenas criamos o vetor e setamos apenas 1 de suas coordenadas (a outra = 0). Assim esse valor que estamos setando
              sera igual ao modulo do vetor, que queremos que seja um numero especifico dependendo das configuracoes.
              Depois iremos atualizar (para variar) a direcao, e somente a direcao, da velocidade.*/
            v = VETORinit(getSpeed() + (getRandDouble()*2 - 1), 0);

            /*Agora escolhemos uma posicao aleatoria ao longo das bordas do oceano para criar o passageiro,
              e atualizamos a sua direcao para eles comecarem se mexendo ao centro do oceano.*/
            if (posInicial == 0)
            {
                p = VETORinit(rand()%120, 0);
                if (estadoInicial <= 3)
                    setEstado(1, v);
                else if (estadoInicial == 4)
                    setEstado(7, v);
                else if (estadoInicial == 5)
                    setEstado(5, v);
            }
            else if (posInicial == 1)
            {
                p = VETORinit(0, rand()%30);
                if (estadoInicial <= 3)
                    setEstado(2, v);
                else if (estadoInicial == 4)
                    setEstado(4, v);
                else if (estadoInicial == 5)
                    setEstado(5, v);
            }
            else if (posInicial == 2)
            {
                p = VETORinit(rand()%120, 29);
                if (estadoInicial <= 3)
                    setEstado(0, v);
                else if (estadoInicial == 4)
                    setEstado(6, v);
                else if (estadoInicial == 5)
                    setEstado(4, v);
            }
            else if (posInicial == 3)
            {
                p = VETORinit(119, rand()%30);
                if (estadoInicial <= 3)
                    setEstado(3, v);
                else if (estadoInicial == 4)
                    setEstado(6, v);
                else if (estadoInicial == 5)
                    setEstado(7, v);
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

    /*Entao inicializamos nossas coisas...*/
	srand( getRandomSeed() );
	inicializaEntidades();
	inicializaPassageiros();

	/*Aqui o vetor que sera usado para calcula a velocidade de todos os passagerios
	  do jogo e alocado e inicializado com valor 0.0 .*/
	MediaVelo = malloc( 10*getTimeLimit()*sizeof(double) );

	inicial = clock();
	previous = 0;
	while (clock() - inicial < CLOCKS_PER_SEC*getTimeLimit() )
	{
		delta = clock() - previous;
		if (delta > CLOCKS_PER_SEC/getFramesPerSec() )
		{
		    /*Calculo da variacao de tempo (em segundo) entre o ciclo anterior e esse.*/
			deltaTime = (double)delta/(double)CLOCKS_PER_SEC;
			/*===================================================*/
			/*executa update aqui (desenho -> logica). */

			/*primeiro rodamos funcoes de limpeza necessarias...*/
			limpaMar();

			/*update logico...*/
			colisaoGeral(deltaTime);
			updateGameLogic(deltaTime);
			updateLogic(deltaTime);

			/*update grafico...*/
			system("clear");  /*Nota: o comando para limpar o terminal e' clear no linux, cls no windows.*/
			updateDesenho();
			desenhaMar();
            printf("\n");
			/*====================================================*/
			previous = clock();
		}
	}

    /*Aqui a Velocidade Media e Desvio Padrao de todos os passageiros gerados pelo
      programa sao calculadas e retornadas. */
	printf("A Velocidade Media dos passageiros foi: %f\n", getMedia( Time, MediaVelo ));
	printf("O desvio padrao da Velocidade dos passageiros foi: %f\n", getDesvioPadrao( Time, MediaVelo ));

    free(MediaVelo);

    /*Finalmente terminamos esses modulos do programa, liberando toda a memoria usada.*/
    terminaPassageiros();
	terminaEntidades();

    return 0;
}

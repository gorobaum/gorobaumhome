/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Config.c - implementacao do sistema que gerencia os valores configuraveis do jogo.

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
#include <string.h>
#include "Config.h"

/****************************************************
 Valores de Configuracao
*****************************************************/
unsigned int timeLimit;           /*Tempo limite (em segundos) para que o jogo fique rodando.*/
unsigned int FPS;                 /*Taxa de Frames por Segundo do jogo.*/
unsigned int seed;                /*Semente para o gerador de numeros aleatorios*/
double frequency;                 /*Frequencia media para geracao de passageiros novos.*/
double speed;                     /*Modulo da velocidade media para passageiros novos.*/
unsigned int maxNumPassageiros;   /*Numero maximo de passageiros vivos simultaneamente.*/


/****************************************************
 Funcoes Principais
*****************************************************/
/*Funcao Principal do Config, interpreta os parametros passados por command-line para o jogo. */
void interpretaParametros(int argc, char* argv[])
{
	/* argc = contagem de argumentos passados. (minimo = 1, o nome do programa)
	   argv = vetor dos argumentos (strings) passados.

	   Argumentos que usamos:
		-tX / -timeX:  X = numero de segundos pra ficar rodando.
		-fpsX /-FPSX:  X = fps do jogo (usar default se necessario)
		-sX / -seedX:  X = semente para o srand
		-fX / -freqX:  X = frequencia media para geracao dos passageiros
		-vX / -veloX:  X = velocidade media (modulo) para passageiros novos
		-pX / -passX:  X = numero maximo de passageiros vivos simultaneamente
	*/
	int i;

	/*Atribuicao dos valores padrao.*/
	timeLimit = DEFAULT_TIME_LIMIT;
	FPS = DEFAULT_FPS;
	seed = DEFAULT_SEED;
	frequency = DEFAULT_FREQUENCY;
	speed = DEFAULT_SPEED;
	maxNumPassageiros = DEFAULT_MAX_NUM_PASS;

	for (i=1; i < argc; i++)
	{
		if ( strncmp(argv[i], "-time", 5) == 0 && strlen(argv[i]) > 2 )
			timeLimit = atoi(&argv[i][5]);
		else if ( strncmp(argv[i], "-t", 2) == 0 && strlen(argv[i]) > 2 )
			timeLimit = atoi(&argv[i][2]);
		else if ( strncmp(argv[i], "-fps", 4) == 0 && strlen(argv[i]) > 2 )
			FPS = atoi(&argv[i][4]);
		else if ( strncmp(argv[i], "-FPS", 4) == 0 && strlen(argv[i]) > 2 )
			FPS = atoi(&argv[i][4]);
		else if ( strncmp(argv[i], "-seed", 5) == 0 && strlen(argv[i]) > 2 )
			seed = atoi(&argv[i][5]);
		else if ( strncmp(argv[i], "-s", 2) == 0 && strlen(argv[i]) > 2 )
			seed = atoi(&argv[i][2]);
		else if ( strncmp(argv[i], "-freq", 5) == 0 && strlen(argv[i]) > 2 )
			frequency = strtod(&argv[i][5], NULL);
		else if ( strncmp(argv[i], "-f", 2) == 0 && strlen(argv[i]) > 2 )
			frequency = strtod(&argv[i][2], NULL);
		else if ( strncmp(argv[i], "-velo", 5) == 0 && strlen(argv[i]) > 2 )
			speed = strtod(&argv[i][5], NULL);
		else if ( strncmp(argv[i], "-v", 2) == 0 && strlen(argv[i]) > 2 )
			speed = strtod(&argv[i][2], NULL);
		else if ( strncmp(argv[i], "-pass", 5) == 0 && strlen(argv[i]) > 2 )
			maxNumPassageiros = atoi(&argv[i][5]);
		else if ( strncmp(argv[i], "-p", 2) == 0 && strlen(argv[i]) > 2 )
			maxNumPassageiros = atoi(&argv[i][2]);
	}
}


/****************************************************
  Funcoes para adquirir os valores de configuracao.
*****************************************************/
/*Retorna o tempo limite (em segundos) para que o jogo fique rodando.*/
unsigned int getTimeLimit()
{
	return timeLimit;
}

/*Retorna a axa de Frames por Segundo do jogo.*/
unsigned int getFramesPerSec()
{
	return FPS;
}

/*Retorna a semente para o gerador de numeros aleatorios*/
unsigned int getRandomSeed()
{
	return seed;
}

/*Retorna a frequencia media para geracao de passageiros novos.*/
double getFrequency()
{
	return frequency;
}

/*Retorna o modulo da velocidade media para passageiros novos.*/
double getSpeed()
{
	return speed;
}

/*Retorna o numero maximo de passageiros vivos simultaneamente.*/
unsigned int getMaxNumPassageiros()
{
	return maxNumPassageiros;
}

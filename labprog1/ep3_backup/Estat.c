/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Estat.c - implementa as funcoes estatisticas usadas pelo jogo.

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
#include <time.h>
#include "Estat.h"


/****************************************************
 Simulacao de Cadeia de Markov
*****************************************************/
/*Calcula e retorna o proximo estado de uma cadeia de Markov homogenea, de acordo com o estado atual, numero de estados e
  matriz de transicao passados.*/
int markovProximoEstado(int estadoAtual, int numEstados, double** transicao)
{
	int i;
	double r, j;

	r = getRandDouble()*100;
	for (i=0, j=0; i<=numEstados; i++)
	{
		if ( r < j ) /* r < j  ==> j é o limite superior do bloco da barra de probabilidades aonde r caiu, da qual devemos retornar o estado*/
		{
			/* estado = i-1*/
			return i -1;
		}
		j = j + transicao[estadoAtual][i] * 100;
	}
	return -1;
}


/****************************************************
 Chance e Numeros Aleatorios
*****************************************************/
/*Executa um teste aleatorio para ver se deu a chance (probabilidade, em %) foi bem sucedida.*/
short checkChance(double chance)
{
	if ( getRandDouble()*100  <= chance )
		return 1;
	return 0;
}

/*Retorna um double aleatorio, no intervalo [0, 1[  */
double getRandDouble()
{
	return (double)rand() / (double)RAND_MAX;
}

/*Retorna um inteiro aleatorio no intervalo [0, max[. Se max = 0, usa o padrao do sistema para valor maximo.*/
int getRand(int max)
{
	if (max > 0)
		return rand() % max;
	return rand();
}

/*Retorna um inteiro aleatorio no intervalo [a, b[  */
int getRandInRange(int a, int b)
{
	if (a < 0 || b < 0)
	{
		printf("ERROR in Estat.c: getRandInRange - A or B is less than 0\n");
		return 0;
	}
	if (b < a)
	{
		printf("ERROR in Estat.c: getRandInRange - B is less than A\n");
		return 0;
	}

	return (rand() % (b-a)) + a;
}

/****************************************************
 Funcoes auxiliares para calcular estatisticas de conjuntos (de numeros, inteiros e reais)
*****************************************************/
/*Retorna a variancia dos n itens da lista de doubles l.*/
double getVariancia( int n, double* l )
{
	int i;
	double ret = 0;
	double media = getMedia(n, l);
	for (i=0; i<n; i++)
	{
		ret += (l[i] - media) * (l[i] - media);
	}
	ret = ret / (double)n;
	return ret;
}

/*Retorna o desvio padrao dos n itens da lista de doubles l.*/
double getDesvioPadrao( int n, double* l )
{
	return sqrt( getVariancia(n, l) );
}

/*Retorna a media dos n itens da lista de doubles l.*/
double getMedia( int n, double* l )
{
	int i;
	double ret = 0;
	for (i=0; i<n; i++)
	{
		ret += l[i];
	}
	ret = ret / (double)n;
	return ret;
}

/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Naufrago_teste.c - Versao do Naufrago.c para testes.
                   Roda varios testes automatizados diferentes para testar o programa,
                   imprimindo os resultados apos a execucao do programa.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (comando:  make teste)
***************************************************/


/****************************************************
 Os includes basicos...
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
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
  dos passageiros do jogo.*/
double timeElapsed = 0.0, *AuxVelo, *MediaVelo;
/*Vetores de velocidade inicial e final de 2 passageiros, para o teste de colisao.*/
Vetor Vini[2], Vfim[2];
/*As variaveis Contador e Time sao usadas para as iteracoes do AuxVelo e do MediaVelo, respectivamente.
  TesteCriou e' usado como bool para dizer se os passageiros ja foram criados no teste de colisao.
  QualTeste armazena o tipo de teste sendo rodado.
  Colidiu indica se a colisao ja ocorreu no teste de colisao.
  E massaColisao e' um vetor para guardar o valor das massas dos 2 passageiros do teste de colisao.*/
int Contador, Time, TesteCriou, QualTeste, Colidiu, massaColisao[2];
/*Vetor contendo os 2 passageiros (2 entidades) usados no teste de colisao.*/
Entity entColisao[2];


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
void updateGameLogic(double deltaTime, int QualTeste)
{
    int i, estadoInicial, posInicial, numVivos;
    Vetor v, p;

	/*Esta parte aloca espaco para um vetor auxiliar, coloca a media da velocidade
	  de todas as entidades que existem no momento na posicao Time do vetor MediaVelo.*/
	if ( QualTeste == 3 && getEntityCount() > 0 )
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
		if ( QualTeste != 2 )
		{
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
        }
        else if ( TesteCriou == 0 )
        {
			/*usando a variavel posInicial como uma auxiliar para guardar o valor do estado do
			  passageiro criado anteriormente aqui, para que o proximo passageiro nao tenha o mesmo estado.*/
			posInicial = estadoInicial = -1;
        	for( i = 0; i < 2; i++ )
        	{
				while (estadoInicial == posInicial)
					estadoInicial = rand()%8;

				posInicial = estadoInicial;

        	    v = VETORinit( 3.5, 0 );
        		setEstado( estadoInicial, v );

        		p = VETORinit(60, 15);
                if (getX(v) != 0)
                    setX(p, 60 -getX(v)*4);
                if (getY(v) != 0)
                    setY(p, 15 -getY(v)*4);

				Vini[i] = VETORinit( getX(v), getY(v) );
				massaColisao[i] = rand()%60 + 40;
				entColisao[i] = criaPassageiro(p, v, massaColisao[i]);
        	}
        	TesteCriou = 1;
        }

        if ( QualTeste == 2 && Colidiu == 0 && getEstaColidindo( entColisao[0] ) && getEstaColidindo( entColisao[1] ) )
        {
        	Vfim[0] = VETORinit( getX(getVelocidade(entColisao[0])), getY(getVelocidade(entColisao[0])) );
			Vfim[1] = VETORinit( getX(getVelocidade(entColisao[1])), getY(getVelocidade(entColisao[1])) );
        	Colidiu = 1;
        }
        timeElapsed -= 1.0;
    }
}


/*******************************
  Funcao principal do Jogo
*********************************/
/*Funcao para rodar o jogo em si, com os parametros passados.
  Assim podemos rodar o jogo mais de uma vez com parametros diferentes durante a mesma execucao deste programa de testes.
  Fora algumas alteracoes para os testes, seria o equivalente ao Main do Naufrago.c normal.*/
int runGame( int podeDesenhar, int argc, char **argv )
{
	clock_t inicial, previous, delta;
	double deltaTime;
	int i, j;

	/*Primeiramente lemos os parametros passados:*/
	interpretaParametros(argc, argv);

    /*Entao inicializamos nossas coisas...*/
	srand( getRandomSeed() );
	inicializaEntidades();
	inicializaPassageiros();

	/*Aqui o vetor que sera usado para calcula a velocidade de todos os passagerios
	  do jogo e alocado e inicializado com valor 0.0 .*/
	if ( QualTeste == 3 ) MediaVelo = malloc( 10*getTimeLimit()*sizeof(double) );
	else if (QualTeste == 2)
	{
	    for (i=0; i<8; i++)
            for (j=0; j<8; j++)
                if (i == j)
                    setProbDeMudancaDeEstado(i, j, 1.00);
                else
                    setProbDeMudancaDeEstado(i, j, 0.0);
	}

    printf("\nExecutando o teste %d... Por favor espere por %d segundos...\n\n", QualTeste, getTimeLimit() );
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
			updateGameLogic(deltaTime, QualTeste);
			updateLogic(deltaTime);

			/*update grafico...*/
			if ( podeDesenhar != 0)
			{
                system("clear");  /*Nota: o comando para limpar o terminal e' clear no linux, cls no windows.*/
                updateDesenho();
                desenhaMar();
                printf("\n");
			}
			/*====================================================*/
			previous = clock();
		}
	}

    /*Aqui a Velocidade Media e Desvio Padrao de todos os passageiros gerados pelo
      programa sao calculadas e retornadas. */
    if (QualTeste == 3)
    {
        printf("A Velocidade Media Padrao (para a geracao dos passageiros) e': %f\n", getSpeed() );
		printf("A Velocidade Media dos passageiros foi: %f\n", getMedia( Time, MediaVelo ));
		printf("O desvio padrao da Velocidade dos passageiros foi: %f\n", getDesvioPadrao( Time, MediaVelo ));
	    free(MediaVelo);
	}

    /*Finalmente terminamos esses modulos do programa, liberando toda a memoria usada.*/
    terminaPassageiros();
	terminaEntidades();

    return 0;
}


/*******************************
  Main desta versao de testes.
*********************************/
int main()
{
	int argc, i, podeDesenhar;
	double CoefRest;
	char **argv, *AuxString1, *AuxString2;

    /*Inicializamos nossas (varias) variaveis....*/
    Contador = Time = TesteCriou = QualTeste = Colidiu = 0;
    argc = 3;

	argv = malloc(7*sizeof(char*));
	for ( i = 0; i < 7; i++ )
	{
        argv[i] = malloc(10*sizeof(char));
        memset(argv[i], 0, 10);
	}
	AuxString1 = malloc(20*sizeof(char));
	AuxString2 = malloc(20*sizeof(char));
	memset(AuxString1, 0, 20);
	memset(AuxString2, 0, 20);
	for ( i=0; i<2; i++)
	{
		entColisao[i] = NULL;
		Vini[i] = NULL;
		Vfim[i] = NULL;
	}

    /*Perguntamos ao usuario qual teste e' pra rodar...*/
	printf("Digite o numero correspondente para iniciar o teste: \n");
	printf("1 - Teste de Robustez \n");
	printf("2 - Teste de Colisao \n");
	printf("3 - Teste de Velocidade \n");
	printf("Digite o numero: ");
	scanf("%d", &QualTeste);
	printf("Deseja que o oceano seja desenhado?\n");
	scanf("%d", &podeDesenhar);

    /*Executamos o(s) teste(s)...*/
	if ( QualTeste == 1 )
	{
		printf("Digite um numero de passageiros para o teste: \n");
		scanf("%s", AuxString2);
		strcpy( AuxString1, "-p" );
		strcat( AuxString1, AuxString2 );
		strcpy( argv[1], AuxString1 );
		strcpy( argv[2], "-f100" );
		printf("Rodando o programa com %s passageiros. Presione qualquer tecla para iniciar o programa. \n", AuxString2);
		getchar();
		runGame( podeDesenhar, argc, argv );

		printf("Digite um numero de passageiros para o teste: \n");
		scanf("%s", AuxString2);
		strcpy( AuxString1, "-p" );
		strcat( AuxString1, AuxString2 );
		strcpy( argv[1], AuxString1 );
		strcpy( argv[2], "-f100" );
		printf("Rodando o programa com %s passageiros. Presione qualquer tecla para iniciar o programa. \n", AuxString2);
		getchar();
		runGame( podeDesenhar, argc, argv );

		printf("Digite a velocidade dos passageiros para o teste: \n");
		scanf("%s", AuxString2);
		strcpy( AuxString1, "-v" );
		strcat( AuxString1, AuxString2 );
		strcpy( argv[1], AuxString1 );
		strcpy( argv[2], "-f100" );
        printf("Rodando o programa com velocidade inicial %s. Presione qualquer tecla para iniciar o programa. \n", AuxString2);
		getchar();
		runGame( podeDesenhar, argc, argv );

		printf("Digite a velocidade dos passageiros para o teste: \n");
		scanf("%s", AuxString2);
		strcpy( AuxString1, "-v" );
		strcat( AuxString1, AuxString2 );
		strcpy( argv[1], AuxString1 );
		strcpy( argv[2], "-f100" );
		printf("Rodando o programa com velocidade inicial %s. Presione qualquer tecla para iniciar o programa. \n", AuxString2);
		getchar();
		runGame( podeDesenhar, argc, argv );
	}
	else if (QualTeste == 2)
	{
		strcpy( AuxString1, "-t8" );
		strcpy( argv[1], AuxString1 );
		runGame( podeDesenhar, argc, argv );
	}
	else runGame( podeDesenhar, argc, argv );

    /*Hora de imprimir os resultados necessarios.*/
	if ( QualTeste == 2 )
	{
		printf("Info do Passageiro 1: Massa=%d;  VelocidadeInicial=(%f, %f) [Modulo=%f]   VelocidadeFinal=(%f, %f) [Modulo=%f] \n",
						 massaColisao[0], getX(Vini[0]), getY(Vini[0]), VETORmodulo(Vini[0]), getX(Vfim[0]), getY(Vfim[0]),
						 VETORmodulo(Vfim[0]) );
		printf("Info do Passageiro 2: Massa=%d;  VelocidadeInicial=(%f, %f) [Modulo=%f]   VelocidadeFinal=(%f, %f) [Modulo=%f] \n",
						 massaColisao[1], getX(Vini[1]), getY(Vini[1]), VETORmodulo(Vini[1]), getX(Vfim[1]), getY(Vfim[1]),
						 VETORmodulo(Vfim[1]) );

        if ( getX(Vini[0]) != getX(Vini[1]) )
            CoefRest = ( (getX(Vfim[1]) - getX(Vfim[0])) / (getX(Vini[0]) - getX(Vini[1])) );
        else
            CoefRest = ( (getY(Vfim[1]) - getY(Vfim[0])) / (getY(Vini[0]) - getY(Vini[1])) );
		printf("Coeficiente de Restituicao: %f\n", CoefRest);
	}

	printf("Testes Concluidos!!! \n");

    /*Acabamos os testes, liberamos a memoria.*/
    for ( i = 0; i < 7; i++ ) free(argv[i]);
	if (QualTeste == 2)
	{
		for ( i=0; i<2; i++)
		{
			free(Vini[i]);
			free(Vfim[i]);
		}
	}
    free(argv);
    free(AuxString1);
	free(AuxString2);

	return 0;
}

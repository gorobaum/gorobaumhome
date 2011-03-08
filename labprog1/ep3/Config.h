/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Config.h - interface do sistema que gerencia os valores configuraveis do jogo.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/

#ifndef CONFIG
#define CONFIG

/*Funcao Principal do Config, interpreta os parametros passados por command-line para o jogo. */
void interpretaParametros(int argc, char* argv[]);

/*Valores padrao para alguns valores de configuracao.*/
#define DEFAULT_TIME_LIMIT 30
#define DEFAULT_FPS  30
#define DEFAULT_SEED  time(NULL)
#define DEFAULT_FREQUENCY  25
#define DEFAULT_SPEED  50
#define DEFAULT_MAX_NUM_PASS  100

/*Funcoes para adquirir os valores de configuracao.*/
unsigned int getTimeLimit();           /*Retorna o tempo limite (em segundos) para que o jogo fique rodando.*/
unsigned int getFramesPerSec();        /*Retorna a taxa de Frames por Segundo do jogo.*/
unsigned int getRandomSeed();          /*Retorna a semente para o gerador de numeros aleatorios*/
double getFrequency();                 /*Retorna a frequencia media para geracao de passageiros novos (deve ser >= 1).*/
double getSpeed();                     /*Retorna o modulo da velocidade media para passageiros novos.*/
unsigned int getMaxNumPassageiros();   /*Retorna o numero maximo de passageiros vivos simultaneamente.*/
#endif


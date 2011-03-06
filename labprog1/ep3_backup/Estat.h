/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Estat.h - interface das funcoes estatisticas usadas pelo jogo.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/


#ifndef ESTAT
#define ESTAT

/*Funcoes relativas a Cadeia de Markov.*/

/*Calcula o proxima estado da cadeia de markov homogenea.*/
int markovProximoEstado(int estadoInicial, int numEstados, double** transicao);


/*Funcoes relativas a chance e numeros aleatorios.*/
short checkChance(double chance); /*Executa um teste aleatorio para ver se deu a chance (probabilidade, em %) foi bem sucedida.*/
double getRandDouble();           /*Retorna um double aleatorio, no intervalo [0, 1[  */
/*Retorna um inteiro aleatorio no intervalo [0, max[. Se max = 0, usa o padrao do sistema para valor maximo.*/
int getRand(int max);
int getRandInRange(int a, int b); /*Retorna um inteiro aleatorio no intervalo [a, b[  */


/*Funcoes Estatisticas Auxiliares.*/
double getVariancia( int n, double* l );     /*Calcula a variancia dos n itens da lista de doubles l.*/
double getDesvioPadrao( int n, double* l );  /*Calcula o desvio padrao dos n itens da lista de doubles l.*/
double getMedia( int n, double* l );         /*Calcula a media dos n itens da lista de doubles l.*/

#endif


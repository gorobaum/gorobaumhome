/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Entity.h - interface do tipo basico entidade, representando um objeto no jogo.
		   Tambem atua como um gerenciador de todas as entidades do jogo.
		   Implementado de um jeito que remete a orientacao a objetos.  :D

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/
#ifndef ENTITY
#define ENTITY

/*Definicao do tipo basico de uma Entidade.*/
typedef struct _entity* Entity;

/*E a definicao da nossa enumeracao de tipos de entidades...*/
typedef enum { PASS, BOTE, RECIFE, ASIMOV } ENT_TYPE;

#include "Lista.h"
#include "Fisica.h"


/*Funcoes principais do Gerenciador de Entidades.*/
void inicializaEntidades();  /*Inicializa o gerenciador de entidades.*/
void terminaEntidades();     /*Termina o gerenciador de entidades, destruindo todas entidades e liberando toda memoria.*/

/*Funcoes para uma Entidade*/
/*Cria uma entidade nova com os parametros passados.*/
Entity criaEntidade(Vetor pos, Vetor vel, int mass, Item data, unsigned int raio, ENT_TYPE tipo, unsigned long cor,
                    void (*updateEntLogic)(Entity ent, double deltaTime),
                    void (*drawEntity)(Entity ent),
                    void (*funcColidiuCom)(Entity ent, Entity aux, double deltaTime),
                    void (*clearData)(Item data) );
void destroiEntidade(Entity ent);  /*Destroi a entidade passada, liberando a memoria usada por ela.*/
void setEntityToBeDestroyed(Entity ent);  /*Seta a entidade para ser destruida no final do ciclo logico atual.*/
Vetor getPosicao(Entity ent);      /*Retorna a posicao da entidade passada.*/
Vetor getVelocidade(Entity ent);   /*Retorna o vetor da velocidade da entidade passada.*/
int getMassa(Entity ent);          /*Retorna o valor da massa da entidade passada.*/
unsigned int getID(Entity ent);    /*Retorna o identificador unico (ID) da entidade passada.*/
unsigned int getRaio(Entity ent);  /*Retorna o raio da entidade se tratada como uma forma circular. Valor em pixels.*/
ENT_TYPE getTipo(Entity ent);      /*Retorna o tipo da entidade.*/
unsigned long getColor(Entity ent);/*Retorna o valor da cor da entidade.*/
/*Chama a funcao de tratamento de colisao da ENT passada, com os parametros passados.
  AUX e' a entidade com a qual ENT colidiu, sendo que se AUX for NULL significa que a ENT "colidiu" com as bordas do oceano.*/
void callColidiuCom(Entity ent, Entity aux, double deltaTime);
void setEstaColidindo(Entity ent, char emColisao);  /*Seta se a entidade esta em colisao ou nao. Char emColisao usado como Bool.*/
char getEstaColidindo(Entity ent); /*Retorna uma bool dizendo se a entidade esta colidindo ou nao.*/
Item getData(Entity ent);          /*Retorna o Item de dados extras da entidade.*/
void callDrawEntity(Entity ent);   /*Chama a funcao de desenho da entidade passada.*/

/*Funcoes de execucao para todas Entidades*/
/*Executa a funcao passada, com o item argumento opcional passado, para todas as entidades.*/
void executeForAllEntities(void (*func)(Item ent, Item arg), Item arg );
void updateLogic(double deltaTime);    /*Executa a funcao de update logico de todas entidades.*/
void updateDesenho();  /*Executa a funcao de desenho de todas entidades.*/

/*Funcoes Auxiliares*/
/*Retorna a entidade que seja considerada igual ao Item arg(umento) de acordo com a funcao de comparacao passada.
  Esta funcao sera usada para comparar o arg com cada entidade ent da lista de entidades, e devera retornar 0 caso sejam iguais.*/
Entity getEntity(Item arg, int (*compareFunc)(Item arg, Item ent));
int compareEntityID(Item arg, Item ent);        /*Funcao de comparacao entre um ID (arg) e uma Ent.*/
Entity getEntityByID(int ID);                   /*Retorna a entidade com o ID passado.*/
Entity getEntityByPositionVector(Vetor pos);    /*Retorna a entidade com o vetor posicao passada.*/
Entity getEntityByPosition(double x, double y); /*Retorna a entidade com a posicao passada como X e Y direto.*/
int getEntityCount();                           /*Retorna a contagem de entidades vivas.*/
#endif


/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Entity.c - implementa o tipo basico de uma entidade.
		   Tambem atua como um gerenciador de todas as entidades do jogo.
		   Implementado de um jeito que remete a orientacao a objetos.  :D

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
#include "Lista.h"
#include "Entity.h"
#include "Fisica.h"


/****************************************************
 Entidade e Variaveis Globais
*****************************************************/
/*Struct basica representando uma entidade. E' o tipo principal usado por aqui.*/
struct _entity
{
	Vetor posicao;                          /*Vetor representando a posicao da entidade no plano cartesiano.*/
	Vetor velocidade;                       /*Vetor representando a velocidade (direcao e modulo) da entidade no plano cartesiano.*/
	int massa;                              /*Valor da massa da entidade. A unidade e' a mesma para todo o jogo.*/
	unsigned int ID;                        /*Identificador da entidade. E' um valor unico para cada uma.*/
	unsigned int raio;                      /*Valor (pixels) do raio basico da entidade, se tratada como um circulo.*/
	ENT_TYPE tipo;                          /*Enum, identificador do tipo da entidade.*/
	char estaColidindo;                     /*Char usado como uma booleana dizendo se a entidade esta colidindo.*/
	unsigned long color;                    /*Valor da cor para desenhar essa entidade, usado pelo Allegro.*/
	void (*updateEntityLogic)(Entity ent, double deltaTime);  /*Apontador para a funcao de update logico da entidade.*/
	void (*drawEntity)(Entity ent);         /*Apontador para a funcao de desenho da entidade.*/
	void (*colidiuCom)(Entity ent, Entity aux, double deltaTime);  /*Apontador para a funcao que trata a colisao entre duas entidades.*/
	void (*clearData)(Item data);           /*Apontador para a funcao de limpeza do Item data (devendo liberar sua memoria)*/
	Item data;                              /*Item de dados opcional. Pode ser usado para armazenar outros atributos da entidade.*/
};


/*Infelizmente, temos que ter algumas variaveis globais...*/
unsigned int nextID;    /*Valor da ID a ser dada para a proxima entidade criada.*/
S entityList;           /*Lista de todas as entidades criadas (e vivas).*/
S garbageList;          /*Lista de entidades que devem ser destruidas ao final de um ciclo logico.*/

/****************************************************
 Funcoes Principais do Gerenciador de Entidades
*****************************************************/
/*Inicializa o gerenciador de entidades.*/
void inicializaEntidades()
{
	nextID = 1;
	entityList = LISTinit();
	garbageList = LISTinit();
}

/*Funcao auxiliar usada internamente para deletar uma entidade de fato.*/
void _freeEntity(Item d)
{
	Entity ent = (Entity)d;

	/*Antes de liberar a entidade em si, temos que liberar cada struct que ela contem.*/
	free( ent->posicao );
	free( ent->velocidade );
	if (ent->clearData != NULL && ent->data != NULL)   /*Incluindo, se possivel, o Item data.*/
	{
		ent->clearData(ent->data);

	}
	free(ent);
	ent = NULL;
}

/*Termina o gerenciador de entidades, destruindo todas entidades e liberando toda memoria.*/
void terminaEntidades()
{
    LISTfree(garbageList, NULL);
	LISTfree(entityList, _freeEntity);
}

/****************************************************
 Funcoes de uma Entidade
*****************************************************/
/*Cria uma entidade nova com os parametros passados.*/
Entity criaEntidade(Vetor pos, Vetor vel, int mass, Item data, unsigned int raio, ENT_TYPE tipo, unsigned long cor,
                    void (*updateEntLogic)(Entity ent, double deltaTime),
			 		void (*drawEntity)(Entity ent),
			 		void (*funcColidiuCom)(Entity ent, Entity aux, double deltaTime),
			 		void (*clearData)(Item data) )
{
	Entity ent = malloc( sizeof(struct _entity));
	ent->posicao = pos;
	ent->velocidade = vel;
	ent->massa = mass;
	ent->ID = nextID++;
	ent->raio = raio;
	ent->tipo = tipo;
	ent->estaColidindo = 0;
	ent->color = cor;
	ent->updateEntityLogic = updateEntLogic;
	ent->drawEntity = drawEntity;
	ent->colidiuCom = funcColidiuCom;
	ent->clearData = clearData;
	ent->data = data;
	LISTpush(entityList, ent);  /*Criamos e ja adicionamos a entidade na lista de entidades.*/
	return ent;
}

/*Funcao auxiliar usada internamente para comparar 2 entidades, e dizer se elas sao iguais.*/
int compareEntities(Item d1, Item d2)
{
	return (Entity)d1 - (Entity)d2;
}

/*Destroi a entidade passada, liberando a memoria usada por ela.*/
void destroiEntidade(Entity ent)
{
	/*Remove uma entidade da lista que seja considerada igual a ent, de acordo com a funcao de comparacao passada.*/
	LISTremove(entityList, ent, compareEntities, _freeEntity );
	ent = NULL;
}

/*Seta a entidade para ser destruida no final do ciclo logico atual.*/
void setEntityToBeDestroyed(Entity ent)
{
    LISTpush(garbageList, ent);
}

/*Retorna a posicao da entidade passada.*/
Vetor getPosicao(Entity ent)
{
	if (ent == NULL)
		return NULL;
	return ent->posicao;
}

/*Retorna o vetor da velocidade da entidade passada.*/
Vetor getVelocidade(Entity ent)
{
	if (ent == NULL)
		return NULL;
	return ent->velocidade;
}

/*Retorna o valor da massa da entidade passada.*/
int getMassa(Entity ent)
{
	if (ent == NULL)
		return -1;
	return ent->massa;
}

/*Retorna o identificador unico (ID) da entidade passada.*/
unsigned int getID(Entity ent)
{
	if (ent == NULL)
		return 0;
	return ent->ID;
}

/*Retorna o raio da entidade se tratada como uma forma circular. Valor em pixels.*/
unsigned int getRaio(Entity ent)
{
    if (ent == NULL)
        return 0;
    return ent->raio;
}

/*Retorna o tipo da entidade, como definido pela enumeracao dos tipos de entidades ENT_TYPE.*/
ENT_TYPE getTipo(Entity ent)
{
	if (ent == NULL)
		return 0;
	return ent->tipo;
}

/*Retorna o valor da cor da entidade.*/
unsigned long getColor(Entity ent)
{
    if (ent == NULL)
        return 0;
    return ent->color;
}

/*Chama a funcao de tratamento de colisao da ENT passada, com os parametros passados.*/
void callColidiuCom(Entity ent, Entity aux, double deltaTime)
{
    if (ent == NULL)
        return;
    if (ent->colidiuCom != NULL)
        ent->colidiuCom(ent, aux, deltaTime);
}

/*Seta se a entidade esta em colisao ou nao. Char emColisao usado como Bool.*/
void setEstaColidindo(Entity ent, char emColisao)
{
	if (ent == NULL)
		return;
	ent->estaColidindo = emColisao;
}

/*Retorna uma bool dizendo se a entidade esta colidindo ou nao.*/
char getEstaColidindo(Entity ent)
{
	if (ent == NULL)
		return 0;
	return ent->estaColidindo;
}

/*Retorna o Item de dados extras da entidade.*/
Item getData(Entity ent)
{
	if (ent == NULL)
		return NULL;
	return ent->data;
}

/*Chama a funcao de desenho da entidade passada. */
void callDrawEntity(Entity ent)
{
    if (ent != NULL && ent->drawEntity != NULL)
		ent->drawEntity( ent );
}


/****************************************************
 Funcoes Para Execucao em todas Entidades
*****************************************************/
/*Executa a funcao passada, com o item argumento opcional passado, para todas as entidades.*/
void executeForAllEntities( void (*func)(Item ent, Item arg), Item arg  )
{
	LISTdump(entityList, func, arg );
}

/*Funcao auxiliar usada internamente para chamar a funcao de update logic de uma entidade.
  O Item argumento passado e' tido como a variacao do tempo nesse ciclo logico.*/
void _updateEntityLogic(Item entidade, Item arg)
{
	double* deltaTime;
	Entity ent;

	ent = (Entity)entidade;
	deltaTime = (double*)arg;
	if (ent->updateEntityLogic != NULL)
		ent->updateEntityLogic( ent, *deltaTime );
}

/*Funcao auxiliar usada internamente para chamar o destroiEntidade para o Item passado.*/
void _destroiEntidade(Item ent)
{
    destroiEntidade((Entity)ent);
}

/*Executa a funcao de update logico de todas entidades. Apos isso, destroi todas entidades que foram
  marcadas para destruicao no final do ciclo logico atual.*/
void updateLogic(double deltaTime)
{
	LISTdump(entityList, _updateEntityLogic, &deltaTime );

	LISTclear(garbageList, _destroiEntidade);
}

/*Funcao auxiliar usada internamente para chamar a funcao de desenho (update grafico) de uma entidade.
  O Item argumento nao e' usado.*/
void _updateEntityDraw(Item entidade, Item arg)
{
	Entity ent = (Entity)entidade;
	if (ent->drawEntity != NULL)
		ent->drawEntity( ent );
}

/*Executa a funcao de desenho (update grafico) de todas entidades.*/
void updateDesenho()
{
	LISTdump(entityList, _updateEntityDraw, NULL );
}


/****************************************************
 Funcoes Auxiliares
*****************************************************/
/*Retorna a entidade que seja considerada igual ao Item arg(umento) de acordo com a funcao de comparacao passada.
  Esta funcao sera usada para comparar o arg com cada entidade ent da lista de entidades, e devera retornar 0 caso sejam iguais.*/
Entity getEntity(Item arg, int (*compareFunc)(Item arg, Item ent))
{
	return (Entity)LISTgetItem(entityList, arg, compareFunc );
}

/*Funcao auxiliar usada internamente para comparar uma entidade com um ID, retornando 0 caso a entidade passada seja a do ID passado.*/
int compareEntityID(Item arg, Item ent_i)
{
	int* ID;
	Entity ent;

	ID = (int*)arg;
	ent = (Entity)ent_i;

	if (ent->ID == *ID)
		return 0;
	return 1;
}

/*Retorna a entidade com o ID passado.*/
Entity getEntityByID(int ID)
{
	return getEntity(&ID, compareEntityID);
}

/*Funcao auxiliar usada internamente para comparar uma entidade com um vetor posicao, retornando 0 caso a entidade passada esteja
  posicionada no mesmo vetor.*/
int compareEntityPos(Item arg, Item ent_i)
{
	Vetor pos, entPos;
	Entity ent;

	pos = (Vetor)arg;
	ent = (Entity)ent_i;
	entPos = getPosicao(ent);

	if ( CalcDist( pos, entPos) <= getRaio(ent)+10 )
		return 0;
	return 1;
}

/*Retorna a entidade com o vetor posicao passada.*/
Entity getEntityByPositionVector(Vetor pos)
{
	return getEntity(pos, compareEntityPos);
}

/*Retorna a entidade com a posicao passada como X e Y direto.*/
Entity getEntityByPosition(double x, double y)
{
	Entity ent;
	Vetor pos = VETORinit(x, y);
	ent = getEntityByPositionVector(pos);
	free(pos);
	return ent;
}

/*Retorna a contagem de entidades vivas atualmente.*/
int getEntityCount()
{
    return LISTcount(entityList);
}

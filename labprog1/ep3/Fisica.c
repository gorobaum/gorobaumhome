/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Fisica.c - implementacao das funcoes de fisica.

Caio Costa Salgado        #USP: 6920219
Fernando Omar Aluani      #USP: 6797226
Thiago de Gouveia Nunes   #USP: 6797289

entrega: 10/05/2010
Testado no Windows7 (somente compilacao) e Linux (Debian - compilando e rodando)
Compilando com o Makefile incluido (make)
***************************************************/


/****************************************************
 Os includes básicos...
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Entity.h"
#include "Fisica.h"
#include "Estat.h"
#include "Desenho.h"


/****************************************************
 Constantes usadas nesse arquivo
*****************************************************/
#define MAX_OCEANO_X 1024
#define MAX_OCEANO_Y 768
#define MIN_OCEANO 0
#define OFFSET_RAIO 0.0


/****************************************************
 Implementacao das Struct/Tipos.
*****************************************************/
/*Representa um vetor 2D no plano cartesiano R2*/
typedef struct vetor
{
	double x;
	double y;
} _vetor;

/*Struct usada para auxiliar na checagem de colisoes, contendo informacoes pertinentes.*/
typedef struct colisao
{
	Entity ent;        /*A entidade para a qual estamos testando todas as outras para ver se colidem.*/
	double DeltaTime;  /*Variacao de tempo desse ciclo logico.*/
    short podeChecar;  /*Usado como bool dizendo se ja podemos checar por colisoes.*/
} _colisao;



/****************************************************
 Funcoes de Vetores
*****************************************************/
/*Inicializa e retorna um vetor novo com os valores passados.*/
Vetor VETORinit(double x, double y)
{
	Vetor v = malloc( sizeof(struct vetor) );
	v->x = x;
	v->y = y;
	return v;
}

/*Retorna a componente X do vetor passado.*/
double getX( Vetor v )
{
	return v->x;
}

/*Retorna a componente Y do vetor passado.*/
double getY(Vetor v)
{
	return v->y;
}

/*Altera o valor do componente X do vetor passado, com o novo valor dado.*/
void setX( Vetor v, double newX )
{
	v->x = newX;
}

/*Altera o valor do componente Y do vetor passado, com o novo valor dado.*/
void setY( Vetor v, double newY )
{
	v->y = newY;
}

/*Retorna o modulo do vetor dado.*/
double VETORmodulo( Vetor v )
{
	return sqrt( pow(v->x, 2) + pow(v->y, 2) );
}

/*Retorna a distancia entre os 2 vetores passados.*/
double CalcDist( Vetor v1, Vetor v2 )
{
	double DeltaX, DeltaY, Dist;

	DeltaX = (v2->x - v1->x);
	DeltaY = (v2->y - v1->y);
	Dist = sqrt ( pow( DeltaX, 2.0 ) + pow( DeltaY, 2.0 ) );

	return Dist;
}

/*Soma o vetor B no vetor A.*/
void VETORadd(Vetor A, Vetor B)
{
	A->x = (A->x) + (B->x);
	A->y = (A->y) + (B->y);
}

/*Subtrai o vetor B do vetor A.*/
void VETORsubtract(Vetor A, Vetor B)
{
	A->x = (A->x) - (B->x);
	A->y = (A->y) - (B->y);
}

/*Calcula o produto interno (escalar) entre dois vetores.*/
double VETORprodutoInterno(Vetor A, Vetor B)
{
	return getX(A)*getX(B) + getY(A)*getY(B);
}

/*Multiplica o vetor por um valor escalar.*/
void VETORscale(Vetor v, double f)
{
	v->x = (v->x) * f;
	v->y = (v->y) * f;
}

/*Normaliza o vetor passado.*/
void VETORnormalize(Vetor v)
{
	double m = VETORmodulo(v);
	if (m > 0)
	{
		v->x = (v->x) / m;
		v->y = (v->y) / m;
	}
}

/*Arredonda o double passado para o inteiro mais proximo.*/
int round(double x)
{
	int sign, i;

	sign = -2*(x < 0) + 1;
	i = abs( (int)x );

	if ( fabs(x) - i > 0.5 )
		return sign*(i+1);
	else
		return sign*i;
}


/****************************************************
 Funcoes Relativas ao posicionamento e velocidade de entidades.
*****************************************************/
/*Funcao auxiliar usada internamente para retornar a posicao no eixo X para onde a entidade ira.*/
double atualizaPosicaoX( Entity ent, double DeltaTime )
{
	Vetor VetEspaco, VetVelocidade;

	VetEspaco = getPosicao( ent );
	VetVelocidade = getVelocidade( ent );
	return ( (VetEspaco->x) + ((VetVelocidade->x) * DeltaTime) );
}

/*Funcao auxiliar usada internamente para retornar a posicao no eixo Y para onde a entidade ira.*/
double atualizaPosicaoY( Entity ent, double DeltaTime )
{
	Vetor VetEspaco, VetVelocidade;

	VetEspaco = getPosicao( ent );
	VetVelocidade = getVelocidade( ent );
	return ( (VetEspaco->y) + ((VetVelocidade->y) * DeltaTime) );
}

/*Atualiza a posicao da entidade de acordo com sua variacao de movimento (dada pela velocidade e variacao de tempo DeltaTime).*/
void atualizaPosicao( Entity ent, double DeltaTime )
{
	Vetor VetAux;

	VetAux = getPosicao( ent );
	VetAux->x = atualizaPosicaoX( ent, DeltaTime );
	VetAux->y = atualizaPosicaoY( ent, DeltaTime );
}

/*Funcao para "colidir" duas entidades, corrigindo suas velocidades de acordo com suas velocidades anteriores, massa
  e coeficiente de restituicao da colisao (passado como argumento - CoefRest, devendo estar enter 0 e 1). */
void atualizaVelocidade( Entity ent1, Entity ent2, double CoefRest )
{
	Vetor v1, v2, aux;
	double Vel[4], m[2], Qx, Qy, massaTotal, m1, m2;

	v1 = getVelocidade( ent1 );
	v2 = getVelocidade( ent2 );
	m[0] = (double)getMassa( ent1 );
	m[1] = (double)getMassa( ent2 );
	Vel[0] = v1->x;
	Vel[1] = v1->y;
	Vel[2] = v2->x;
	Vel[3] = v2->y;

	Qx = m[0]*Vel[0] + m[1]*Vel[2];
	Qy = m[0]*Vel[1] + m[1]*Vel[3];
	massaTotal = m[0] + m[1];

    aux = VETORinit(0.0, 0.0);

	aux->x = (Qx + m[1]*CoefRest*(Vel[2] - Vel[0])) / massaTotal;
	aux->y = (Qy + m[1]*CoefRest*(Vel[3] - Vel[1])) / massaTotal;
	m1 = VETORmodulo(aux);

	aux->x = (Qx + m[0]*CoefRest*(Vel[0] - Vel[2])) / massaTotal;
	aux->y = (Qy + m[0]*CoefRest*(Vel[1] - Vel[3])) / massaTotal;
	m2 = VETORmodulo(aux);

	calculaDirecoesColisao(ent1, ent2);

    VETORnormalize(v1);
	VETORnormalize(v2);

	VETORscale(v1, m1);
	VETORscale(v2, m2);

	free(aux);
}



/****************************************************
 Funcoes Relativas a Colisoes
*****************************************************/
/*Funcao auxiliar usada internamente para checar se as duas entidades passadas irao colidir no proximo ciclo logico.
  Assume que uma delas esta parada, e a outra se mexendo, entao preve onde essa entidade estara e se estara proxima
  da outra entidade.*/
int checaColisao( Entity entQueMove, Entity entParada, double DeltaTime )
{
	Vetor VetAuxQueMove, VetAuxParada;
	double RaioDoCirculo, dist;

	atualizaPosicao(entQueMove, DeltaTime);
	VetAuxQueMove = getPosicao( entQueMove );

	atualizaPosicao(entParada, DeltaTime);
	VetAuxParada = getPosicao( entParada );

	RaioDoCirculo = getRaio(entQueMove) + getRaio(entParada) + OFFSET_RAIO;

	dist = CalcDist( VetAuxQueMove, VetAuxParada );

    atualizaPosicao(entParada, -DeltaTime);
	atualizaPosicao(entQueMove, -DeltaTime);

	if (dist <= RaioDoCirculo)
	{
	    if (getTipo(entQueMove) == PASS && getTipo(entParada) == PASS)
            return 1;
	    else if ( checkIntersecaoDeFormas(entQueMove, entParada) == 1)
            return 1;
	}
	return 0;
}

/*Funcao auxiliar usada internamente para completar o loop da checagem de colisao.
  Aux e' um objeto da struct Colisao, contendo as informacoes necessarias para fazermos o que devemos fazer.*/
void colisaoDeEntities( Item AuxEnt, Item Aux )
{
	Colisao AuxColi = (Colisao)Aux;
	Entity ent = (Entity)AuxEnt;

    /*Esse loop comeca com podeChecar = 0, porem quando chegamos no ponto de ver se uma entidade esta colidindo com ela mesma
      setamos podeChecar = 1.
      Fazemos isso porque a lista das entidades eh fixa, e nao muda durante a checagem das colisoes.
      Se a lista estiver, por exemplo, na forma {A, B, C, D, E}, quando chegar no ponto de AuxColi->ent ser C, devemos
      testar se C colidi com todas as outras entidades. Porem, antes quando fizemos o mesmo teste para a entidade A
      ja checamos se A colide com C, e nao precisamos fazer isso dinovo. E tambem nao precisamos ver se C colide com C,
      portanto simplesmente ignoramos todas as entidades ate a que estiver logo apos C na lista.
      Implmentamos isso com essa variavel podeChecar, e assim deixamos o loop da checagem de colisao mais eficiente. */
    if (ent == AuxColi->ent)
        AuxColi->podeChecar = 1;
	else if ( !getEstaColidindo( ent ) && !getEstaColidindo( AuxColi->ent ) && AuxColi->podeChecar == 1  )
	{
		if ( checaColisao( ent, AuxColi->ent, AuxColi->DeltaTime ) )
		{
		    /*setEstaColidindo( ent, 1 );
            setEstaColidindo( AuxColi->ent, 1 );*/
            callColidiuCom(AuxColi->ent, ent, AuxColi->DeltaTime);
		}
	}
}

/*Funcao auxiliar usada internamente usada no meio do loop de checagem de colisoes.
  Ela equivale ao segundo FOR do loop (o FOR dentro do outro), executando a funcao colisaoDeEntities para
  cada dupla de entidades no jogo.
  Note que antes de checar se a ent ira colidir com qualquer outra entidade, ela checa se a entidade
  ira sair da tela, o que e' tratado como uma colisao entre 2 entidades (ent, NULL)*/
void colisaoPorEntity( Item ent_i, Item Aux )
{
	Colisao AuxColisao;
	Vetor pos;
	Entity ent;

    ent = (Entity)ent_i;
	AuxColisao = (Colisao)Aux;
	AuxColisao->ent = ent;
	AuxColisao->podeChecar = 0;

	atualizaPosicao(ent, AuxColisao->DeltaTime);
	pos = getPosicao(ent);
	if (round(getX(pos)) < 0 || round(getX(pos)) >= MAX_OCEANO_X || round(getY(pos)) < 0 || round(getY(pos)) >= MAX_OCEANO_Y)
	{
	    /*chama colisao (ent, NULL) */
	    setEstaColidindo( ent, 1 );
	    callColidiuCom(ent, NULL, AuxColisao->DeltaTime);
	    return;
	}
	atualizaPosicao(ent, -(AuxColisao->DeltaTime) );

	executeForAllEntities( colisaoDeEntities, AuxColisao );
}

/*Funcao auxiliar usada internamente para resetar o valor estaColidindo de uma entidade.*/
void _resetEntityColidindo( Item ent_i, Item notUsed )
{
	Entity ent = (Entity)ent_i;
	setEstaColidindo( ent, 0 );
}


/*Realiza o teste geral de colisao, checando todas entidades vivas para ver se elas estao colidindo.
  Se estiverem, seta que elas estao colidindo e atualiza suas velocidades de acordo.
  Notando que o tipo de colisao e' aleatorio. O coeficiente de restituicao da colisao e' calculado aleatoriamente,
  com uma chance maior (definida pela constante CHANCE_REST no Fisica.c) de ser uma colisao elastica.

  Como a lista de entidades da interface Entity nao so' nao e' aberta diretamente a nos, ela tambem e' uma lista
  ligada. Portanto, nao podemos simplesmente fazer um FOR duplo. Mas gracas a uma funcao muito util da interface Entity,
  podemos fazer algo muito parecido, executando uma dada funcao para cada entidade na lista. Assim, recriamos de um jeito
  um pouco estranho o FOR duplo ao executar uma dada funcao para cada entidade dentro de outra funcao que esta sendo
  executada para cada entidade na lista.

  Em suma, traduzindo isso nosso loop da checagem da colisao e' algo assim:

  for ( i = 0;  i < numero_de_entidades; i++)  (funcao colisaoGeral/colisaoPorEntity)
     for (j = i;  j < numero_de_entidades;  j++)  (funcao colisaoPorEntity/colisaoDeEntities)
         checaColisao( lista_de_entidades[i],  lista_de_entidades[j])
         ...  */
void colisaoGeral( double DeltaTime )
{
    Colisao AuxColisao;

    /*Antes resetamos o valor estaColidindo de todas entidades no jogo.*/
	executeForAllEntities( _resetEntityColidindo, NULL );

    /*Alocamos o objeto da struct Colisao que usaremos para passar os argumentos necessarios as outras funcoes
      usadas durante o loop.*/
    AuxColisao = malloc(sizeof(_colisao));
	AuxColisao->ent = NULL;
	AuxColisao->DeltaTime = DeltaTime;
	AuxColisao->podeChecar = 0;

    /*Entao executamos o loop.*/
	executeForAllEntities( colisaoPorEntity, AuxColisao );

    /*E finalmente deletamos o Colisao usado.*/
    AuxColisao->ent = NULL;
	free(AuxColisao);
}

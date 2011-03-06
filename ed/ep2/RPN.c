/***********************************************************************************************************

MAC323 - Estrutura de Dados
IME - USP - Primeiro semestre de 2010
Prof - Ronaldo Fumio Hashimoto

Primeiro Exercicio-programa
Arquivo EP2.c

Aluno:									Numero USP:Thiago G. Nunes							6797289

09/05/2010

***********************************************************************************************************/

#include <string.h>
#include "RPN.h" 

typedef struct ramo* pRamo;

typedef struct ramo 
{
	LL linked;
	pRamo Bef;
} ramo;

typedef struct stack 
{
	pRamo Top;
	int Tam;
}stack;

LL STACKget( Pilha p ) 
{
	LL l;
	pRamo Aux;
	
	if ( !STACKempty( p ) )
	{
		l = LLinit();
		l = (p->Top)->linked;
		Aux = p->Top;
		p->Top = Aux->Bef;
		(p->Tam)--;
		free(Aux);
		return l;
	}
	
	return NULL;
}

int STACKsize( Pilha p )
{
	return p->Tam;
}

LL STACKpeek( Pilha p )
{	
	if ( p->Top != NULL ) return p->Top->linked;
	else return NULL;
}

int STACKempty( Pilha p ) 
{
	return (p->Top == NULL);
}

void STACKrelivetop( Pilha p )
{
	pRamo Aux;
	
	if ( !STACKempty( p ) ) 
	{
		Aux = p->Top;
		p->Top = p->Top->Bef;
		(p->Tam)--;
		free(Aux);
	}
}	

void STACKput( Pilha p, LL l )
{
	pRamo ramo;
	
	ramo = malloc(sizeof(ramo));
	if ( ramo == NULL )
	{
		printf("O ramo nao pode ser alocado. \n");
		exit(0);
	}
	ramo->linked = LLinit();
	ramo->linked = l;
	
	ramo->Bef = p->Top;
	p->Top = ramo;
	(p->Tam)++;
}

Pilha STACKinit(int n) 
{
	Pilha p;
	
	p = malloc(sizeof(stack));
	if ( p == NULL )
	{
		printf("A pilha nao pode ser alocado. \n");
		exit(0);
	}
	p->Top = NULL;
	p->Tam = 0;

	return p;
}

void STACKdestroy( Pilha p )
{
	pRamo Aux1, Aux2;
	
	Aux1 = p->Top;
	Aux2 = p->Top->Bef;
	
	while ( Aux2 != NULL )
	{
		free( Aux1 );
		Aux1 = Aux2;
		Aux2 = Aux2->Bef;
	}
	
	free( Aux1 );
	free( p );
}

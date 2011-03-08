/********************************************************
MAC 211 - Laboratorio de Programacao I
Projeto: Naufrago
Exercicio-Programa 2:  Primeira Fase
Desenho.c - implementa as rotinas para desenho do jogo.

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
#include <allegro.h>

#include "Desenho.h"
#include "Fisica.h"
#include "Entity.h"
#include "Lista.h"


/****************************************************
 Atributos e Variaveis Globais da Interface
*****************************************************/

/*Lembrando que a plano cartesiano no oceano (na tela) e':

  (0,0) --------> (X,0)
    |               |
    |               |
    V               V
  (0,Y) --------> (X,Y)         */


BITMAP* buffer;            /*Nosso bitmap interno para desenho, e' equivalente a janela do programa*/
BITMAP* auxInter;          /*Bitmap auxiliar usado na deteccao de interseccao de formas.*/
short checandoInterseccao; /*Boolean dizendo se estamos checando interseccao de formas ou nao.*/
short interOk;             /*Boolean dizendo se encontramos uma interseccao entre as formas ou nao.*/
S pontosInter;             /*Lista de pontos da ultima interseccao.*/

/*Struct auxiliar usada para armazenar o valor da base e altura de alguma forma geometrica, em pixels.*/
typedef struct rectangle
{
	int base;
	int altura;
} _rectangle;

/****************************************************
 Funcoes Principais da Interface
*****************************************************/
/*Funcao para inicializar os atributos usados internamente por esse script.*/
void inicializaDesenho()
{
    checandoInterseccao = interOk = 0;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    auxInter = create_bitmap(SCREEN_W, SCREEN_H);
	pontosInter = LISTinit();
}

/*Funcao para terminar esse modulo de desenho, liberando toda memoria usada por ele.*/
void terminaDesenho()
{
	LISTfree(pontosInter, clearSimpleData);
    destroy_bitmap(buffer);
    destroy_bitmap(auxInter);
}



/****************************************************
 Funcoes Principais pro Ciclo de Update Grafico
*****************************************************/
/*Funcao para prepara a interface para um novo ciclo de desenho.*/
void preparaPraDesenho()
{
    clear_to_color(buffer, makecol(0,200,255)); /* limpa o buffer para branco...*/

    /*Para ter certeza que o Allegro estara no modo certo de desenho que usamos, o setamos aqui.*/
    solid_mode();
}

/*Funcao principal para desenhar os graficos na tela.
  Como usamos double-buffering, todo o desenho real das entidades e etc e' feito numa memoria separada (num buffer),
  e com essa funcao esse buffer e' desenhado de uma vez so' na tela.*/
void updateScreen()
{
    acquire_screen();
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();
}



/****************************************************
 Funcoes de Desenho
*****************************************************/
/*Desenha um circulo cheio na tela, com centro na posicao passada, com raio e cor passados.*/
void drawCircle(Vetor pos, int raio, unsigned long cor)
{
    int x, y;

    x = round( getX(pos) );
    y = round( getY(pos) );
	if (x >= 0 && x < SCREEN_W && y >= 0 && y < SCREEN_H)
	{
	    if (checandoInterseccao == 0)
            circle(buffer, x, y, raio, cor);
        else
            circle(auxInter, x, y, raio, makecol(126+checandoInterseccao, 126+checandoInterseccao, 126+checandoInterseccao));
	}
}

/*Desenha um triangulo isosceles cheio com a cor passada na tela, com seu centro na posicao dada pelo vetor pos,
  direcionado de acordo com o vetor dir passado (logo a base do vetor fica perpendicularmente na direcao contraria),
  de acordo com a altura e base passados. */
void drawTriangle(Vetor pos, Vetor dir, Rect medidas, unsigned long cor)
{
    int posX[3], posY[3], i, base, altura;
    double Dm, Dx, Dy, offset;

    base = medidas->base;
    altura = medidas->altura;

	if (getX(pos) >= 0 && getX(pos) < SCREEN_W && getY(pos) >= 0 && getY(pos) < SCREEN_H)
	{
	    /*Antes de desenhar temos que calcular os 3 vertices do triangulo, com um pouco de conta de vetores...*/
		Dx = getX(dir);
		Dy = getY(dir);
	    Dm = VETORmodulo(dir);
		if (Dm <= 0)
		{
			Dx = 0;
			Dy = -1;
			Dm = 1;
		}

	    /*O primeiro ponto do triangulo e' o vertice da frente, adquirido adicionando o vetor direcao, normalizado e
	      escalado pela distancia do centro a ele ( 2/3 da altura) 'a posicao passada (que e' o centro do triangulo).*/
	    posX[0] = round( getX(pos) + (getX(dir)/Dm)*2*altura/3 );
	    posY[0] = round( getY(pos) + (getY(dir)/Dm)*2*altura/3 );

	    for (i=0; i<2; i++)
	    {
	        /*Lembrando que se V=(a, b), o vetor normal a ele e' (-b, a)  */
	        offset = -(getY(dir)/Dm)*base/2 * (-1 + 2*(i==0));
	        posX[i+1] = round( getX(pos) - (getX(dir)/Dm)*altura/3 + offset);
	        offset =  (getX(dir)/Dm)*base/2 * (-1 + 2*(i==0));
            posY[i+1] = round( getY(pos) - (getY(dir)/Dm)*altura/3 + offset);
	    }

        if (checandoInterseccao == 0)
		{
            /*triangle(buffer, posX[0], posY[0], posX[1], posY[1], posX[2], posY[2], cor);*/
            line(buffer, posX[0], posY[0], posX[1], posY[1], cor);
            line(buffer, posX[1], posY[1], posX[2], posY[2], cor);
            line(buffer, posX[0], posY[0], posX[2], posY[2], cor);
		}
        else
        {
            cor = makecol(126+checandoInterseccao, 126+checandoInterseccao, 126+checandoInterseccao);
            /*triangle(auxInter, posX[0], posY[0], posX[1], posY[1], posX[2], posY[2], cor);*/
            line(auxInter, posX[0], posY[0], posX[1], posY[1], cor);
            line(auxInter, posX[1], posY[1], posX[2], posY[2], cor);
            line(auxInter, posX[0], posY[0], posX[2], posY[2], cor);
        }
	}
}

/*Desenha um retangulo cheio na tela, com base, altura e cor passados, centrado na posicao dada.*/
void drawRect(Vetor pos, Rect medidas, unsigned long cor)
{
    int x1, x2, y1, y2;
    int base, altura;

    base = medidas->base;
    altura = medidas->altura;

	if (getX(pos) >= 0 && getX(pos) < SCREEN_W && getY(pos) >= 0 && getY(pos) < SCREEN_H)
	{
	    x1 = getX(pos) - base/2;
	    y1 = getY(pos) - altura/2;

	    x2 = getX(pos) + base/2;
	    y2 = getY(pos) + altura/2;

        if (checandoInterseccao == 0)
            rect(buffer, x1, y1, x2, y2, cor);
        else
            rect(auxInter, x1, y1, x2, y2, makecol(126+checandoInterseccao, 126+checandoInterseccao, 126+checandoInterseccao));
	}
}


/****************************************************
 Funcoes Auxiliares
*****************************************************/
/*Funcao auxiliar para transformar um valor RGB num inteiro representando uma cor (como o Allegro usa).
  E' um simples wrapper para uma funcao do Allegro, pois nao quero ter que incluir o Desenho.h e o Allegro em varios
  arquivos, so' por causa dessa funcao, portanto aqui estamos...*/
unsigned long makecolor(short R, short G, short B)
{
    return makecol(R, G, B);
}

/*Cria um Rect com os parametros passados.*/
Rect criaRect(int base, int altura)
{
    Rect r = malloc( sizeof(struct rectangle) );
    r->base = base;
    r->altura = altura;
    return r;
}

/*Retorna o valor da base do Rect passado.*/
int getBase(Rect r)
{
    if (r == NULL)
        return 0;
    return r->base;
}

/*Retorna o valor da Altura do Rect passado.*/
int getAltura(Rect r)
{
    if (r == NULL)
        return 0;
    return r->altura;
}

/*Funcao auxiliar usada internamente para especificar o calculo matematico para criar um efeito de
  blending proprio de cores.*/
unsigned long InterBlender(unsigned long x, unsigned long y, unsigned long n)
{
    return x - y;
}

/*Funcao auxiliar usada internamente para checar se um pixel e' (ou esta perto) da cor preta.
  Usada pela funcao checkIntersecaoDeFormas, essa funcao e' chamada varias vezes, pra cada ponto em multiplos
  circulos, para ver se ha ocorrencia da cor preta.*/
void checkCorPreta(BITMAP *bmp, int x, int y, int d)
{
    int r, g, b, cor;

    cor = getpixel(bmp, x, y);
    r = getr(cor);
    g = getg(cor);
    b = getb(cor);

    if (r < 5 && g < 5 && b < 5)
	{
		if (d == 1)
			LISTpush(pontosInter, VETORinit((double)x, (double)y) );
        interOk = 1;
	}
}

/*Testa as duas entidades passadas para ver se seus desenhos estao em cima um do outro, isto e', se a interseccao
  das suas formas e' diferente de nulo.
  Assim essa funcao pode ser usada para detectar colisao por pixel entre as duas entidades.

  Em suma, ela desenha as duas entidades num tom medio de cinza em um bitmap auxiliar branco, e entao checa a regiao
  entre as duas entidades para ver se ocorreu qualquer pixel preto.
  Se um pixel preto for encontrado, quer dizer que houve interseccao pois de acordo com a funcao de blender que usamos,
  desenhar uma area cinza em cima de outra cinza, sob um fundo branco, fara que a area da interseccao fique preta.*/
short checkIntersecaoDeFormas(Entity e1, Entity e2)
{
    int x, y, i;
    Vetor pos1, pos2;

    /*Comecamos preparando-nos para desenhar com nossa funcao de blender, para desenhar as formas com transparencia...*/
    set_blender_mode(InterBlender, InterBlender, InterBlender, 0, 0, 0, 0);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

    /*Limpamos nosso buffer auxiliar, onde desenharemos as entidades...*/
    clear_to_color(auxInter, makecol(255,255,255));

    /*E entao as desenhamos.*/
    checandoInterseccao = 1;
    callDrawEntity(e1);
    checandoInterseccao = 2;
    callDrawEntity(e2);
    checandoInterseccao = 0;

    pos1 = getPosicao(e1);
    pos2 = getPosicao(e2);
    x = round( (getX(pos1)+getX(pos2))/2.0 );
    y = round( (getY(pos1)+getY(pos2))/2.0 );

    interOk = 0;
    for (i=1; i<((getRaio(e1)+getRaio(e2))/2); i++)
    {
        do_circle(auxInter, x, y, i, 0, checkCorPreta);
        if (interOk == 1)
            return 1;
    }
    return 0;
}

/*Funcao auxiliar usada pelo calculaDirecoesColisao para adquirir o ponto medio dessa lista de pontos.*/
void somaVetores(Item d, Item arg)
{
	Vetor p, m;

	p = (Vetor)d;
	m = (Vetor)arg;

	VETORadd(m, p);
}

/*Funcao auxiliar usada pelo calculaDirecoesColisao para alterar a direcao de uma entidade.*/
void alteraDirecao(Entity ent, Vetor normal)
{
	Vetor pos, dir, proj;
	double prodInterno, modNormal, modDir;

    printf("mark 1 \n");
	pos = getPosicao(ent);
	dir = getVelocidade(ent);

    printf("mark 2 \n");
	modDir = VETORmodulo(dir);
    printf("NORMAL = (%f, %f)[%f]\n", getX(normal), getY(normal), VETORmodulo(normal));
	VETORnormalize(normal);
    printf("NORMAL unitaria = (%f, %f)[%f]\n", getX(normal), getY(normal), VETORmodulo(normal));
    modNormal = VETORmodulo(normal);
    printf("Dir inicial = (%f, %f)[%f]\n", getX(dir), getY(dir), VETORmodulo(dir));
	VETORnormalize(dir);
    printf("Dir unitaria = (%f, %f)[%f]\n", getX(dir), getY(dir), VETORmodulo(dir));
	/*VETORscale(normal, -1.0);*/
	prodInterno = VETORprodutoInterno(dir, normal);

    printf("mark 3 (modNormal = %f) (prodInterno = %f)\n", modNormal*modNormal, prodInterno);
	/*Calculando a projecao da velocidade (dir) na reta normal.*/
	proj = VETORinit(0.0, 0.0);
	VETORadd(proj, normal);
	VETORscale(proj, prodInterno);
	/*setX(proj, prodInterno*getX(normal)/(modNormal*modNormal) );
	setY(proj, prodInterno*getY(normal)/(modNormal*modNormal) );
	VETORadd(proj, pos);*/

    printf("mark 4 ---> Proj = (%f, %f)[%f]\n", getX(proj), getY(proj), VETORmodulo(proj));
	/*Agora, para adquirir a direcao certa, basta subtrair a projecao da direcao, e adicionar o oposto da projecao na direcao.*/
	/*VETORsubtract(dir, proj);
    printf("Dir (-proj) = (%f, %f)[%f]\n", getX(dir), getY(dir), VETORmodulo(dir));*/
	VETORscale(proj, -1.0);
	VETORadd(dir, proj);
	VETORadd(dir, proj);
    printf("Dir (+proj_i) = (%f, %f)[%f]\n", getX(dir), getY(dir), VETORmodulo(dir));

	VETORnormalize(dir);
    printf("Dir final unitario = (%f, %f)[%f]\n", getX(dir), getY(dir), VETORmodulo(dir));
    printf("mark 5 \n");
    VETORscale(dir, modDir);
    printf("Dir final = (%f, %f)[%f]\n", getX(dir), getY(dir), VETORmodulo(dir));

    printf("mark 6 \n");
	free(proj);

}

/*Usada pela colisao, essa funcao auxiliar server para alterar a direcao da velocidade das duas entidades
  apos uma colisao, de acordo com suas formas geometricas (possivelmente diferentes) e etc.*/
void calculaDirecoesColisao(Entity e1, Entity e2)
{
    int x, y, i;
    Vetor pos1, pos2, normal;

	/*E' estranho, e provavelmente nao o jeito mais eficiente de fazer isso, mas para calcular as direcoes novas
	  executamos o algoritmo da checkIntersecaoDeFormas novamente, mas agora armazenando os pontos onde houve a intersecao
	  das entidades, pois precisamos deles para calcular o ponto da colisao, a reta normal, tangente, etc...*/

    /*Comecamos preparando-nos para desenhar com nossa funcao de blender, para desenhar as formas com transparencia...*/
    set_blender_mode(InterBlender, InterBlender, InterBlender, 0, 0, 0, 0);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

    /*Limpamos nosso buffer auxiliar, onde desenharemos as entidades...*/
    clear_to_color(auxInter, makecol(255,255,255));

    /*E entao as desenhamos.*/
    checandoInterseccao = 1;
    callDrawEntity(e1);
    checandoInterseccao = 2;
    callDrawEntity(e2);
    checandoInterseccao = 0;

    pos1 = getPosicao(e1);
    pos2 = getPosicao(e2);
    x = round( (getX(pos1)+getX(pos2))/2.0 );
    y = round( (getY(pos1)+getY(pos2))/2.0 );

    interOk = 0;
	LISTclear(pontosInter, clearSimpleData);
    for (i=1; i<((getRaio(e1)+getRaio(e2))/2); i++)
    {
        do_circle(auxInter, x, y, i, 1, checkCorPreta);
        if (interOk == 1)
            break;
    }

	/*Agora que temos os pontos da intersecao, vamos a proxima parte: calcular as direcoes.*/
    normal = VETORinit(0.0, 0.0);
	if (LISTcount(pontosInter) <= 0)
	{
		/*Nao temos pontos de intersecao, mas estamos colidindo... Quer dizer que sao dois passageiros colidindo,
		  ou seja, dois circulos. Achar o ponto medio e' facil:*/
        VETORadd(normal, pos2);
        VETORsubtract(normal, pos1); /*Vetor direcao do pos1 --> pos2 */
        VETORnormalize(normal);
        VETORscale(normal, getRaio(e1)); /*Vetor direcao pos1 --> pos2 com modulo = raio da e1 */
        VETORadd(normal, pos1);          /*pMedio = ponto entre e1 e e2*/
	}
	else
	{
        LISTdump(pontosInter, somaVetores, normal );
        setX(normal,  getX(normal)/(double)LISTcount(pontosInter) );
        setY(normal,  getY(normal)/(double)LISTcount(pontosInter) );
	}
    /*Com isso, normal e' o vetor representando o ponto medio entre as duas unidades, ou seja,
     o ponto central da colisao. Basta subtrair a posicao de uma ent que ele sera' o vetor normal
     'a superficie da colisao (ou 'a reta tangente das formas no ponto da colisao)*/

	if (getTipo(e1) == PASS)  /*PASS colidindo com algo, assim e' melhor*/
	    VETORsubtract(normal, pos1);
	else if (getTipo(e2) == PASS)  /*algo nao-pass colidiu com um pass */
	{
		VETORsubtract(normal, pos2);
		VETORscale(normal, -1.0);
	}
	else if (getTipo(e1) == BOTE)
	{
		
	}

	alteraDirecao(e1, normal);
	VETORscale(normal, -1.0);
	alteraDirecao(e2, normal);

	free(normal);
}

/*Usada pela colisao, essa funcao auxiliar server para alterar a direcao da velocidade de uma entidade
  apos uma colisao com a parede.*/
void calculaDirecaoColisaoParede(Entity ent)
{
    Vetor pos, normal;

    pos = getPosicao(ent);

	/*Agora que temos os pontos da intersecao, vamos a proxima parte: calcular as direcoes.*/
	if (round(getX(pos)) < 0)
	    normal = VETORinit(0.0, getY(pos));
	else if (round(getX(pos)) >= SCREEN_W)
	    normal = VETORinit(SCREEN_W, getY(pos));
	else if (round(getY(pos)) < 0)
	    normal = VETORinit(getX(pos), 0.0);
	else if (round(getY(pos)) >= SCREEN_H)
	    normal = VETORinit(getX(pos), SCREEN_H);
	else
	{
		/*erro...*/
		return;
	}

    /*Com isso, normal e' o vetor representando o ponto da "colisao" com a parede.
      Basta subtrair a posicao da ent que ele sera' o vetor normal 'a superficie da colisao
      (ou 'a reta tangente das formas no ponto da colisao)*/

    VETORsubtract(normal, pos);
	alteraDirecao(ent, normal);

	free(normal);
}

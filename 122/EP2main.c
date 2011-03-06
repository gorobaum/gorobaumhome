/*
MAC 122 - Principio de Desenvolvimento de Algoritmos
Exercicio-Programa 2:  Fractais

Fernando Omar Aluani
#USP: 6797226

entrega: 3/10/2009
Testado no Linux (Ubuntu)
Compilando com: -Wall -ansi -pedantic -std=c99 -lglut -lm
*/

/*Parte deste código foi retirado de http://mindfuck.de-brauwer.be/articles/glut/ */

/*
Includes...
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/*
Definiçoes e variaveis globais.
*/

#define PI 3.1415926535897931 /*Valor do PI proveniente da calculadora do computador.*/

/*Identificador da janela e seu comprimento e largura. */
static int win;
static int width = 500;
static int height = 500;
/*Identificadores dos menus*/
static int menuID;
static int basesMenu;
static int modelosMenu;
static int recursaoMenu;
static int coresMenu;

/*Variaveis globais usadas pelo programa*/
static short DO_DISPLAY;          /*usado como uma bool, para controlarmos se podemos ou nao atualizar a imagem da janela.*/
static short DO_SWAP;             /*tambem uma bool, para controlarmos se podemos ou nao dar swapBuffers quando o programa estiver Idle.*/
static short nivelRecursao = 0;   /*o nivel de recursao do fractal atual.*/
static short TIPO_BASE = -1;      /*o tipo da base (os valores possiveis sao os mesmos passados para a funcao de menu basesMenuClick.*/
static double anguloBase = 0.0;   /*Angulo entre 2 segmentos consecutivos da base (um poligono regular).*/
static short TIPO_MODELO = -1;    /*o tipo do modelo (os valores possiveis sao os mesmos passados para a funcao de menu modelosMenuClick.*/
static short USE_MULTI_COR = 0;   /*Se eh para usarmos cores variadas e aleatorias no desenho do fractal.*/

/*Array de matrizes contendo a informaçao de construçao dos modelos.*/
double infoModelos[8][33][2] = {
	{ /*Koch triadrico*/
		{4, 0},              /*A primeira linha eh usada somente para guardar o numero de segmentos que este modelo contem.*/
		{0.0,     1.0/3.0},  /**/
		{PI/3,    1.0/3.0},  /*As linhas seguintes de cada matriz sao duplas, marcando (angulo, escala)*/
		{-2*PI/3, 1.0/3.0},  /*angulo = angulo desse ponto em relacao ao anterior.*/
		{PI/3,    1.0/3.0}   /*escala = tamanho desse segmento do modelo em relacao ao segmento onde ele esta sendo colocado*/
	},
	{ /*Koch quadrico 1  (uma variacao simples do koch quadrico que nao esta no enunciado)*/
		{5, 0},
		{0.0,   1.0/3.0},
		{PI/2,  1.0/3.0},
		{-PI/2, 1.0/3.0},
		{-PI/2, 1.0/3.0},
		{PI/2,  1.0/3.0}
	},
	{ /*Koch quadrico 2*/
		{8, 0},
		{0.0,     0.25},
		{PI/2,    0.25},
		{-PI/2,   0.25},
		{-PI/2,   0.25},
		{0,       0.25},
		{PI/2,    0.25},
		{PI/2,    0.25},
		{-PI/2,   0.25}
	},
	{ /*Koch quadrico 3*/
		{32, 0},
		{PI/2,    0.125},
		{-PI/2,   0.125},
		{PI/2,    0.125},
		{PI/2,    0.125},
		{-PI/2,   0.125},
		{-PI/2,   0.125},
		{0,       0.125},
		{PI/2,    0.125},
		{-PI/2,   0.125},
		{-PI/2,   0.125},
		{0,       0.125},
		{-PI/2,   0.125},
		{PI/2,    0.125},
		{PI/2,    0.125},
		{0,       0.125},
		{-PI/2,   0.125},
		{0,       0.125},
		{PI/2,    0.125},
		{0,       0.125},
		{-PI/2,   0.125},
		{-PI/2,   0.125},
		{PI/2,    0.125},
		{0,       0.125},
		{PI/2,    0.125},
		{PI/2,    0.125},
		{-PI/2,   0.125},
		{0,       0.125},
		{PI/2,    0.125},
		{PI/2,    0.125},
		{-PI/2,   0.125},
		{-PI/2,   0.125},
		{PI/2,    0.125}
	},
	{ /*Curva Quadrada (inventado por mim: uma "curva" feita com angulos retos. Niveis altos de recursao mostram bem a curva)*/
		{3, 0},
		{PI/4,   0.35355339059327379},    /*sqrt(1.0/8.0) = 0.35355339059327379*/
		{-PI/2,  0.35355339059327379*2},
		{PI/2,   0.35355339059327379}
	},
	{ /*Base Recursiva (tambem inventado por mim: o modelo eh a propria base)*/
		/*O numero de segmentos eh o numero de segmentos da base. Esse valor sera apropriadamente setado junto com a base.*/
		/*O segundo valor da primeira linha, normalmente nao usado, nesse caso eh a escala do segmento do modelo.*/
		{-1, 0.5}
	},
	{ /*Floco de neve*/
		{7, 0},
		{PI/3,    1.0/3.0},
		{0.0,     1.0/3.0},
		{-PI/3,   1.0/3.0},
		{-PI/3,   1.0/3.0},
		{-PI/2,   0.57735026918962573},  /*escala = sqrt(3)/3.0*/
		{5*PI/6,  1.0/3.0},
		{0.0,     1.0/3.0}
	},
	{ /*Curva peano-gosper*/
		{7, 0},
		{-0.33347317225183193,       0.3779644730092272},  /* angulo = -(PI/3)+acos(2.0/sqrt(7))*/
		{PI/3,                       0.3779644730092272},
		{2*PI/3,                     0.3779644730092272},  /*  */
		{-PI/3,                      0.3779644730092272},  /* escalas = 1.0/sqrt(7) */
		{-2*PI/3,                    0.3779644730092272},  /*  */
		{0.0,                        0.3779644730092272},
		{-PI/3,                      0.3779644730092272}
	}
};

/*O mesmo que o array de matrizes anterior, infoModelos.
  Este porem guarda a informaçao dos modelos quando invertido verticalmente (em torno do eixo vertical).
  Como nao usamos a inversao vertical para todos modelos, so guardamos a informacao daqueles que poderao ser invertidos verticalmente.*/
double infoModelosInversoV[2][7][2] = {  /*a matriz do modelo invertido ao redor do eixo vertical*/
	{ /*Floco de neve*/
		{0.0,     1.0/3.0},
		{0.0,     1.0/3.0},
		{5*PI/6,  0.57735026918962573}, /*escala = sqrt(3)/3.0*/
		{-PI/2,   1.0/3.0},
		{-PI/3,   1.0/3.0},
		{-PI/3,   1.0/3.0},
		{0.0,     1.0/3.0}
	},
	{ /*Curva peano-gosper*/
		{1.3806707234484294,         0.3779644730092272}, /* angulo = (2*PI/3)-acos(2.0/sqrt(7)) */
		{-PI/3,                      0.3779644730092272},
		{0.0,                        0.3779644730092272}, /*  */
		{-2*PI/3,                    0.3779644730092272}, /* escalas = 1.0/sqrt(7) */
		{-PI/3,                      0.3779644730092272}, /*  */
		{2*PI/3,                     0.3779644730092272},
		{PI/3,                       0.3779644730092272}
	}
};

/*Outro array de matrizes, mas este guarda a ordem na qual certos modelos deverao ser invertidos.
  Cada dupla e igual a (deve inverter horizontalmente, deve inverter verticalmente).*/
short ordemModelos[2][7][2] = {
	{ {1,0}, {0,1}, {0,1}, {0,1}, {1,1}, {1,0}, {0,1} }, /*ordem do floco de neve. */
	{ {0,0}, {1,1}, {1,1}, {0,0}, {0,0}, {0,0}, {1,1} }  /*ordem peano-gosper. */
};


/*
E finalmente nossas funcoes.
*/


/*Funcao basica para criar um ponto.*/
void criaPonto(double x, double y)
{
	/*Caso a opcao de cor escolhida seja multi-colorido, a cada ponto do poligono setamos uma cor RGB basica diferente. Nos niveis de recursao mais altos, com muitos pontos, nao eh muito aparente. Porem nos primeiros niveis que nao tem tantos pontos o efeito eh bem... colorido haha.*/
	if (USE_MULTI_COR >= 1) 
	{
		switch (USE_MULTI_COR)
		{
			case (1):
				glColor3f(1.0, 0.0, 0.0);
				break;	
			case (2):
				glColor3f(0.0, 1.0, 0.0);
				break;
			case (3):
				glColor3f(0.0, 0.0, 1.0);
				USE_MULTI_COR = 0;
				break;
		}
		USE_MULTI_COR++;
	}
	glVertex2f( x, y );
}


/*Funcao para criar um modelo fractal recursivamente, ate o nivel de recursao selecionado. */
void criaSegmentoModelo(double Xo, double Yo, double angulo, double tamanhoSegmento, short pontosFaltando, short nivelRecursaoAtual, short inverteModeloH, short inverteModeloV)
{
	if (nivelRecursaoAtual > nivelRecursao || pontosFaltando <= 0)
		return;
	
	/* Se devemos ou nao inverter o modelo horizontalmente e/ou verticalmente. Dependendo do parametro passado e do tipo de inversao a qual o segmento em que estamos adicionando o modelo ja foi submetido. */
	short indice = (short)infoModelos[TIPO_MODELO][0][0] - pontosFaltando;
	short inversaoH = 0;
	short inversaoV = 0;
	if (TIPO_MODELO > 5 && nivelRecursaoAtual >= 1)
	{
		if ( inverteModeloV == 1)
			indice = pontosFaltando - 1;
		inversaoH = inverteModeloH != ordemModelos[TIPO_MODELO-6][indice][0];
		inversaoV = inverteModeloV != ordemModelos[TIPO_MODELO-6][indice][1];
	}
	/*Para inverter horizontalmente, basta inverter os angulos, trocando seus sinais. Para isso, usamos esse fator.*/
	double invModH = 1.0 - 2*inverteModeloH;
	/*Para inverter verticalmente porem eh um pouco mais complicado. Devemos usar o modelo ja invertido.*/
	double tamanho;
	indice = (short)infoModelos[TIPO_MODELO][0][0] - pontosFaltando;
	if (inverteModeloV && TIPO_MODELO > 5)
	{
		angulo += infoModelosInversoV[TIPO_MODELO-6][indice][0] * invModH;
		tamanho = tamanhoSegmento * infoModelosInversoV[TIPO_MODELO-6][indice][1];
	}
	else if (TIPO_MODELO == 5)
	{
		angulo -= PI - anguloBase;
		tamanho = tamanhoSegmento * infoModelos[TIPO_MODELO][0][1];
	}
	else
	{
		angulo += infoModelos[TIPO_MODELO][indice + 1][0] * invModH;
		tamanho = tamanhoSegmento * infoModelos[TIPO_MODELO][indice + 1][1];
	}

	/*Calculamos o proximo ponto do modelo nesse nivel de recursao antes de tudo.*/
	double X = Xo + (tamanho * cos(angulo));
	double Y = Yo + (tamanho * sin(angulo));

	/*Depois mandamos criar o modelo no proximo nivel de recursao no que sera o segmento (Xo,Yo)->(X,Y)*/
	criaSegmentoModelo(Xo, Yo, angulo, tamanho, (short)infoModelos[TIPO_MODELO][0][0], nivelRecursaoAtual+1, inversaoH, inversaoV);

	/*Criamos nosso ponto...*/
	criaPonto(X, Y);

	/*E finalmente mandamos criar o proximo ponto do modelo no nivel atual de recursao.*/
	criaSegmentoModelo(X, Y, angulo, tamanhoSegmento, pontosFaltando-1, nivelRecursaoAtual, inverteModeloH, inverteModeloV);
}


/*Funcao para criar a base (um poligono regular) recursivamente, ja aplicando o modelo fractal em seus segmentos.*/
void criaSegmentoBase(double Xo, double Yo, double angulo, double tamanho, short pontosFaltando)
{
	if (pontosFaltando == 0)
		return;

	/*Calculamos o proximo ponto da base.*/
	double X = Xo + (tamanho * cos(angulo));
	double Y = Yo + (tamanho * sin(angulo));

	/*Mandamos criar o modelo no primeiro nivel de recursao entre esse segmento (Xo,Yo)->(X,Y) */
	criaSegmentoModelo(Xo, Yo, angulo, tamanho, (short)infoModelos[TIPO_MODELO][0][0], 1, 0,0);

	/*Criamos nosso ponto previamente calculado.*/
	criaPonto(X, Y);

	/*Atualizamos o angulo para mandar criar o proximo ponto da base.*/
	angulo -= PI - anguloBase;
	criaSegmentoBase(X, Y, angulo, tamanho, pontosFaltando-1);
}


/*Funcao principal para desenhar o fractal na tela. Deve ser chamado entre uma chamada de glBegin/glEnd */
void desenhaFractal()
{
	/*Considerando que o raio da circunferencia circunscrita no poligono eh 1/4 da media entre a largura e o comprimento, usamos da formula para descobrir esse raio para descobrir o tamanho do lado do poligono.*/
	double raio = (height + width) / 8;
	double tamanho = 2*sin(PI/TIPO_BASE)*raio;
	/*E finalmente calculamos o (X,Y) do primeiro ponto do poligono, tentando sempre ser o mais a baixo-esquerda possivel.*/
	double Xinicial = (width/2) - tamanho/2;
	double Yinicial = (height/2) - raio + 0.2*tamanho;

	/*criamos o 1º ponto e o numero de pontos faltando para desenhar a base, lembrando que temos que repetir o 1º ponto no final, para fechar o poligono da base.*/
	criaPonto(Xinicial, Yinicial);
	short pontosFaltando = TIPO_BASE - 1*(TIPO_BASE == 2);

	/*E mandamos criar o proximo ponto da base, dando inicio ao processo recursivo que cria o fractal com a base, modelo e nivel de recursao escolhidos.*/
	criaSegmentoBase(Xinicial, Yinicial, anguloBase, tamanho, pontosFaltando);
}


/*Funcao para desenhar texto na tela, nas coordenadas dadas.*/
void desenhaTexto(char* string, double x, double y)
{
	glPushMatrix();
	glRasterPos2f(x, y);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *string++);
	glPopMatrix();
}


/*Callback do display da janela.*/
void display(void)
{
	/*So damos o display caso tenhamos mudado algo que necessite que a imagem seja atualizada. Assim a janela nao eh inutilmente redesenhada quando fazemos coisas que nao mudam a imagem, como mexer no menu, e portanto nao perdemos processamento a toa.*/
	if (DO_DISPLAY != 0)
	{
		/*Toda vez que o OpenGL vai desenhar algo chama essa função*/
		glClear(GL_COLOR_BUFFER_BIT);

		/*Comecamos desenhando o texto dizendo algumas informaçoes basicas do fractal para o usuario no topo-esquerdo da janela.*/
		char texto[30];
		sprintf(texto, "Nivel de Recursao: %d", nivelRecursao);
		desenhaTexto(texto, 0, height-10); 

		/*E tambem desenhamos na tela o texto dizendo qual modelo esta selecionado.*/
		switch (TIPO_MODELO)
		{
			case (-1):
				desenhaTexto("Nenhum modelo selecionado...", 0, height-20);
				break;
			case (0): /*Koch triadrico*/
				desenhaTexto("Modelo: Koch Triadrico", 0, height-20);
				break;
			case (1): /*Koch quadrico 1*/
				desenhaTexto("Modelo: Koch Quadrico Variacao 1", 0, height-20);
				break;
			case (2): /*Koch quadrico 2*/
				desenhaTexto("Modelo: Koch Quadrico Variacao 2", 0, height-20);
				break;
			case (3): /*Koch quadrico 3*/
				desenhaTexto("Modelo: Koch Quadrico Variacao 3", 0, height-20);
				break;
			case (4): /*Curva Quadrada*/
				desenhaTexto("Modelo: Curva Quadrada", 0, height-20);
				break;
			case (5): /*Base Recursiva*/
				desenhaTexto("Modelo: Base Recursiva", 0, height-20);
				break;
			case (6): /*Floco de neve*/
				desenhaTexto("Modelo: Floco de Neve", 0, height-20);
				break;
			case (7): /*Curva peano-gosper*/
				desenhaTexto("Modelo: Curva Peano-Gosper", 0, height-20);
				break;
		}

		/*E agora desenhamos a imagem em si, o nosso poligono/fractal.
		 OBS:
		    > GL_POLYGON eh preenchido, mas por alguma razao, nao funciona como esperamos.
		    > GL_LINE_LOOP faz a forma do poligono direitinho, sem precisar duplicar o primeiro ponto na ultima posicao, porem por alguma razao, a cada tantos pontos (mais ou menos 8000), ele cria linhas que nao deveriam existir, entre um ponto e a origem do poligono.
		    > O jeito entao eh usar GL_LINE_STRIP, e duplicar o primeiro ponto no final do poligono. */
		if (TIPO_BASE != -1)
		{
			glBegin( GL_LINE_STRIP );
			desenhaFractal();
			glEnd();
		}

		glFlush(); /*Força desenhar a janela (Não apagar)*/
		DO_DISPLAY = 0;
		DO_SWAP = 1;
	}
}


/*Callback chamado quando o programa esta idle (sem nada sendo executado)
  Usado para dar swap no nosso double-buffer separadamente do metodo de display.*/
void idle(void)
{
	if (DO_SWAP != 0)
	{
		glutSwapBuffers();
		DO_SWAP = 0;
	}
}


/*Funcao para limpar o conteudo grafico da janela*/
void clearDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


/*Callback do menu principal.*/
void menuClick(int value)
{
	/*Aqui são tratadas as chamadas ao menu. value é o ID do item no menu.*/
	switch (value)
	{
		case (0): /*quit*/
			glutDestroyWindow(win);
			exit(0);
			break;
		case (1): /*resetar*/
			TIPO_BASE = -1;  
			TIPO_MODELO = -1;
			nivelRecursao = 0;
			clearDisplay();
			DO_DISPLAY = 1;
			break;
	}
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Callback do menu de selecao da base.*/
void basesMenuClick(int value)
{
	TIPO_BASE = value;
	anguloBase = ( (TIPO_BASE - 2)*PI ) / TIPO_BASE; /*atualizamos o angulo da base, armazenado globalmente.*/
	infoModelos[5][0][0] = TIPO_BASE;                /*e atualizamos o numero de segmentos do modelo Base Recursiva.*/
	DO_DISPLAY = 1;
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Callback do menu de selecao do modelo fractal.*/
void modelosMenuClick(int value)
{
	TIPO_MODELO = value;
	DO_DISPLAY = 1;
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Callback do menu do nivel de recursao.*/
void recursaoMenuClick(int value)
{
	if (value == 11)  /*aumentar nivel +1*/
	{
		nivelRecursao++;
	}
	else
	{
		if (value == 12) /*diminuir nivel -1*/
			nivelRecursao--;
		else  /*setar nivel especifico, de 0 a 10*/
			nivelRecursao = value;
		if (nivelRecursao < 0)
			nivelRecursao = 0;
	}
	DO_DISPLAY = 1;
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Callback do menu de cores.*/
void coresMenuClick(int value)
{
	USE_MULTI_COR = 0;
	switch (value)
	{
		case (-1): /*multi colorido*/
			USE_MULTI_COR = 1;
			break;
		case (0): /*preto*/ 
			glColor3f(0.0, 0.0, 0.0);
			break;
		case (1): /*cinza*/
			glColor3f(0.5, 0.5, 0.5);
			break;
		case (2): /*vermelha*/
			glColor3f(1.0, 0.0, 0.0); 
			break;
		case (3): /*verde*/
			glColor3f(0.0, 1.0, 0.0);
			break;
		case (4): /*azul*/
			glColor3f(0.0, 0.0, 1.0);
			break;
		case (5): /*amarelo*/
			glColor3f(1.0, 1.0, 0.0);
			break;
		case (6): /*roxo*/
			glColor3f(1.0, 0.0, 1.0);
			break;
		case (7): /*laranja*/
			glColor3f(1.0, 0.5, 0.0);
			break;
	}
	DO_DISPLAY = 1;
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Funcao para inicializar o menu pop-up utilizado.*/
void createMenu(void)
{
	/*Criando sub-menu de bases*/
	basesMenu = glutCreateMenu(basesMenuClick);
	glutAddMenuEntry("Linha", 2);
	glutAddMenuEntry("Triangulo", 3);
	glutAddMenuEntry("Quadrado", 4);
	glutAddMenuEntry("Pentagono", 5);
	glutAddMenuEntry("Hexagono", 6);
	glutAddMenuEntry("Octogono", 8);
	glutAddMenuEntry("Decagono", 10);
	glutAddMenuEntry("Dodecagono", 12);

	/*Criando sub-menu de modelos*/
	modelosMenu = glutCreateMenu(modelosMenuClick);
	glutAddMenuEntry("Koch (triadrico)", 0);
	glutAddMenuEntry("Koch (quadrico, var 1)", 1);
	glutAddMenuEntry("Koch (quadrico, var 2)", 2);
	glutAddMenuEntry("Koch (quadrico, var 3)", 3);
	glutAddMenuEntry("Curva Quadrada", 4);
	glutAddMenuEntry("Base Recursiva", 5);
	glutAddMenuEntry("Floco de Neve", 6);
	glutAddMenuEntry("Curva Peano-Gosper", 7);

	/*Criando sub-menu de recursao*/
	recursaoMenu = glutCreateMenu(recursaoMenuClick);
	glutAddMenuEntry("Aumentar Nivel (+1)", 11);
	glutAddMenuEntry("Diminuir Nivel (-1)", 12);
	glutAddMenuEntry("Nivel 0", 0);
	glutAddMenuEntry("Nivel 1", 1);
	glutAddMenuEntry("Nivel 2", 2);
	glutAddMenuEntry("Nivel 3", 3);
	glutAddMenuEntry("Nivel 4", 4);
	glutAddMenuEntry("Nivel 5", 5);
	glutAddMenuEntry("Nivel 6", 6);
	glutAddMenuEntry("Nivel 7", 7);
	glutAddMenuEntry("Nivel 8", 8);
	glutAddMenuEntry("Nivel 9", 9);
	glutAddMenuEntry("Nivel 10", 10);

	/*Criando sub-menu de cores*/
	coresMenu = glutCreateMenu(coresMenuClick);
	glutAddMenuEntry("Multi-Colorido", -1);
	glutAddMenuEntry("Preto", 0);
	glutAddMenuEntry("Cinza", 1);
	glutAddMenuEntry("Vermelho", 2);
	glutAddMenuEntry("Verde", 3);
	glutAddMenuEntry("Azul", 4);
	glutAddMenuEntry("Amarelo", 5);
	glutAddMenuEntry("Roxo", 6);
	glutAddMenuEntry("Laranja", 7);

	/*Criando o menu principal*/
	menuID = glutCreateMenu(menuClick);

	glutAddSubMenu("Bases", basesMenu);
	glutAddSubMenu("Modelos", modelosMenu);
	glutAddSubMenu("Nivel de Recursao", recursaoMenu);
	glutAddSubMenu("Cores", coresMenu);

	glutAddMenuEntry("Resetar", 1);
	glutAddMenuEntry("QUIT", 0);

	/*Faz com que o menu seja chamado quando apertamos o botão direito*/
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/*Callback da janela - quando seu tamanho eh mudado. Usado para atualizar o tamanho da janela para nos e para o glut.*/
void reshape(int w,int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	width = w;
	height = h;
	DO_DISPLAY = 1;
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Callback do mouse, quando ocorre um evento de botao do mouse dentro da janela. Usamos ele para 2 coisas:
	1º: redesenhar a janela com qualquer evento de botao.
	2º: aumentar ou diminuir o nivel de recursao do fractal com o movimento da roda do mouse.  */
void gerenciaMouse(int button, int state, int x, int y)
{
	if (button == 3 && state == GLUT_UP) /*Por testes descobri que button=3 eh a roda do mouse para cima*/
	{
		nivelRecursao++;
	}
	else if (button == 4 && state == GLUT_UP)  /*e que button=4 eh a roda para baixo.*/
	{
		nivelRecursao--;
		if (nivelRecursao < 0)
			nivelRecursao = 0;
	}
	DO_DISPLAY = 1;
	glutPostRedisplay(); /*diz para o glut redesenhar a janela no proximo loop*/
}


/*Funcao para definir varios atributos do glut quando inicializado.*/
void init()
{
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glLineWidth(1.5);
	glPointSize(1.0);
	glClearColor(1.0, 1.0, 1.0, 1.0); /*branco*/

	glColor3f(0.0, 0.0, 0.0); /*preto*/

	DO_DISPLAY = 1;
}


/*O ponto de entrada do programa.*/
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	/*Em vez de GLUT_SINGLE uso GLUT_DOUBLE para usar uma janela double-buffered, possibilitando que o programa desenhe os poligonos 
	  bem mais rapidamente que o normal, sem aquela aparencia de que ele esta desenhando ponto por ponto...*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width,height); /*se voce deseja deixar em fullscreen comente essa linha
		                       e descomente a glutFullScreen(). Se quer só aumentar o
                	               tamanho inicial da janela, basta trocar os valores*/
	glutCreateWindow("EP2 - Fernando (6797226)");
	/*glutFullScreen();*/

	init();                       /*inicializa alguns atributos do glut.*/
	createMenu();                 /*inicializa nossos menus.*/
	glutDisplayFunc(display);     /*Seta o callback de display da janela.*/
	glutIdleFunc(idle);           /*Seta o callback de quando o programa fica idle (sem executar nada).*/
	glutReshapeFunc(reshape);     /*Seta o callback de quando o tamanho da janela eh mudado pelo usuario.*/
	glutMouseFunc(gerenciaMouse); /*Seta o callback de eventos do mouse.*/

	glutMainLoop(); /*O OpenGL passa a tomar controle total do programa*/


	return 0;
}

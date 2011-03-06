/* MAC - 0122  Principios de Desenvolvimento de Algoritmos  */
/* Prof : Carlos E. Ferreira                                */
/* EP - 2 Fractais                                          */
/*                                                          */
/* Aluno: Thiago de Gouveia Nunes                           */
/* Numero USP: 6797289                                      */
/* Data de Entrega : 08/10/2009                             */
/*                                                          */
/* O EP foi feito no Linux                                  */



/* O EP se baseia em varias funções particulares para cada fractal. */


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>          

#define QUIT 0
#define EXEC 1
#define X 2
#define Y 3
#define Z 4
#define K 5
#define CLEAR 6
#define pi 3.141592653589793238462643
#define angbase 0.333473172

/* A struct abaixo foi feita somente para facilitar o entendimento do EP. */

typedef struct p { 
 				double x;
				double y;
				} ponto;

static int win;
static int menid;
static int submenid;
static int submenb;
static int submenint;
static int submencor;
static int primitive = 10;
static int base = 13;
static int Frac = 2;
static ponto pts[7]; /* Este array e o abaixo sao usados para a construcao dos poligonos. */
static double angpts[7];
static int inter = 0; /* Variavel que controla o nivel de interacao. */
static int multicor = 0; /* Variavel que controla a cor. */
static double anggosper[7] = { 0, -pi/3, -pi, -2*pi/3, 0, 0, pi/3, }; /* Array que contem os angulos do fractal peano-gosper. */

void draw_segmento( ponto p1, ponto p2 )
{
  glBegin(GL_LINES);
    glVertex2f( p1.x, p1.y);
    glVertex2f( p2.x, p2.y);
  glEnd();
}

/* A função abaixo calcula o angulo entre dois pontos. */

double angulo ( ponto p1 , ponto p2 )
{
	return atan2 ( ( p2.y - p1.y ) , ( p2.x - p1.x ) );
}

/* A funcao poligono constroi os poligonos e preenche os arrays pts com os pontos dos poligonos e angpts com os angulos entre os pontos. */

void poligono ( ponto pt , double lado, int nlado )
{
	ponto atual, prox;
	int k = 0;
	double angext = (2*pi)/nlado;
	
	atual = pt;
	pts[0] = pt;
	
	for ( k = 0; k < nlado ; k ++) 
	{
		prox.x = atual.x + lado*cos( k*angext );
		prox.y = atual.y + lado*sin( k*angext );
		pts[k+1] = prox;
		angpts[k] = angulo ( pts[k] , pts[k+1] );
		atual = prox;
	}
}

/* Esta função é responsavel pela mudança de cor do fractal, ela é chamada toda vez que a cor é mudada. */
void escolhecor ( double red, double green, double blue )
{
  glColor3f( red, green, blue);
}

/* Esta função calcula a distancia entre dois pontos. */
double distancia ( ponto p1 , ponto p2 )
{
	double d1, d2;
	
	d1 = (p1.x - p2.x)*(p1.x - p2.x);
	d2 = (p1.y - p2.y)*(p1.y - p2.y);

	return ( sqrt( d1 + d2 ) );
} 

/* Abaixo seguem as funções recursivas usadas para desenhar os fractais. As funções são todas semelhantes, logo explicarei o basico aqui e o particular de cada uma quando chegarmos a elas. Todas as funções recebem dois pontos, o angulo entre eles, o tipo da base e o nivel da interação. Se a interação for nivel zero a função desenha uma reta. Se não ela calcula os pontos para o proximo nivel. O angulo entre os pontos são achados usando a congruencia do numero do loop com o numero de retas criadas pelo nivel 1 do fractal em questão. Logo apos isso a função é chamada novamente com um nivel de interação menor. */

/* Esta é a função recursiva do fractal Ilha de Koch Triadica. */
void ilhadekochT( ponto pt1, ponto pt2, double ang, int tipobase, int interacao)
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	
	base = tipobase;
	atual = pt1;
	prox = pt2;
	dist = distancia ( pt1 , pt2 )/3; 
	
	if ( interacao == 0 ) {
				if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
		draw_segmento(atual , prox);
	}
	else {
		for ( n = 0; n < 4; n++)
		{
			interac = interacao;		
				switch ( ( n%4 ) ) 
				{
					case 0:
					case 3:
					p = 0;
					break;
					case 1:
					p = -1;
					break;
					case 2:
					p = 1;
					break;
				}
			prox.x = atual.x + dist*cos( ang + (p * (pi/3)) );
			prox.y = atual.y + dist*sin( ang + (p * (pi/3)) );
			ilhadekochT( atual , prox, angulo ( atual , prox ), base, --interac );
			atual = prox;
	 	}	
	}
}

/* Esta é a função recursiva do fractal Ilha de Koch Quadrica I. */
void ilhadekochQI( ponto pt1, ponto pt2, double ang, int tipobase, int interacao)
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	
	base = tipobase;
	atual = pt1;
  prox = pt2;
	dist = distancia ( pt1 , pt2 )/4; 
	
	if ( interacao == 0 ){
		if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
		draw_segmento(atual , prox);
	}
	else {
		for ( n = 0; n < 8; n++)
		{
			interac = interacao;		
				switch ( ( n%8 ) ) 
				{
					case 0:
					case 7:
					case 2:
					case 5:
					p = 0;
					break;
					case 1:
					case 6:
					p = 1;
					break;
					case 3:
					case 4:
					p = -1;
					break;
				}
			prox.x = atual.x + dist*cos( ang + (p * (pi)/2) );
			prox.y = atual.y + dist*sin( ang + (p * (pi)/2) );
			ilhadekochQI( atual , prox, angulo ( atual , prox ), base, --interac ); 
			atual = prox;
		}	
	}
}

/* Esta é a função recursiva do fractal Ilha de Koch Quadrica II. */
void ilhadekochQII( ponto pt1, ponto pt2, double ang, int tipobase, int interacao)
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	
	base = tipobase;
	atual = pt1;
	prox = pt2;
	dist = distancia ( pt1 , pt2 )/8; 
	
	if ( interacao == 0 ) {
		if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
		draw_segmento(atual , prox);
	}
	else {
		for ( n = 0; n < 32; n++)
		{
			interac = interacao;		
			switch ( ( n%32 ) ) {
				case 1:
				case 5:
				case 6:
				case 8:
				case 13:
				case 14:
				case 17:
  			case 18:
				case 23:
				case 25:
				case 26:
				case 30:
				p = 0;
				break;
				case 3:
				case 11:
				case 20:
				case 28:
				p = 2;
				break;
				case 0:
				case 2:
				case 4:
				case 7:
				case 24:
				case 27:
				case 29:
				case 31:
				p = 1;
				break;
				case 9:
				case 10:
				case 12:
				case 15:
				case 16:
				case 19:
				case 21:
				case 22:
				p = -1;
				break;
			}
			prox.x = atual.x + dist*cos( ang + (p * (pi)/2) );
			prox.y = atual.y + dist*sin( ang + (p * (pi)/2) );
			ilhadekochQII( atual , prox, angulo ( atual , prox ), base, --interac );
			atual = prox;
		}	
	}
}

/* As duas funções abaixo são responsaveis pelo fractal peano-gosper. A função peanogosper desenha o fractal normalmente, mas como observado pela figura dada no enunciado, o fractal se inverte no decorer do desenho, quando isso ocorre a função em questão chama peanogosperIV, que inverte o desenho da proxima interação, mantendo a ordem do fractal. Neste fractal é necessario somar um angulo inicial, chamado de angbase, pois o fractal tem um pequeno angulo em relação a horizontal. Os angulos desse fractal são pegos do array anggosper, definido acima.  */

void peanogosperIV ( ponto, ponto, double, int, int );

void peanogosper ( ponto pt1, ponto pt2, double ang, int tipobase, int interacao) 
{
	ponto prox, atual;
	int base, n, interac;
	double dist;
	
	base = tipobase;
	atual = pt1;
	prox = pt2;
	dist = distancia ( pt1 , pt2 )/sqrt(7); 
	
	if ( interacao == 0 ) {
		if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
		draw_segmento(atual , prox);
	}
	else {
		for ( n = 0; n < 7; n++)
		{
				interac = interacao;		
				prox.x = atual.x + dist*cos( ang + angbase + anggosper[n] );
				prox.y = atual.y + dist*sin( ang + angbase + anggosper[n] );
				if ( ( interac >= 2 ) && ( n == 1 || n == 2 || n == 6 ) ) {
					peanogosperIV( atual , prox, angulo ( atual , prox ), base, --interac );
				}
				else {
					peanogosper( atual , prox, angulo ( atual , prox ), base, --interac );
				}
				atual = prox;
   	}
	}
}

void peanogosperIV ( ponto pt1, ponto pt2, double ang, int tipobase, int interacao) 
{
	ponto prox, atual;
	int base, n, interac;
	double dist;
	
	base = tipobase;
	atual = pt1;
	prox = pt2;
	dist = distancia ( pt1 , pt2 )/sqrt(7); 
	
	if ( interacao == 0 ) {
		if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
		draw_segmento(atual , prox);
	}
	else {
		for ( n = 6; n >= 0; n--)
		{
				interac = interacao;
				prox.x = atual.x + dist*cos( ang + angbase + anggosper[n] );
				prox.y = atual.y + dist*sin( ang + angbase + anggosper[n] );
				if ( ( interac >= 2 ) && ( n == 0 || n == 4 || n == 5 ) ) {
					peanogosperIV( atual , prox, angulo ( atual , prox ), base, --interac );
				}
				else {
					peanogosper( atual , prox, angulo ( atual , prox ), base, --interac );
				}
				atual = prox;
   	}
	}
}

/* Esta função faz com que cada vez que o usuario clique em EXEC o fractal, base, cor e nivel de interação escolidos sejam desenhados. */
void display(void)
{
  /*Toda vez que o OpenGL vai desenhar algo chama essa função*/
  glClear(GL_COLOR_BUFFER_BIT);
	
  if( primitive == EXEC) {
  	int lados, k;
  	lados = base - 10;
    
		switch ( Frac ) {
		case 2: 
			for ( k = 0; k < lados; k++) {
    		ilhadekochT( pts[k], pts[k+1], angpts[k],  base, inter );
    	}
		break;
		case 3:
			for ( k = 0; k < lados; k++) {
    		ilhadekochQI( pts[k], pts[k+1], angpts[k],  base, inter );
    	}
    break;
    case 4:
			for ( k = 0; k < lados; k++) {
    		ilhadekochQII( pts[k], pts[k+1], angpts[k],  base, inter );
    	}
    break;
    case 5:
    	for ( k = 0; k < lados; k++) {
    		peanogosper( pts[k], pts[k+1], angpts[k],  base, inter );
    	}
    break;	
		}
		primitive = 10;
  }

  glutSwapBuffers();
  glFlush();/*Força desenhar a janela (Não apagar)*/
}

/* Essa função escolhe o fractal a ser desenhado atraves da variavel global Frac. Porem se o valor recebido for EXEC, a função display desenha o fractal em questão. */
void menu(int value)
{
  /*Aqui são tratadas as chamadas ao menu
   value é o ID do item no menu*/

	if ( value != EXEC ) Frac = value;

  if(value == QUIT){
    glutDestroyWindow(win);
    exit(0);
  }
  else{
    primitive = value;
		
  }
  
  /*redesenhando*/
  glutPostRedisplay();
}

/* Essa função define a base a ser desenhada. São 5 bases, reta, triangulo, quadrado, retangulo e hexagono. */
void tipo ( int value )
{
	ponto pt, pt1;
	pt.x = 155;
	pt.y = 155;
	pt1.x = 355;
	pt1.y = 155;
	base = value;
	
  switch ( base ) {
  case 11:
  pts[0] = pt;
  pts[1] = pt1;
  angpts[0] = angulo ( pt, pt1 );
  break;
	case 13:
	poligono ( pt , 200 , 3 );
	break;
	case 14:
	poligono ( pt , 200 , 4 );
	break;
	case 15:
	poligono ( pt , 150 , 5 );
	break;
	case 16:
	poligono ( pt , 150 , 6 );
	break;
	}
}

/* Essa função aumenta ou diminue o nivel de interação. */
void interac ( int value )
{
  inter += value;
}

/* Essa função define a cor do desenho chamando a função escolhecor. No ultimo case, ela defini a variavel multicor como 1, que faz com que a cor mude conforme o ponto muda, fazendo o fractal ficar multicolorido. Essa operação pode ser vista nas funções que desenham os fractais. */
void menucor( int value )
{
	switch (value) {
	case 0:
	escolhecor( 1.0 , 1.0 , 1.0 );
	multicor = 0;
	break;
	case 1:
	escolhecor( 1.0 , 0.0 , 0.0 );
	multicor = 0;
	break;
	case 2:
	escolhecor( 0.0 , 1.0 , 0.0 );
	multicor = 0;
	break;
	case 3:
	escolhecor( 0.0 , 0.0 , 1.0 );
	multicor = 0;
	break;
	case 4:
	escolhecor( 1.0 , 1.0 , 0.0 );
	multicor = 0;
	break;
	case 5:
	escolhecor( 1.0 , 0.0 , 1.0 );
	multicor = 0;
	break;
	case 6:
	escolhecor( 0.0 , 1.0 , 1.0 );
	multicor = 0;
	break;
	case 7:
	multicor = 1;
	break;
	}
}

void createMenu(void)
{
	/* Esse menu define a cor do desenho. */ 
  submencor = glutCreateMenu(menucor);
  
  glutAddMenuEntry("Branco", 0);
  glutAddMenuEntry("Vermelho", 1);
  glutAddMenuEntry("Verde", 2);
  glutAddMenuEntry("Azul", 3);
  glutAddMenuEntry("Amarelo", 4);
  glutAddMenuEntry("Rosa", 5);
  glutAddMenuEntry("Azul Piscina", 6);
  glutAddMenuEntry("Colorido", 7);

	/* Esse menu escolhe o nivel de interação. */
	submenint = glutCreateMenu(interac);
	
	glutAddMenuEntry("++", 1);
  glutAddMenuEntry("--", -1);

  /*Criando um menu para as bases*/
  submenb = glutCreateMenu(tipo);
  
  glutAddMenuEntry("Reta", 11);
  glutAddMenuEntry("Triangulo", 13);
  glutAddMenuEntry("Quadrado", 14);
	glutAddMenuEntry("Pentagono", 15);
	glutAddMenuEntry("Hexagono", 16);

  /*Criando um menu*/
  submenid = glutCreateMenu(menu);

  /*Adicionando entradas*/
  glutAddMenuEntry("Ilha de Koch Triadica ", X);
  glutAddMenuEntry("Ilha de Koch Quadrica I ", Y);
  glutAddMenuEntry("Ilha de Koch Quadrica II ", Z);
  glutAddMenuEntry("Peano - Gosper ", K);

  /*Criando outro menu. Daqui em diante ele é o principal*/
  menid = glutCreateMenu(menu);

  /* Criando entradas*/
  glutAddMenuEntry("Exec", EXEC);

  /*Associando o menu submenid como submenu*/
  glutAddSubMenu("Fractal", submenid);
  glutAddSubMenu("Base", submenb);
  glutAddSubMenu("Interacao", submenint);
  glutAddSubMenu("Cores", submencor);
  
  glutAddMenuEntry("Clear", CLEAR);
  glutAddMenuEntry("Quit", QUIT);

  /*Faz com que o menu seja chamado quando apertamos o botão direito*/
  glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void reshape(int w,int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
}

void init()
{
  glEnable (GL_LINE_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE); 

  glLineWidth(1.5);
  glPointSize(1.0);
  glClearColor(0.0, 0.0, 0.0, 1.0); /* O fundo base é preto. */

  glColor3f(1.0, 1.0, 1.0); /* A cor base é branca. */
}

int main(int argc, char ** argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowSize(700,700); /*se voce deseja deixar em fullscreen comente essa linha
                                 e descomente a glutFullScreen(). Se quer só aumentar o
                                 tamanho inicial da janela, basta trocar os valores*/
  glutCreateWindow("EP 2 - Fractais");  
  /* glutFullScreen(); */ 

  init();
  createMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop(); /*O OpenGL passa a tomar controle total do programa*/
  
  return 0;
}

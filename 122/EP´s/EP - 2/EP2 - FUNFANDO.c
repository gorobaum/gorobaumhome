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
static ponto pts[7];
static double angpts[7];
static int inter = 0;
static int multicor = 0;

void draw_segmento( ponto p1, ponto p2 )
{
  glBegin(GL_LINES);
    glVertex2f( p1.x, p1.y);
    glVertex2f( p2.x, p2.y);
  glEnd();
}

double angulo ( ponto p1 , ponto p2 )
{
	return atan2 ( ( p2.y - p1.y ) , ( p2.x - p1.x ) );
}

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
	/* draw_segmento(atual , prox); */
	atual = prox;
	}
}

void escolhecor ( double red, double green, double blue )
{
  glColor3f( red, green, blue);
}

double distancia ( ponto p1 , ponto p2 )
{
	double d1, d2;
	
	d1 = (p1.x - p2.x)*(p1.x - p2.x);
	d2 = (p1.y - p2.y)*(p1.y - p2.y);

	return ( sqrt( d1 + d2 ) );
} 

void ilhadekochT( ponto pt1, ponto pt2, double ang, int tipobase, int interacao)
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	base = tipobase;
	atual = pt1;
	dist = distancia ( pt1 , pt2 )/3; 
	
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
			if ( interac > 0 ) {
				ilhadekochT( atual , prox, angulo ( atual , prox ), base, --interac );
			}
			else if ( interacao == 0 )
			{
				if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
			draw_segmento(atual , prox);
			}
			atual = prox;
	}	
}

void ilhadekochQI( ponto pt1, ponto pt2, double ang, int tipobase, int interacao)
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	base = tipobase;
	atual = pt1;
	dist = distancia ( pt1 , pt2 )/4; 
	
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
			if ( interac > 0 ) {
				ilhadekochQI( atual , prox, angulo ( atual , prox ), base, --interac );
			}
			else if ( interacao == 0 )
			{
				if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
			draw_segmento(atual , prox);
			}
			atual = prox;
	}	
}

void ilhadekochQII( ponto pt1, ponto pt2, double ang, int tipobase, int interacao)
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	base = tipobase;
	atual = pt1;
	dist = distancia ( pt1 , pt2 )/8; 
	
	for ( n = 0; n < 32; n++)
	{
		interac = interacao;		
			switch ( ( n%32 ) ) 
			{
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
			if ( interac > 0 ) {
				ilhadekochQII( atual , prox, angulo ( atual , prox ), base, --interac );
			}
			else if ( interacao == 0 )
			{
				if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
			draw_segmento(atual , prox);
			}
			atual = prox;
	}	
}

void peanogosper ( ponto pt1, ponto pt2, double ang, int tipobase, int interacao) 
{
	ponto prox, atual;
	int base, n, p, interac;
	double dist;
	base = tipobase;
	atual = pt1;
	dist = distancia ( pt1 , pt2 )/sqrt(7); 
	
	for ( n = 0; n < 7; n++)
	{
		interac = interacao;		
			switch ( ( n%7 ) ) 
			{
				case 0:
				p = 0;
				break;
				case 1:
				p = 1;
				break;
				case 2:
				p = 3;
				break;
				case 3:
				p = 2;
				break;
				case 4:
				case 5:
				p = 0;
				break;
				case 6:
				p = -1;
				break;
			}
			if ( interac > 0 ) {
				prox.x = atual.x + dist*cos( ang + angbase + (p * (pi)/3) );
				prox.y = atual.y + dist*sin( ang + angbase + (p * (pi)/3) );
				peanogosper( atual , prox, angulo ( atual , prox ), base, --interac );
			}
			else if ( interacao == 0 )
			{
				if ( multicor == 1 ) escolhecor ( fabs( cos( atual.x ) ) , fabs ( cos ( prox.x) ), fabs ( cos ( atual.y ) ) );  
			draw_segmento(atual , prox);
			}
			atual = prox;
   }
}

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

void tipo ( int value )
{
	ponto pt;
	pt.x = 100;
	pt.y = 100;
	base = value;
  switch ( base ) {
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

void interac ( int value )
{
  inter += value;
}

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
  submencor = glutCreateMenu(menucor);
  
  glutAddMenuEntry("Branco", 0);
  glutAddMenuEntry("Vermelho", 1);
  glutAddMenuEntry("Verde", 2);
  glutAddMenuEntry("Azul", 3);
  glutAddMenuEntry("Amarelo", 4);
  glutAddMenuEntry("Rosa", 5);
  glutAddMenuEntry("Azul Piscina", 6);
  glutAddMenuEntry("Random", 7);

	submenint = glutCreateMenu(interac);
	
	glutAddMenuEntry("++", 1);
  glutAddMenuEntry("--", -1);

  /*Criando um menu para as bases*/
  submenb = glutCreateMenu(tipo);

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
  glClearColor(0.0, 0.0, 0.0, 1.0);

  glColor3f(1.0, 1.0, 1.0); /*cor vermelha*/
}

int main(int argc, char ** argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowSize(500,500); /*se voce deseja deixar em fullscreen comente essa linha
                                 e descomente a glutFullScreen(). Se quer só aumentar o
                                 tamanho inicial da janela, basta trocar os valores*/
  glutCreateWindow("EP 2 - Fractais");  
/*    glutFullScreen();   */

  init();
  createMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop(); /*O OpenGL passa a tomar controle total do programa*/
  
  return 0;
}

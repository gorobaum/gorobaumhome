/*Parte deste código foi retirado de http://mindfuck.de-brauwer.be/articles/glut/ */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>   
#include <math.h>           

#define QUIT 0
#define EXEC 1
#define X 2
#define Y 3
#define Z 4
#define CLEAR 5
#define pi 3.141592653589793238462643

static int win;
static int menid;
static int submenid;
static int submenb;
static int primitive = 0;
static int base;
static int Frac;
static int interac = 0;

typedef struct p {
		double x;
		double y;
		} ponto;

double angulo ( ponto p1 , ponto p2 )
{
	return atan2( ( p2.y - p1.y ), ( p2.x - p1.x ) );
} 

double distancia ( ponto p1 , ponto p2 )
{
	double d1, d2;
	
	d1 = (p1.x - p2.x)*(p1.x - p2.x);
	d2 = (p1.y - p2.y)*(p1.y - p2.y);

	return ( sqrt( d1 + d2 ) );
}


void draw_segmento( ponto p1, ponto p2 )
{      
  glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
  glEnd();
}

void ilhadekochT ( ponto p1, ponto p2, int inter, int base )
{
	ponto prox, atual;
	double angext, dist, ang;
	int lados, n, k, p, nivel;
	
	nivel = inter;
	
	switch ( base ) {
	case 13:
	lados = 3;
	break;
	case 14:
	lados = 4;
	break;
	case 15:
	lados = 5;
	break;
	case 16:
	lados = 6;
	break;
	} 
	
	angext = (2*pi)/lados;
	ang = 0;
	atual = p1;
	prox = p2;
	dist = distancia(atual, prox)/pow(3,nivel);
	for ( k = 0; k <= lados ; k++ )
	{
		ang += k*angext;
		for ( n = 0; n <= pow(4,nivel); n++ )
		{
			switch ( n%4 ) {
			case 3:
			case 0:
			p = 0;
			break;
			case 1:
			p = 1;
			break;
			case 2:
			p = -1;
			break;
			}
			ang += (p*(pi)/3);
			prox.x = atual.x + dist*cos( ang );
			prox.y = atual.y + dist*sin( ang );
			draw_segmento ( prox , atual );
			atual = prox;
		}
	}
}

void display(void)
{
  /*Toda vez que o OpenGL vai desenhar algo chama essa função*/
  glClear(GL_COLOR_BUFFER_BIT);
  
  if ( primitive != EXEC ) { 
  Frac = primitive;
  interac = 0;
  }
  
  int x;
	ponto p1, p2;
	p1.x = 100;
	p1.y = 100;
	p2.x = 200;
	p2.y = 100;
	
	if ( primitive == EXEC ) {
		primitive = 0;
		switch ( Frac ) {
		case 2:
		x = interac;
		ilhadekochT( p1, p2, x ,base);
		interac ++;
		break;
  	}
  }
  
  glFlush();/*Força desenhar a janela (Não apagar)*/
}


void menu(int value)
{
  /*Aqui são tratadas as chamadas ao menu
   value é o ID do item no menu*/

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

void menub ( int value )
{
	base = value;
}

void createMenu(void)
{
	/*Criando um menu para as bases*/
	submenb = glutCreateMenu(menub);
	
	glutAddMenuEntry("Triangulo", 13);
  glutAddMenuEntry("Quadrado", 14);
  glutAddMenuEntry("Pentagono", 15);
  glutAddMenuEntry("Hexagono", 16);
	
  /*Criando um menu*/
  submenid = glutCreateMenu(menu);

  /*Adicionando entradas*/
  glutAddMenuEntry("Ilha de Koch Triadica", X);
  glutAddMenuEntry("Ilha de Koch Quadrica", Y);
  glutAddMenuEntry("Z", Z);

  /*Criando outro menu. Daqui em diante ele é o principal*/
  menid = glutCreateMenu(menu);

  /* Criando entradas*/
  glutAddMenuEntry("Exec", EXEC);

  /*Associando o menu submenid como submenu*/
  glutAddSubMenu("Fractal", submenid);
  glutAddSubMenu("Base", submenb);
  
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
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glColor3f(1.0, 0.0, 0.0); /*cor vermelha*/
}

int main(int argc, char ** argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

  glutInitWindowSize(500,500); /*se voce deseja deixar em fullscreen comente essa linha
                                 e descomente a glutFullScreen(). Se quer só aumentar o
                                 tamanho inicial da janela, basta trocar os valores*/
  glutCreateWindow("Segmento");  
/*    glutFullScreen();   */

  init();
  createMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop(); /*O OpenGL passa a tomar controle total do programa*/
  
  return 0;
}

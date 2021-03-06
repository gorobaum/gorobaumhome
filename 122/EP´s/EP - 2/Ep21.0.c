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

typedef struct p {
 				double x;
				double y;
				} ponto;

static int win;
static int menid;
static int submenid;
static int submenb;
static int primitive = 10;
static int base = 0;
static int Frac = 2;
static ponto ptbase[6];
static double angpt[6];
static int inter = 0;


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
	ptbase[0] = pt;	
	prox = pt;
	atual = pt;

	for ( k = 0; k < nlado ; k ++) 
	{
	prox.x = atual.x + lado*cos( k*angext );
	prox.y = atual.y + lado*sin( k*angext );
	angpt[k] = angulo( atual , prox );
	draw_segmento(atual , prox);
	ptbase[k+1] = prox;
	atual = prox;
	}
}

void ilhadekoch( ponto pt, int tipobase)
{
	double dist, angext, ang;
	ponto atual, prox;
	int k, lados, p, n;
	n = 0;
	
	switch ( tipobase ) {
	case 13:
	poligono ( pt , 200 , 3 );
	lados = 3;
	break;
	case 14:
	poligono ( pt , 200 , 4 );
	lados = 4;
	break;
	case 15:
	poligono ( pt , 150 , 5 );
	lados = 5;
	break;
	case 16:
	poligono ( pt , 150 , 6 );
	lados = 6;
	break;
	}
	
	
	angext = (2*pi)/lados ;
	dist = 200/pow(3,inter);
	ang = 0;
 
	for ( n = 0; n < lados; n++)
	{
		ang += n*angext;
		atual = ptbase[n];
		for ( k = 0; k < pow(4,inter); k++)
		{
			switch ( ( k%4 ) ) 
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
			ang += p * (pi/3); 
			prox.x = atual.x + dist*cos( ang );
			prox.y = atual.y + dist*sin( ang );
			draw_segmento(atual , prox);
			atual = prox;
		}	
	}
}

double distancia ( ponto p1 , ponto p2 )
{
	double d1, d2;
	
	d1 = (p1.x - p2.x)*(p1.x - p2.x);
	d2 = (p1.y - p2.y)*(p1.y - p2.y);

	return ( sqrt( d1 + d2 ) );
} 

void display(void)
{
  /*Toda vez que o OpenGL vai desenhar algo chama essa função*/
  glClear(GL_COLOR_BUFFER_BIT);
	
  if( primitive == EXEC) {
    ponto pt;
		pt.x = 100;
		pt.y = 100;
		inter ++;
    
		switch ( Frac ) {
		case 2:
    ilhadekoch( pt, base );
		break;
		}
		primitive = 10;
  }

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
  base = value;
}

void createMenu(void)
{
  /*Criando um menu para as bases*/
  submenb = glutCreateMenu(tipo);

  glutAddMenuEntry("Triangulo", 13);
  glutAddMenuEntry("Quadrado", 14);
	glutAddMenuEntry("Pentagono", 15);
	glutAddMenuEntry("Hexagono", 16);

  /*Criando um menu*/
  submenid = glutCreateMenu(menu);

  /*Adicionando entradas*/
  glutAddMenuEntry("Ilha de Koch", X);
  glutAddMenuEntry("Y", Y);
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

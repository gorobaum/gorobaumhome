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
static int primitive = 10;
static int base = 13;
static int Frac = 2;

typedef struct ponto {
 				double x;
				double y;
				} Ponto;

void draw_segmento( Ponto p1, Ponto p2 )
{      
  glBegin(GL_LINES);
    glVertex2f( p1.x, p1.y);
    glVertex2f( p2.x, p2.y);
  glEnd();
}

Apontador insere ( Apontador lista , double x , double y)
{
	Apontador p = lista,novo = malloc ( sizeof ( Ponto ) );
	if ( novo == NULL ) exit(0);
	novo->x = x;
	novo->y = y;
	novo->ap = NULL;
	while ( p->ap != NULL )
			p = p->ap;
	p->ap = novo;
	return lista;
}

Apontador poligono ( Apontador apont , double lado, int nlado )
{
	Apontador atual, prox, novo, inicial;
	int k = 0;
	prox = malloc ( sizeof ( Ponto ) );
	if ( prox == NULL ) exit(0);
	prox->ap = NULL;
	prox->x = 0;
	prox->y = 0;
	double angext = (2*pi)/nlado;
	
	inicial = apont;
	atual = apont;  

	for ( k = 0; k < nlado ; k ++) 
	{
	prox->x = atual->x + lado*cos( k*angext );
	prox->y = atual->y + lado*sin( k*angext );
	insere ( inicial , prox->x, prox->y);
	draw_segmento(atual , prox);
	atual = prox;
	}
}

void ilhadekoch( Apontador apont, int tipobase, int inter)
{
	switch ( tipobase ) {
	case 13:
	poligono ( apont , 200 , 3 );
	break;
	case 14:
	poligono ( apont , 200 , 4 );
	break;
	case 15:
	poligono ( apont , 150 , 5 );
	break;
	case 16:
	poligono ( apont , 150 , 6 );
	break;
	}
	

}

double distancia ( Ponto p1 , Ponto p2 )
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
		Apontador apont;
    Ponto pt;
		pt.x = 200;
		pt.y = 200;
		pt.ap = NULL;
		
		apont = &pt;
    
		switch ( Frac ) {
		case 2:
    ilhadekoch( apont, base, 1 );
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

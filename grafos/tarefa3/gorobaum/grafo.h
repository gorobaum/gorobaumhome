/*password rajimema123 */
/*username Gorobaum */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */


#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHshow DIGRAPHshow
#define maxV 100
#define LINESIZE 10

typedef struct digraph *Digraph;

int DIGRAPHpath (Digraph G);
void DIGRAPHshow (Digraph G);
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w);
int DIGRAPHNumArcs( Vertex w, Digraph G );
int* DIGRAPHVertexArcs( Vertex w, Digraph G );
int DIGRAPHGetNumVet( Digraph G );
Digraph DIGRAPHinit (int V);

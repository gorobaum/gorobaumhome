/*username Gorobaum */
/*password rajimema123 */
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

typedef struct digraph *Digraph;

int DIGRAPHpath(Digraph G, int parnt[]);
void DIGRAPHshow(Digraph G);
void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w, double cst);
int DIGRAPHNumArcs( Vertex w, Digraph G );
int* DIGRAPHVertexArcs( Vertex w, Digraph G );
int DIGRAPHGetNumVet( Digraph G );
Digraph DIGRAPHinit(int V);
int DIGRAPHcycle(Digraph G, Vertex s, int parnt[]);
void DIGRAPHdfs (Digraph G, Vertex s, int pos[]);
void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst);
void dijkstra(Graph G, Vertex s, Vertex parnt[], double cst[]);

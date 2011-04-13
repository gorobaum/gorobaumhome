/*password rajimema123 */
/*username Gorobaum */
/*Nome Thiago de Gouveia Nunes */
/*nusp 6797289 */


#include <stdio.h>
#include <stdlib.h>
#include "grafos.c"

typedef struct digraph *Digraph;

int DIGRAPHpath (Digraph G);
void DIGRAPHshow (Digraph G);
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w);
Digraph DIGRAPHinit (int V);

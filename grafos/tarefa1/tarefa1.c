#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph


typedef struct {
    Vertex v;
    Vertex w;
} Arc;

typedef struct digraph *Digraph;

struct digraph {
    int V;
    int A;
    int **adj;
};

Arc ARC (Vertex v, Vertex w) {
    Arc e;
    e.v=v;
    e.w=w;
    return e;
}

int **MATRIXinit (int r, int c, int val) {
    Vertex i, j;
    int **m = malloc(r*sizeof(*int));
    for ( i = 0; i < r; i++)
        m[i] = malloc( c*sizeof(int));
    for ( i = 0; i < r; i++ )
        for ( j = 0; j < c; j++ )
            m[i][j] = val;
    return m;
}

Digraph DIGRAPHinit (int V) {
    Digraph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = MATRIXinit( V, V, 0 );
    return G;
}

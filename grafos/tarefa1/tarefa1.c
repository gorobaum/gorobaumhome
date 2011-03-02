#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHshow DIGRAPHshow
#define MAXVERTEX 100

static int lbl[MAXVERTEX];

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
    int **m;
    m = malloc( r*sizeof(int *));
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

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    if (v != w && G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    if ( G->adj[v][w] == 1 ) {
        G->adj[v][w] = 0;
        G->A--;
    }
}

void DIGRAPHshow (Digraph G) {
    Vertex v, w;
    for ( v = 0; v < G->V; v++ ) {
        printf("%2d:", v);
        for ( w = 0; w < G->V; w++ )
            if ( G->adj[v][w] == 1 ) printf(" %2d ", w);
        printf("\n");
    }
}

void GRAPHinsertE (Graph G, Vertex v, Vertex w) {
    DIGRAPHinsertA(G, v, w); 
    DIGRAPHinsertA(G, w, v);
}

int pathR (Digraph G, Vertex v, Vertex t) {
    Vertex w;
    lbl[v] = 0;
    if ( v == t ) return 1;
    for ( w = 0; w < G->V; w++ ) 
        if ( G->adj[v][w] == 1 && lbl[w] == -1 )
            if ( pathR(G, w, t) == 1 )
                return 1;
    return 0;
}

int DIGRAPHpath (Digraph G, Vertex s, Vertex t) {
    Vertex v;
    for ( v = 0; v > G->V; v++ )
        lbl[v] = -1;
    return pathR(G, s, t);
}

int main (int argc, char **argv) {
    int Arcs, Vertexs, c[3], i;
    Digraph G;    
    for ( i = 0; i < 3; i++ ) c[i] = getchar();
    Vertexs = c[0] - '0';
    Arcs = c[2] - '0';
    printf("Pessoas - %d \nAmizades - %d \n", Arcs, Vertexs);
    
    while ( c[0] != EOF ) {
        for ( i = 0; i < 3; i++ ) { 
            c[i] = getchar();
            printf("%x \n", c[i]);
            if ( c[i] == EOF ) break;
        }
        printf("Vertex %d-%d", c[0], c[2]);
    }
    G = DIGRAPHinit( Vertexs );   
    return 0;
}
